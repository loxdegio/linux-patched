#ifndef _ASM_X86_VDSO_H
#define _ASM_X86_VDSO_H

#include <asm/page_types.h>
#include <linux/linkage.h>
#include <linux/init.h>

#ifndef __ASSEMBLER__

#include <linux/mm_types.h>

struct vdso_image {
	void *data;
	unsigned long size;   /* Always a multiple of PAGE_SIZE */

	/* text_mapping.pages is big enough for data/size page pointers */
	struct vm_special_mapping text_mapping;

	unsigned long alt, alt_len;

	unsigned long sym_end_mapping;  /* Total size of the mapping */

	unsigned long sym_vvar_page;
	unsigned long sym_hpet_page;
	unsigned long sym_VDSO32_NOTE_MASK;
	unsigned long sym___kernel_sigreturn;
	unsigned long sym___kernel_rt_sigreturn;
	unsigned long sym___kernel_vsyscall;
	unsigned long sym_VDSO32_SYSENTER_RETURN;
};

#ifdef CONFIG_X86_64
extern const struct vdso_image vdso_image_64;
#endif

#ifdef CONFIG_X86_X32
extern const struct vdso_image vdso_image_x32;
#endif

#if defined CONFIG_X86_32 || defined CONFIG_COMPAT
extern const struct vdso_image vdso_image_32_int80;
#if defined(CONFIG_COMPAT) || defined(CONFIG_X86_XEN)
extern const struct vdso_image vdso_image_32_syscall;
#endif
extern const struct vdso_image vdso_image_32_sysenter;

extern const struct vdso_image *selected_vdso32;
#endif

extern void __init init_vdso_image(const struct vdso_image *image);

#endif /* __ASSEMBLER__ */

#endif /* _ASM_X86_VDSO_H */
