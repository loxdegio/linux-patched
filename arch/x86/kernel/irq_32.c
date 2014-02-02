/*
 *	Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 *
 * This file contains the lowest level x86-specific interrupt
 * entry, irq-stacks and irq statistics code. All the remaining
 * irq logic is done by the generic kernel/irq/ code and
 * by the x86-specific irq controller code. (e.g. i8259.c and
 * io_apic.c.)
 */

#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/notifier.h>
#include <linux/cpu.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/percpu.h>
#include <linux/mm.h>

#include <asm/apic.h>

DEFINE_PER_CPU_SHARED_ALIGNED(irq_cpustat_t, irq_stat);
EXPORT_PER_CPU_SYMBOL(irq_stat);

DEFINE_PER_CPU(struct pt_regs *, irq_regs);
EXPORT_PER_CPU_SYMBOL(irq_regs);

#ifdef CONFIG_DEBUG_STACKOVERFLOW

int sysctl_panic_on_stackoverflow __read_mostly;

/* Debugging check for stack overflow: is there less than 1KB free? */
static int check_stack_overflow(void)
{
	long sp;

	__asm__ __volatile__("andl %%esp,%0" :
			     "=r" (sp) : "0" (THREAD_SIZE - 1));

	return sp < STACK_WARN;
}

static void print_stack_overflow(void)
{
	printk(KERN_WARNING "low stack detected by irq handler\n");
	dump_stack();
	if (sysctl_panic_on_stackoverflow)
		panic("low stack detected by irq handler - check messages\n");
}

#else
static inline int check_stack_overflow(void) { return 0; }
static inline void print_stack_overflow(void) { }
#endif

/*
 * per-CPU IRQ handling contexts (thread information and stack)
 */
union irq_ctx {
	unsigned long		previous_esp;
	u32			stack[THREAD_SIZE/sizeof(u32)];
} __attribute__((aligned(THREAD_SIZE)));

static DEFINE_PER_CPU(union irq_ctx *, hardirq_ctx);
static DEFINE_PER_CPU(union irq_ctx *, softirq_ctx);

static void call_on_stack(void *func, void *stack)
{
	asm volatile("xchgl	%%ebx,%%esp	\n"
		     "call	*%%edi		\n"
		     "movl	%%ebx,%%esp	\n"
		     : "=b" (stack)
		     : "0" (stack),
		       "D"(func)
		     : "memory", "cc", "edx", "ecx", "eax");
}

static inline int
execute_on_irq_stack(int overflow, struct irq_desc *desc, int irq)
{
	union irq_ctx *irqctx;
	u32 *isp, arg1, arg2;

	irqctx = __this_cpu_read(hardirq_ctx);

	/*
	 * this is where we switch to the IRQ stack. However, if we are
	 * already using the IRQ stack (because we interrupted a hardirq
	 * handler) we can't do that and just have to keep using the
	 * current stack (which is the irq stack already after all)
	 */
	if (unlikely((void *)current_stack_pointer - (void *)irqctx < THREAD_SIZE))
		return 0;

	/* build the stack frame on the IRQ stack */
	isp = (u32 *) ((char *)irqctx + sizeof(*irqctx) - 8);
	irqctx->previous_esp = current_stack_pointer;

#ifdef CONFIG_PAX_MEMORY_UDEREF
	__set_fs(MAKE_MM_SEG(0));
#endif

	if (unlikely(overflow))
		call_on_stack(print_stack_overflow, isp);

	asm volatile("xchgl	%%ebx,%%esp	\n"
		     "call	*%%edi		\n"
		     "movl	%%ebx,%%esp	\n"
		     : "=a" (arg1), "=d" (arg2), "=b" (isp)
		     :  "0" (irq),   "1" (desc),  "2" (isp),
			"D" (desc->handle_irq)
		     : "memory", "cc", "ecx");

#ifdef CONFIG_PAX_MEMORY_UDEREF
	__set_fs(current_thread_info()->addr_limit);
#endif

	return 1;
}

/*
 * allocate per-cpu stacks for hardirq and for softirq processing
 */
void irq_ctx_init(int cpu)
{
	if (per_cpu(hardirq_ctx, cpu))
		return;

	per_cpu(hardirq_ctx, cpu) = page_address(alloc_pages_node(cpu_to_node(cpu), THREADINFO_GFP, THREAD_SIZE_ORDER));
	per_cpu(softirq_ctx, cpu) = page_address(alloc_pages_node(cpu_to_node(cpu), THREADINFO_GFP, THREAD_SIZE_ORDER));
}

void do_softirq_own_stack(void)
{
	union irq_ctx *irqctx;
	u32 *isp;

	irqctx = __this_cpu_read(softirq_ctx);
	irqctx->previous_esp = current_stack_pointer;

	/* build the stack frame on the softirq stack */
	isp = (u32 *) ((char *)irqctx + sizeof(*irqctx) - 8);

#ifdef CONFIG_PAX_MEMORY_UDEREF
	__set_fs(MAKE_MM_SEG(0));
#endif

	call_on_stack(__do_softirq, isp);

#ifdef CONFIG_PAX_MEMORY_UDEREF
	__set_fs(current_thread_info()->addr_limit);
#endif

}

bool handle_irq(unsigned irq, struct pt_regs *regs)
{
	struct irq_desc *desc;
	int overflow;

	overflow = check_stack_overflow();

	desc = irq_to_desc(irq);
	if (unlikely(!desc))
		return false;

	if (user_mode(regs) || !execute_on_irq_stack(overflow, desc, irq)) {
		if (unlikely(overflow))
			print_stack_overflow();
		desc->handle_irq(irq, desc);
	}

	return true;
}
