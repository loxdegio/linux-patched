/*
 * Copyright 2013 Ideas On Board SPRL
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DT_BINDINGS_CLOCK_R8A7790_H__
#define __DT_BINDINGS_CLOCK_R8A7790_H__

/* CPG */
#define R8A7790_CLK_MAIN		0
#define R8A7790_CLK_PLL0		1
#define R8A7790_CLK_PLL1		2
#define R8A7790_CLK_PLL3		3
#define R8A7790_CLK_LB			4
#define R8A7790_CLK_QSPI		5
#define R8A7790_CLK_SDH			6
#define R8A7790_CLK_SD0			7
#define R8A7790_CLK_SD1			8
#define R8A7790_CLK_Z			9

/* MSTP0 */
#define R8A7790_CLK_MSIOF0		0

/* MSTP1 */
#define R8A7790_CLK_VCP1		0
#define R8A7790_CLK_VCP0		1
#define R8A7790_CLK_VPC1		2
#define R8A7790_CLK_VPC0		3
#define R8A7790_CLK_JPU			6
#define R8A7790_CLK_SSP1		9
#define R8A7790_CLK_TMU1		11
#define R8A7790_CLK_3DG			12
#define R8A7790_CLK_2DDMAC		15
#define R8A7790_CLK_FDP1_2		17
#define R8A7790_CLK_FDP1_1		18
#define R8A7790_CLK_FDP1_0		19
#define R8A7790_CLK_TMU3		21
#define R8A7790_CLK_TMU2		22
#define R8A7790_CLK_CMT0		24
#define R8A7790_CLK_TMU0		25
#define R8A7790_CLK_VSP1_DU1		27
#define R8A7790_CLK_VSP1_DU0		28
#define R8A7790_CLK_VSP1_R		30
#define R8A7790_CLK_VSP1_S		31

/* MSTP2 */
#define R8A7790_CLK_SCIFA2		2
#define R8A7790_CLK_SCIFA1		3
#define R8A7790_CLK_SCIFA0		4
#define R8A7790_CLK_MSIOF2		5
#define R8A7790_CLK_SCIFB0		6
#define R8A7790_CLK_SCIFB1		7
#define R8A7790_CLK_MSIOF1		8
#define R8A7790_CLK_MSIOF3		15
#define R8A7790_CLK_SCIFB2		16
#define R8A7790_CLK_SYS_DMAC1		18
#define R8A7790_CLK_SYS_DMAC0		19

/* MSTP3 */
#define R8A7790_CLK_IIC2		0
#define R8A7790_CLK_TPU0		4
#define R8A7790_CLK_MMCIF1		5
#define R8A7790_CLK_SDHI3		11
#define R8A7790_CLK_SDHI2		12
#define R8A7790_CLK_SDHI1		13
#define R8A7790_CLK_SDHI0		14
#define R8A7790_CLK_MMCIF0		15
#define R8A7790_CLK_IIC0		18
#define R8A7790_CLK_PCIEC		19
#define R8A7790_CLK_IIC1		23
#define R8A7790_CLK_SSUSB		28
#define R8A7790_CLK_CMT1		29
#define R8A7790_CLK_USBDMAC0		30
#define R8A7790_CLK_USBDMAC1		31

/* MSTP5 */
#define R8A7790_CLK_AUDIO_DMAC1		1
#define R8A7790_CLK_AUDIO_DMAC0		2
#define R8A7790_CLK_THERMAL		22
#define R8A7790_CLK_PWM			23

/* MSTP7 */
#define R8A7790_CLK_EHCI		3
#define R8A7790_CLK_HSUSB		4
#define R8A7790_CLK_HSCIF1		16
#define R8A7790_CLK_HSCIF0		17
#define R8A7790_CLK_SCIF1		20
#define R8A7790_CLK_SCIF0		21
#define R8A7790_CLK_DU2			22
#define R8A7790_CLK_DU1			23
#define R8A7790_CLK_DU0			24
#define R8A7790_CLK_LVDS1		25
#define R8A7790_CLK_LVDS0		26

/* MSTP8 */
#define R8A7790_CLK_VIN3		8
#define R8A7790_CLK_VIN2		9
#define R8A7790_CLK_VIN1		10
#define R8A7790_CLK_VIN0		11
#define R8A7790_CLK_ETHER		13
#define R8A7790_CLK_SATA1		14
#define R8A7790_CLK_SATA0		15

/* MSTP9 */
#define R8A7790_CLK_GPIO5		7
#define R8A7790_CLK_GPIO4		8
#define R8A7790_CLK_GPIO3		9
#define R8A7790_CLK_GPIO2		10
#define R8A7790_CLK_GPIO1		11
#define R8A7790_CLK_GPIO0		12
#define R8A7790_CLK_RCAN1		15
#define R8A7790_CLK_RCAN0		16
#define R8A7790_CLK_QSPI_MOD		17
#define R8A7790_CLK_IICDVFS		26
#define R8A7790_CLK_I2C3		28
#define R8A7790_CLK_I2C2		29
#define R8A7790_CLK_I2C1		30
#define R8A7790_CLK_I2C0		31

/* MSTP10 */
#define R8A7790_CLK_SSI_ALL		5
#define R8A7790_CLK_SSI9		6
#define R8A7790_CLK_SSI8		7
#define R8A7790_CLK_SSI7		8
#define R8A7790_CLK_SSI6		9
#define R8A7790_CLK_SSI5		10
#define R8A7790_CLK_SSI4		11
#define R8A7790_CLK_SSI3		12
#define R8A7790_CLK_SSI2		13
#define R8A7790_CLK_SSI1		14
#define R8A7790_CLK_SSI0		15
#define R8A7790_CLK_SCU_ALL		17
#define R8A7790_CLK_SCU_DVC1		18
#define R8A7790_CLK_SCU_DVC0		19
#define R8A7790_CLK_SCU_SRC9		22
#define R8A7790_CLK_SCU_SRC8		23
#define R8A7790_CLK_SCU_SRC7		24
#define R8A7790_CLK_SCU_SRC6		25
#define R8A7790_CLK_SCU_SRC5		26
#define R8A7790_CLK_SCU_SRC4		27
#define R8A7790_CLK_SCU_SRC3		28
#define R8A7790_CLK_SCU_SRC2		29
#define R8A7790_CLK_SCU_SRC1		30
#define R8A7790_CLK_SCU_SRC0		31

#endif /* __DT_BINDINGS_CLOCK_R8A7790_H__ */
