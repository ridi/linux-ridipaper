/*
 * Copyright (C) 2011-2013 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/linkage.h>
#include <mach/hardware.h>

#define L2_CACHE_SYNC	0x730

.extern iram_tlb_phys_addr
.globl mx6_lpddr2_iram_start
.globl mx6_lpddr2_iram_end

	.macro   switch_to_400MHz

	/* check if periph_clk_sel is already set */
	ldr	r0, [r6, #0x14]
	and	r0, r0, #0x2000000
	cmp	r0, #0x2000000
	beq	set_ahb_podf_before_switch1

	/* 
	 * Step 1: Change periph_clk to be sourced from pll3_clk.
	 * Ensure PLL3 is the source and set the divider to 1.
	 */
	ldr	r0, [r6, #0x18]
	bic	r0, r0, #0x3000
	str	r0, [r6, #0x18]

	ldr     r0, [r6, #0x14]
	bic     r0, r0, #0x38000000
	str     r0, [r6, #0x14]

	/* Now switch periph_clk to pll3_main_clk. */
	ldr	r0, [r6, #0x14]
	orr	r0, r0, #0x2000000
	str	r0, [r6, #0x14]

periph_clk_switch5:
	ldr	r0, [r6, #0x48]
	cmp	r0, #0
	bne	periph_clk_switch5

	b	switch_pre_periph_clk_400

set_ahb_podf_before_switch1:
	/*
	 * Set the AHB dividers before the switch.
	 * Especially if the AHB is at 24MHz, divider
	 * would be at divide by 1 and clock
	 * would be too fast when switching to PLL3.
	 */
	ldr	r0, [r6, #0x14]
	ldr	r2, =0x3f1f00
	bic	r0, r0, r2
	orr	r0, r0, #0x900
	orr	r0, r0, #0x10000
	str	r0, [r6, #0x14]

wait_div_update400_1:
	ldr	r0, [r6, #0x48]
	cmp	r0, #0
	bne	wait_div_update400_1

switch_pre_periph_clk_400:
	/* Now switch pre_periph_clk to PFD_400MHz. */
	ldr	r0, [r6, #0x18]
	bic	r0, r0, #0xC0000
	orr	r0, r0, #0x40000
	str	r0, [r6, #0x18]

	/* Now switch periph_clk back. */
	ldr	r0, [r6, #0x14]
	bic	r0, r0, #0x2000000
	str	r0, [r6, #0x14]

periph_clk_switch6:
	ldr	r0, [r6, #0x48]
	cmp	r0, #0
	bne	periph_clk_switch6

	/*
	 * change AHB divider so that we are at 400/3=133MHz.
	 * don't change AXI clock divider.
	 * Set the MMDC_DIV=1, AXI_DIV=2, AHB_DIV=3 (need to maintain GPT divider).
	 */
	ldr	r0, [r6, #0x14]
	ldr	r2, =0x3f1f00
	bic	r0, r0, r2
	orr	r0, r0, #0x900
	orr	r0, r0, #0x10000
	str	r0, [r6, #0x14]

wait_div_update400_2:
	ldr	r0, [r6, #0x48]
	cmp	r0, #0
	bne	wait_div_update400_2

	ldr     r0, =ANATOP_BASE_ADDR
	add     r0, r0, #PERIPBASE_VIRT
	ldr	r1, [r0, #0x260]
	mov	r2, r1
	/*Is mx6q?*/
	and	r1, r1, #0xff0000
	cmp	r1, #0x630000
	bne	skip_gpt_workaround2
	/*Is mx6q TO1.0?*/
	and	r2, r2, #0xff
	cmp	r2, #0x0
	bne	skip_gpt_workaround2
	/* Change the GPT divider so that its at 6MHz. */
	ldr	r0, [r6, #0x1C]
	bic	r0, r0, #0x3F
	orr	r0, r0, #0xA
	str	r0, [r6, #0x1C]
skip_gpt_workaround2:
	.endm

	.macro   switch_to_24MHz
	/*
	 * Change the freq now
	 * Try setting DDR to 24MHz.
	 * Source it from the periph_clk2
	 * Ensure the periph_clk2 is sourced from 24MHz
	 * and the divider is 1.
	 */
	ldr	r0, [r6, #0x18]
	bic	r0, r0, #0x3000
	orr	r0, r0, #0x1000
	str	r0, [r6, #0x18]

	ldr	r0, [r6, #0x14]
	bic	r0, r0, #0x38000000
	str	r0, [r6, #0x14]

	/* Now switch periph_clk to 24MHz. */
	ldr	r0, [r6, #0x14]
	orr	r0, r0, #0x2000000
	str	r0, [r6, #0x14]

periph_clk_switch1:
	ldr	r0, [r6, #0x48]
	cmp	r0, #0
	bne	periph_clk_switch1

	/* Change all the dividers to 1. */
	ldr	r0, [r6, #0x14]
	ldr	r2, =0x3f1f00
	bic	r0, r0, r2
	orr	r0, r0, #0x100
	str	r0, [r6, #0x14]

	/* Wait for the divider to change. */
wait_div_update:
	ldr	r0, [r6, #0x48]
	cmp	r0, #0
	bne	wait_div_update

	ldr     r0, =ANATOP_BASE_ADDR
	add     r0, r0, #PERIPBASE_VIRT
	ldr	r1, [r0, #0x260]
	mov	r2, r1
	/*Is mx6q?*/
	and	r1, r1, #0xff0000
	cmp	r1, #0x630000
	bne	skip_gpt_workaround4
	/*Is mx6q TO1.0?*/
	and	r2, r2, #0xff
	cmp	r2, #0x0
	bne	skip_gpt_workaround4
	/* Change the GPT divider so that its at 6MHz. */
	ldr	r0, [r6, #0x1C]
	bic	r0, r0, #0x3F
	orr	r0, r0, #0x1
	str	r0, [r6, #0x1C]
skip_gpt_workaround4:

	.endm

	.macro   mmdc_clk_lower_100MHz

	/*
	 * Prior to reducing the DDR frequency (at 528/400 MHz),
	 * read the Measure unit count bits (MU_UNIT_DEL_NUM)
	 */
	ldr	r2, =0x8B8
	ldr	r0, [r5, r2]
	/* Original MU unit count */
	mov	r0, r0, LSR #16
	ldr	r1, =0x3FF
	and	r0, r0, r1
	/* Original MU unit count * 2 */
	mov	r11, r0, LSL #1
	/*
	 * Bypass the automatic measure unit when below 100 MHz
	 * by setting the Measure unit bypass enable bit (MU_BYP_EN)
	 */
	ldr	r0, [r5, r2]
	orr	r0, r0, #0x400
	str	r0, [r5, r2]
	/*
	 * Double the measure count value read in step 1 and program it in the
	 * measurement bypass bits (MU_BYP_VAL) of the MMDC PHY Measure Unit
	 * Register for the reduced frequency operation below 100 MHz
	 */
	ldr	r0, [r5, r2]
	ldr	r1, =0x3FF
	bic	r0, r0, r1
	orr	r0, r0, r11
	str	r0, [r5, r2]
	/* Now perform a Force Measurement. */
	ldr	r0, [r5, r2]
	orr	r0, r0, #0x800
	str	r0, [r5, r2]

	/*
	 * Prior to reducing the DDR frequency (at 528/400 MHz),
	 * read the Measure unit count bits (MU_UNIT_DEL_NUM)
	 */
	ldr	r2, =0x8B8
	ldr	r0, [r7, r2]
	/* Original MU unit count */
	mov	r0, r0, LSR #16
	ldr	r1, =0x3FF
	and	r0, r0, r1
	/* Original MU unit count * 2 */
	mov	r11, r0, LSL #1
	/*
	 * Bypass the automatic measure unit when below 100 MHz
	 * by setting the Measure unit bypass enable bit (MU_BYP_EN)
	 */
	ldr	r0, [r7, r2]
	orr	r0, r0, #0x400
	str	r0, [r7, r2]
	/*
	 * Double the measure count value read in step 1 and program it in the
	 * measurement bypass bits (MU_BYP_VAL) of the MMDC PHY Measure Unit
	 * Register for the reduced frequency operation below 100 MHz
	 */
	ldr	r0, [r7, r2]
	ldr	r1, =0x3FF
	bic	r0, r0, r1
	orr	r0, r0, r11
	str	r0, [r7, r2]
	/* Now perform a Force Measurement. */
	ldr	r0, [r7, r2]
	orr	r0, r0, #0x800
	str	r0, [r7, r2]
	/* Wait for FRC_MSR to clear. */
lower_100MHz_wait:
	ldr	r0, [r5, r2]
	and	r0, r0, #0x800
	cmp	r0, #0x0
	bne	lower_100MHz_wait

lower_100MHz_wait_1:
	ldr	r0, [r7, r2]
	and	r0, r0, #0x800
	cmp	r0, #0x0
	bne	lower_100MHz_wait_1

	.endm

	.macro   mmdc_clk_above_100MHz

	/* Make sure that the PHY measurement unit is NOT in bypass mode */
	ldr	r2, =0x8B8
	ldr	r0, [r5, r2]
	bic	r0, r0, #0x400
	str	r0, [r5, r2]
	/* Now perform a Force Measurement. */
	ldr	r0, [r5, r2]
	orr	r0, r0, #0x800
	str	r0, [r5, r2]

	/* Make sure that the PHY measurement unit is NOT in bypass mode */
	ldr	r2, =0x8B8
	ldr	r0, [r7, r2]
	bic	r0, r0, #0x400
	str	r0, [r7, r2]
	/* Now perform a Force Measurement. */
	ldr	r0, [r7, r2]
	orr	r0, r0, #0x800
	str	r0, [r7, r2]
	/* Wait for FRC_MSR to clear. */
above_100MHz:
	ldr	r0, [r5, r2]
	and	r0, r0, #0x800
	cmp	r0, #0x0
	bne	above_100MHz

above_100MHz_1:
	ldr	r0, [r7, r2]
	and	r0, r0, #0x800
	cmp	r0, #0x0
	bne	above_100MHz_1

	.endm

	.macro	disable_l1_dcache

	/*
	 * Flush all data from the L1 data cache before disabling
	 * SCTLR.C bit.
	 */
	push	{r0 - r11, lr}

	ldr	r0, =v7_flush_kern_cache_all
	mov	lr, pc
	mov	pc, r0
	pop	{r0 - r11, lr}

	/* disable d-cache */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x4
	mcr	p15, 0, r0, c1, c0, 0
	dsb
	isb

	push	{r0 - r11, lr}

	ldr	r0, =v7_flush_kern_cache_all
	mov	lr, pc
	mov	pc, r0
	pop	{r0 - r11, lr}

	.endm

    /*
	 *  mx6_lpddr2_freq_change
	 *
	 *  Idle the processor (eg, wait for interrupt).
	 *  Make sure DDR is in self-refresh.
	 *  IRQs are already disabled.
	 */
ENTRY(mx6_lpddr2_freq_change)
mx6_lpddr2_iram_start:

	stmfd	sp!, {r4-r11}	@ Save registers

	ldr	r5, =MMDC_P0_BASE_ADDR
	add	r5, r5, #PERIPBASE_VIRT
	ldr	r6, =CCM_BASE_ADDR
	add	r6, r6, #PERIPBASE_VIRT
	ldr	r7, =MMDC_P1_BASE_ADDR
	add	r7, r7, #PERIPBASE_VIRT
	mov	r4, r0				@save new freq requested

lpddr2_freq_change:
	/* Make sure no TLB miss will occur when the DDR is in self refresh.
	 * Invalidate TLB single entry to ensure that the address is not
	 * already in the TLB.
	 */

	adr	r10, lpddr2_freq_change		@Address in this function.

	mcr	p15, 0, r10, c8, c7, 1		@//@ Make sure freq code address
									@//  @ is not already in TLB.
	mcr	p15, 0, r5, c8, c7, 1		@//@ make sure MMDC_P0 address
									@//@ is not already in TLB.
	mcr	p15, 0, r6, c8, c7, 1		@//@ Make sure CCM address
									@//@ is not already in TLB.
	mcr	p15, 0, r7, c8, c7, 1		@//@ make sure MMDC_P1 address
									@//@ is not already in TLB.

	mrc	p15, 0, r0, c10, c0, 0		@//@ Read the TLB lockdown register
	orr	r0, r0, #1					@//@ Set the Preserve bit.
	mcr	p15, 0, r0, c10, c0, 0		@//@ Write to the lockdown register

	ldr	r2, [r5]					@ TLB will miss,
									@MMDC_P0 address will be loaded
	ldr	r2, [r6]					@ TLB will miss,
									@CCM address will be loaded
	ldr	r2, [r7]					@ TLB will miss,
									@MMDC_P1 will be loaded
	ldr	r2, [r10]					@ TLB will miss

	mrc	p15, 0, r0, c10, c0, 0		@//@ Read the lockdown register
									@//@ (victim will be incremented)
	bic	r0, r0, #1					@//@ Clear the preserve bit
	mcr	p15, 0, r0, c10, c0, 0		@//@ Write to the lockdown register

	/* Make sure all the L1 & L2 buffers are drained, as
	  * we don't want any writes to the DDR when it is
	  * in self-refresh.
	  */
	/* Make sure the L1 buffers are drained. */
	dsb

	/*
	  * Need to flush and disable L1 before disabling L2, we need data to
	  * coherent. Flushing L1 pushes everyhting to L2. We sync L2 later, but
	  * it can still have dirty lines. While exiting, we need to enable L2 first
	  * and then L1.
	 . */
	disable_l1_dcache

#ifdef CONFIG_CACHE_L2X0
	/* Make sure the L2 buffers are drained.
	  * Sync operation on L2 drains the buffers.
	  */
	ldr      r0, =L2_BASE_ADDR
	add     r0, r0, #PERIPBASE_VIRT
	/* Wait for background operations to complete. */
wait_for_l2_to_idle:
	ldr	r1, [r0, #L2_CACHE_SYNC]
	cmp	r1, #0x0
	bne	wait_for_l2_to_idle

	mov    r1, #0x0
	str      r1, [r0, #0x730]
    /* Disable L2. */
    str   r1, [r0, #0x100]
#endif

     /* The second dsb might be needed to keep cache sync (device write)
       * ordering with the memory accesses before it.
       */
	dsb
	isb

	/* Disable automatic power saving. */

	ldr	r0, [r5, #0x404]
	orr	r0, r0, #0x01
	str	r0, [r5, #0x404]

	ldr	r0, [r7, #0x404]
	orr	r0, r0, #0x01
	str	r0, [r7, #0x404]

	/*
	 * Disable MMDC power down timer.
	 * MMDC0_MDPDC disable power down timer
	 */
	ldr	r0, [r5, #0x4]
	bic	r0, r0, #0xff00
	str	r0, [r5, #0x4]

	ldr	r0, [r7, #0x4]
	bic	r0, r0, #0xff00
	str	r0, [r7, #0x4]

	/* Delay for a while */
	ldr	r1, =10
delay1:
	ldr	r2, =0
cont1:
	ldr	r0, [r5, r2]
	add	r2, r2, #4
	cmp	r2, #16
	bne	cont1
	sub     r1, r1, #1
	cmp	r1, #0
	bgt	delay1

	/* set DVFS - enter self refresh mode */
	ldr	r0, [r5, #0x404]
	orr	r0, r0, #0x200000
	str	r0, [r5, #0x404]

	ldr	r0, [r7, #0x404]
	orr	r0, r0, #0x200000
	str	r0, [r7, #0x404]

poll_dvfs_set_1:
	ldr	r0, [r5, #0x404]
	and	r0, r0, #0x2000000
	cmp	r0, #0x2000000
	bne	poll_dvfs_set_1

poll_dvfs_set_2:
	ldr	r0, [r7, #0x404]
	and	r0, r0, #0x2000000
	cmp	r0, #0x2000000
	bne	poll_dvfs_set_2

	/* if requested frequency is greater than 100MHz go to 400MHz */
	ldr	r1, =100000000
	cmp	r4, r1
	bge	switch_freq_400

    ldr    r0, [r5, #0x10] /* MMDC0_MDCFG1 */  
    and    r0, r0, #0x0F
	cmp    r0, #2
	bne    skip_RL_WL_6_3

	ldr    r0,=0x03162073  
    str    r0,[r5, #0xc] /* MMDC0_MDCFG0 */  
    ldr    r0,=0x00020482  
    str    r0,[r5, #0x10] /* MMDC0_MDCFG1 */  
    ldr    r0,=0x00000049  
    str    r0,[r5, #0x14] /* MMDC0_MDCFG2 */  
    ldr    r0,=0x00020333  
    str    r0,[r5, #0x38] /* MMDC0_MDCFG3LP */  
    ldr    r0,=0x0000168c  
    str    r0,[r5, #0x18] /* MMDC0_MISC */  

    ldr    r0,=0x03162073  
    str    r0,[r7, #0xc] /* MMDC0_MDCFG0 */  
    ldr    r0,=0x00020482  
    str    r0,[r7, #0x10] /* MMDC0_MDCFG1 */  
    ldr    r0,=0x00000049  
    str    r0,[r7, #0x14] /* MMDC0_MDCFG2 */  
    ldr    r0,=0x00020333  
    str    r0,[r7, #0x38] /* MMDC0_MDCFG3LP */  
    ldr    r0,=0x0000168c  
    str    r0,[r7, #0x18] /* MMDC0_MISC */  

skip_RL_WL_6_3:
	mmdc_clk_lower_100MHz
	switch_to_24MHz

	b	freq_done

switch_freq_400:
	switch_to_400MHz
	mmdc_clk_above_100MHz

    ldr    r0, [r5, #0x10] /* MMDC0_MDCFG1 */  
    and    r0, r0, #0x0F
	cmp    r0, #2
	bne    skip_restore_RL_WL_6_3

    ldr    r0,=0x53574133  
    str    r0,[r5, #0xc] /* MMDC0_MDCFG0 */  
    ldr    r0,=0x00110A82  
    str    r0,[r5, #0x10] /* MMDC0_MDCFG1 */  
    ldr    r0,=0x00000093  
    str    r0,[r5, #0x14] /* MMDC0_MDCFG2 */  
    ldr    r0,=0x00190778  
    str    r0,[r5, #0x38] /* MMDC0_MDCFG3LP */  
    ldr    r0,=0x0000174c  
    str    r0,[r5, #0x18] /* MMDC0_MISC */  

    ldr    r0,=0x53574133  
    str    r0,[r7, #0xc] /* MMDC0_MDCFG0 */  
    ldr    r0,=0x00110A82  
    str    r0,[r7, #0x10] /* MMDC0_MDCFG1 */  
    ldr    r0,=0x00000093  
    str    r0,[r7, #0x14] /* MMDC0_MDCFG2 */  
    ldr    r0,=0x00190778  
    str    r0,[r7, #0x38] /* MMDC0_MDCFG3LP */  
    ldr    r0,=0x0000174c  
    str    r0,[r7, #0x18] /* MMDC0_MISC */  

skip_restore_RL_WL_6_3:

freq_done:

	/* clear DVFS - exit from self refresh mode */
	ldr	r0, [r5, #0x404]
	bic	r0, r0, #0x200000
	str	r0, [r5, #0x404]

	ldr	r0, [r7, #0x404]
	bic	r0, r0, #0x200000
	str	r0, [r7, #0x404]

poll_dvfs_clear_1:
	ldr	r0, [r5, #0x404]
	and	r0, r0, #0x2000000
	cmp	r0, #0x2000000
	beq	poll_dvfs_clear_1
poll_dvfs_clear_2:
	ldr	r0, [r7, #0x404]
	and	r0, r0, #0x2000000
	cmp	r0, #0x2000000
	beq	poll_dvfs_clear_2

     ldr     r1, =24000000
     cmp    r4, r1
     beq     skip_power_down

	/*
	 * MMDC0_MAPSR adopt power down enable
	 * setmem /32 0x021b0404 = 0x00011006
	 */
	ldr	r0, [r5, #0x404]
	bic	r0, r0, #0x01
	str	r0, [r5, #0x404]

	ldr	r0, [r7, #0x404]
	bic	r0, r0, #0x01
	str	r0, [r7, #0x404]

	/* Enable MMDC power down timer. */
	ldr	r0, [r5, #0x4]
	orr	r0, r0, #0x5500
	str	r0, [r5, #0x4]

	ldr	r0, [r7, #0x4]
	orr	r0, r0, #0x5500
	str	r0, [r7, #0x4]

skip_power_down:
     /* clear SBS - unblock DDR accesses */
     ldr     r0, [r5, #0x410]
     bic     r0, r0, #0x100
     str     r0, [r5, #0x410]

     ldr     r0, [r7, #0x410]
     bic     r0, r0, #0x100
     str     r0, [r7, #0x410]

#ifdef CONFIG_CACHE_L2X0
    /* Enable L2. */
	ldr      r0, =L2_BASE_ADDR
	add     r0, r0, #PERIPBASE_VIRT
	ldr    r1, =0x1
    str   r1, [r0, #0x100]
	dsb
	isb
#endif

	/* Enable L1 data cache. */
	mrc    p15, 0, r0, c1, c0, 0
	orr    r0, r0, #0x4
	mcr    p15, 0, r0, c1, c0, 0
	/* Restore registers */
	
	isb
	dsb

    nop
    nop
    nop
    nop
    nop

    nop
    nop
    nop
    nop
    nop

    nop
    nop
    nop
    nop
    nop

    nop
    nop
    nop
    nop
    nop

    nop
    nop
    nop
    nop
    nop

	ldmfd sp!, {r4-r11}
	mov     pc, lr

	/*
	 * Add ltorg here to ensure that all
	 * literals are stored here and are
	 * within the text space.
	 */
	.ltorg
mx6_lpddr2_iram_end:

ENDPROC(mx6_lpddr2_freq_change)

