/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc. All Rights Reserved.
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

#include <linux/types.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/nodemask.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include <linux/fsl_devices.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>
#include <linux/i2c.h>
#include <linux/i2c/pca953x.h>
#include <linux/ata.h>
#include <linux/regulator/consumer.h>
#include <linux/pmic_external.h>
#include <linux/pmic_status.h>
#include <linux/ipu.h>
#include <linux/mxcfb.h>
#include <linux/pwm_backlight.h>
#include <linux/fec.h>
#include <linux/memblock.h>
#include <linux/gpio.h>
#include <linux/ion.h>
#include <linux/etherdevice.h>
#include <linux/power/sabresd_battery.h>
#include <linux/regulator/anatop-regulator.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/fixed.h>
#include <linux/mfd/max17135.h>
#include <linux/mfd/wm8994/pdata.h>
#include <linux/mfd/wm8994/gpio.h>
#include <sound/wm8962.h>
#include <linux/mfd/mxc-hdmi-core.h>

#include <mach/common.h>
#include <mach/hardware.h>
#include <mach/mxc_dvfs.h>
#include <mach/memory.h>
#include <mach/iomux-mx6q.h>
#include <mach/imx-uart.h>
#include <mach/viv_gpu.h>
#include <mach/ahci_sata.h>
#include <mach/ipu-v3.h>
#include <mach/mxc_hdmi.h>
#include <mach/mxc_asrc.h>
#include <mach/mipi_dsi.h>
#include <mach/system.h>

#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <linux/mmc/sdhci.h>
#include "usb.h"
#include "devices-imx6q.h"
#include "crm_regs.h"
#include "cpu_op-mx6.h"
#include "board-mx6dl_ntx.h"

#include "ntx_hwconfig.h"

#include "ntx_firmware_parser.h"
#include "ntx_firmware.h"

#include <linux/mfd/ricoh619.h>
#include <linux/rtc/rtc-ricoh619.h>
#include <linux/power/ricoh619_battery.h>
#include <linux/regulator/ricoh619-regulator.h>

#include <linux/cyttsp5_core.h>
#include <linux/cyttsp5_platform.h>

#include <mach/imx_rfkill.h>

#define GDEBUG 0
#include <linux/gallen_dbg.h>

#include <linux/wlan_plat.h>

#define ntx_EPDC_SDDO_0	IMX_GPIO_NR(2, 22)
#define ntx_EPDC_SDDO_1	IMX_GPIO_NR(3, 10)
#define ntx_EPDC_SDDO_2	IMX_GPIO_NR(3, 12)
#define ntx_EPDC_SDDO_3	IMX_GPIO_NR(3, 11)
#define ntx_EPDC_SDDO_4	IMX_GPIO_NR(2, 27)
#define ntx_EPDC_SDDO_5	IMX_GPIO_NR(2, 30)
#define ntx_EPDC_SDDO_6	IMX_GPIO_NR(2, 23)
#define ntx_EPDC_SDDO_7	IMX_GPIO_NR(2, 26)
#define ntx_EPDC_SDDO_8	IMX_GPIO_NR(2, 24)
#define ntx_EPDC_SDDO_9	IMX_GPIO_NR(3, 15)
#define ntx_EPDC_SDDO_10	IMX_GPIO_NR(3, 16)
#define ntx_EPDC_SDDO_11	IMX_GPIO_NR(3, 23)
#define ntx_EPDC_SDDO_12	IMX_GPIO_NR(3, 19)
#define ntx_EPDC_SDDO_13	IMX_GPIO_NR(3, 13)
#define ntx_EPDC_SDDO_14	IMX_GPIO_NR(3, 14)
#define ntx_EPDC_SDDO_15	IMX_GPIO_NR(5, 2)
#define ntx_EPDC_GDCLK	IMX_GPIO_NR(2, 17)
#define ntx_EPDC_GDSP	IMX_GPIO_NR(2, 16)
#define ntx_EPDC_GDOE	IMX_GPIO_NR(6, 6)
#define ntx_EPDC_GDRL	IMX_GPIO_NR(5, 4)
#define ntx_EPDC_SDCLK	IMX_GPIO_NR(3, 31)
#define ntx_EPDC_SDOEZ	IMX_GPIO_NR(3, 30)
#define ntx_EPDC_SDOED	IMX_GPIO_NR(3, 26)
#define ntx_EPDC_SDOE	IMX_GPIO_NR(3, 27)
#define ntx_EPDC_SDLE	IMX_GPIO_NR(3, 1)
#define ntx_EPDC_SDCLKN	IMX_GPIO_NR(3, 0)
#define ntx_EPDC_SDSHR	IMX_GPIO_NR(2, 29)
#define ntx_EPDC_PWRCOM	IMX_GPIO_NR(2, 28)
#define ntx_EPDC_PWRSTAT	IMX_GPIO_NR(2, 21)
#define ntx_EPDC_PWRCTRL0	IMX_GPIO_NR(2, 20)
#define ntx_EPDC_PWRCTRL1	IMX_GPIO_NR(2, 19)
#define ntx_EPDC_PWRCTRL2	IMX_GPIO_NR(2, 18)
#define ntx_EPDC_PWRCTRL3	IMX_GPIO_NR(3, 28)
#define ntx_EPDC_BDR0	IMX_GPIO_NR(3, 2)
#define ntx_EPDC_BDR1	IMX_GPIO_NR(3, 3)
#define ntx_EPDC_SDCE0	IMX_GPIO_NR(3, 4)
#define ntx_EPDC_SDCE1	IMX_GPIO_NR(3, 5)
#define ntx_EPDC_SDCE2	IMX_GPIO_NR(3, 6)
#define ntx_EPDC_SDCE3	IMX_GPIO_NR(3, 7)
#define ntx_EPDC_SDCE4	IMX_GPIO_NR(3, 8)
#define ntx_EPDC_PMIC_WAKE	IMX_GPIO_NR(3, 20)
#define ntx_EPDC_PMIC_INT	IMX_GPIO_NR(2, 25)
#define ntx_EPDC_VCOM	IMX_GPIO_NR(3, 17)

#define MX6DL_WACOM_INT			IMX_GPIO_NR(2, 6)
#define MX6DL_WACOM_PDCT		IMX_GPIO_NR(2, 5)
#define MX6DL_WACOM_FWE			IMX_GPIO_NR(2, 4)
#define MX6DL_WACOM_RST			IMX_GPIO_NR(2, 7)

extern char *gp_reg_id;
extern char *soc_reg_id;
extern char *pu_reg_id;
extern int epdc_enabled;
extern u32 enable_ldo_mode;
extern int gSleep_Mode_Suspend;

#define _MYINIT_DATA	
#define _MYINIT_TEXT	
volatile static unsigned char _MYINIT_DATA *gpbHWCFG_paddr;
volatile unsigned long _MYINIT_DATA gdwHWCFG_size;
volatile int _MYINIT_DATA giBootPort;
volatile unsigned long _MYINIT_DATA gdwNTXFW_size;
volatile NTX_HWCONFIG *gptHWCFG;

volatile unsigned gMX6DL_WIFI_3V3 = IMX_GPIO_NR(2, 13);
volatile unsigned gMX6DL_WIFI_RST = IMX_GPIO_NR(2, 14);
volatile unsigned gMX6DL_WIFI_INT = IMX_GPIO_NR(2, 12);
volatile unsigned gMX6DL_BT_EN = IMX_GPIO_NR(1, 4);	/* KEY_ROW1 */
volatile unsigned gMX6DL_BT_INT = -1;

NTX_FW_LM3630FL_RGBW_current_tab_hdr *gptLm3630fl_RGBW_curr_tab_hdr = 0;
NTX_FW_LM3630FL_dualcolor_hdr *gptLm3630fl_dualcolor_tab_hdr = 0;
NTX_FW_LM3630FL_dualcolor_percent_tab *gptLm3630fl_dualcolor_percent_tab = 0;

static void * _MemoryRequest(void *addr, u32 len, const char * name)
{
    void * mem = NULL;
    do {
        printk(KERN_DEBUG "***%s:%d: request memory region! addr=%p, len=%hd***\n",
                __FUNCTION__, __LINE__, addr, len);
        if (!request_mem_region((u32)addr, len, name)) {
            printk(KERN_CRIT "%s():  request memory region failed! addr=%p, len %hd\n",__FUNCTION__, addr, len);
            break;
        }
        mem = (void *) ioremap_nocache((u32)addr, len);
        if (!mem) {
            printk(KERN_CRIT "***%s:%d: could not ioremap %s***\n", __FUNCTION__, __LINE__, name);
            release_mem_region((u32)addr, len);
            break;
        }
    } while (0);
    return mem;
}

int gIsCustomerUi;
static int _MYINIT_TEXT hwcfg_p_setup(char *str)
{
	gpbHWCFG_paddr = (unsigned char *)simple_strtoul(str,NULL,0);
	if(NULL==gptHWCFG) {
		gptHWCFG = (NTX_HWCONFIG *)_MemoryRequest((void *)gpbHWCFG_paddr, gdwHWCFG_size, "hwcfg_p");
		if(!gptHWCFG) {
			return 0;
		}
	}
	printk("%s() hwcfg_p=%p,vaddr=%p,size=%d,pcb=0x%x\n",__FUNCTION__,
		gpbHWCFG_paddr,gptHWCFG,(int)gdwHWCFG_size,gptHWCFG->m_val.bPCB);
	gIsCustomerUi = (int)gptHWCFG->m_val.bUIStyle;
	
	return 1;
}

#ifdef CONFIG_ANDROID_RAM_CONSOLE
static struct resource ram_console_resource = {
	.name = "android ram console",
	.flags = IORESOURCE_MEM,
};

static struct platform_device android_ram_console = {
	.name = "ram_console",
	.num_resources = 1,
	.resource = &ram_console_resource,
};

static int __init imx6x_add_ram_console(void)
{
	return platform_device_register(&android_ram_console);
}
#else
#define imx6x_add_ram_console() do {} while (0)
#endif

static int _MYINIT_TEXT ram_console_p_setup(char *str)
{
#ifdef CONFIG_ANDROID_RAM_CONSOLE
	phys_addr_t phys = (phys_addr_t)simple_strtoul(str,NULL,0);

	ram_console_resource.start = phys;
	ram_console_resource.end   = phys + SZ_1M - 1;
#endif

	return 1;
}

static int _MYINIT_TEXT hwcfg_size_setup(char *str)
{
	gdwHWCFG_size = (unsigned long)simple_strtoul(str,NULL,0);
	printk("%s() hwcfg_szie=%d\n",__FUNCTION__,(int)gdwHWCFG_size);
	return 1;
}

static int _MYINIT_TEXT boot_port_setup(char *str)
{
	giBootPort = (int)simple_strtoul(str,NULL,0);
	printk("%s() boot_port=%d\n",__FUNCTION__,giBootPort);
	return 1;
}

volatile static unsigned char _MYINIT_DATA *gpbNTXFW_paddr;
volatile unsigned long _MYINIT_DATA gdwNTXFW_size;
volatile NTX_FIRMWARE_HDR *gptNTXFW;

#if 0
extern NTX_FW_LM3630FL_RGBW_current_tab_hdr *gptLm3630fl_RGBW_curr_tab_hdr;
extern NTX_FW_LM3630FL_dualcolor_hdr *gptLm3630fl_dualcolor_tab_hdr;
extern NTX_FW_LM3630FL_dualcolor_percent_tab *gptLm3630fl_dualcolor_percent_tab;
#endif

static int ntxfw_item_proc(
		NTX_FIRMWARE_HDR *I_ptFWHdr,
		NTX_FIRMWARE_ITEM_HDR *I_ptFWItemHdr,
		void *I_pvFWItemBin,int I_iItemIdx)
{
	int iRet = 0;

	if(!gptHWCFG) {
		return -1;
	}

	if(I_ptFWItemHdr->dw12345678!=0x12345678) {
		printk(KERN_WARNING"ntxfw format error !\n");
		return -2;
	}

	printk("ntxfw[%d],\"%s\",type=0x%x,sz=%d\n",I_iItemIdx,
			I_ptFWItemHdr->szFirmwareName,
			I_ptFWItemHdr->wFirmwareType,
			(int)I_ptFWItemHdr->dwFirmwareSize);

	if( 2==gptHWCFG->m_val.bFL_PWM||4==gptHWCFG->m_val.bFL_PWM||
			5==gptHWCFG->m_val.bFL_PWM||6==gptHWCFG->m_val.bFL_PWM||
			7==gptHWCFG->m_val.bFL_PWM)
	{

		if(NTX_FW_TYPE_FLPERCETCURTABLE==I_ptFWItemHdr->wFirmwareType) {
			extern void ntx_percent_curr_tab_set(void *pvTable);
			ntx_percent_curr_tab_set(I_pvFWItemBin);
		}

#if	0 //def CONFIG_BACKLIGHT_LM3630A//[
		// models with lm3630 .
		else if(NTX_FW_TYPE_LM3630_FLPERCTTAB==I_ptFWItemHdr->wFirmwareType) {
			NTX_FW_LM3630FL_percent_tab *ptLm3630fl_percent_tab = I_pvFWItemBin;
			printk("lm3630fl percent table,color=%d\n",ptLm3630fl_percent_tab->bColor);

			if(1==gptHWCFG->m_val.bFrontLight) {
				// TABLE0 .
				lm3630a_set_FL_W_duty_table(gptHWCFG->m_val.bFrontLight,
					100,ptLm3630fl_percent_tab->bPercentBrightnessA);
				lm3630a_set_default_power_by_table(gptHWCFG->m_val.bFrontLight,
					ptLm3630fl_percent_tab->bDefaultCurrent);
			}
		}
		else if(NTX_FW_TYPE_LM3630_FLCURTABLE==I_ptFWItemHdr->wFirmwareType) {
			NTX_FW_LM3630FL_current_tab *ptLm3630fl_ricohcurr_tab = I_pvFWItemBin;
			printk("lm3630fl ricoh current table,color=%d\n",ptLm3630fl_ricohcurr_tab->bColor);

			if(5==gptHWCFG->m_val.bFL_PWM) {
				// RGBW FL .
				if(NTX_FW_FL_COLOR_WHITE==ptLm3630fl_ricohcurr_tab->bColor) {
					lm3630a_set_FL_RicohCurrTab(1,1,ptLm3630fl_ricohcurr_tab->dwCurrentA,255);
				}
				else
				if(NTX_FW_FL_COLOR_RED==ptLm3630fl_ricohcurr_tab->bColor) {
					lm3630a_set_FL_RicohCurrTab(1,0,ptLm3630fl_ricohcurr_tab->dwCurrentA,255);
				}
				else
				if(NTX_FW_FL_COLOR_GREEN==ptLm3630fl_ricohcurr_tab->bColor) {
					lm3630a_set_FL_RicohCurrTab(0,1,ptLm3630fl_ricohcurr_tab->dwCurrentA,255);
				}
				else
				if(NTX_FW_FL_COLOR_BLUE==ptLm3630fl_ricohcurr_tab->bColor) {
					lm3630a_set_FL_RicohCurrTab(0,0,ptLm3630fl_ricohcurr_tab->dwCurrentA,255);
				}
			}

		}
		else if(NTX_FW_TYPE_LM3630_RGBW_CURTAB_HDR==I_ptFWItemHdr->wFirmwareType) {
			gptLm3630fl_RGBW_curr_tab_hdr = I_pvFWItemBin;
			printk("lm3630fl RGBW curr table:%d items\n",(int)gptLm3630fl_RGBW_curr_tab_hdr->dwTotalItems);
		}
		else if(NTX_FW_TYPE_LM3630_RGBW_CURTAB==I_ptFWItemHdr->wFirmwareType) {
			NTX_FW_LM3630FL_RGBW_current_item *L_ptLm3630fl_RGBW_cur_tab = I_pvFWItemBin;
			if(gptLm3630fl_RGBW_curr_tab_hdr) {
				lm3630a_set_FL_RGBW_RicohCurrTab(gptLm3630fl_RGBW_curr_tab_hdr->dwTotalItems,L_ptLm3630fl_RGBW_cur_tab);
			}
			else {
				printk(KERN_ERR"[Warning] LM3630FL RGBW curr table header not exist !!\n");
			}
		}
		else if(NTX_FW_TYPE_LM3630_DUALFL_HDR==I_ptFWItemHdr->wFirmwareType) {
			gptLm3630fl_dualcolor_tab_hdr = I_pvFWItemBin;
			printk("lm3630fl dual color table : %d temperatures ,c1_pwr=0x%x,c2_pwr=0x%x\n",
				(int)gptLm3630fl_dualcolor_tab_hdr->dwTotalColors,
				gptLm3630fl_dualcolor_tab_hdr->bDefaultC1_Current,
				gptLm3630fl_dualcolor_tab_hdr->bDefaultC2_Current);
		}
		else if(NTX_FW_TYPE_LM3630_DUALFL_PERCENTTAB==I_ptFWItemHdr->wFirmwareType) {
			if(gptLm3630fl_dualcolor_tab_hdr) {
				gptLm3630fl_dualcolor_percent_tab = I_pvFWItemBin;
			}
			else {
				printk(KERN_ERR"[Warning] LM3630FL dualcolor table header not exist !!\n");
			}
		}
		else if(NTX_FW_TYPE_LM3630_MIX2COLOR11_CURTAB==I_ptFWItemHdr->wFirmwareType) {
			NTX_FW_LM3630FL_MIX2COLOR11_current_tab *L_ptLm3630fl_Mix2Color11_curr_tab = I_pvFWItemBin;
			lm3630a_set_FL_Mix2color11_RicohCurrTab(L_ptLm3630fl_Mix2Color11_curr_tab);
		}
#endif //]CONFIG_BACKLIGHT_LM3630A
		else {
		}
	}

	return iRet;
}


static int _MYINIT_TEXT ntxfw_p_setup(char *str)
{
	gpbNTXFW_paddr = (unsigned char *)simple_strtoul(str,NULL,0);
	gptNTXFW = (NTX_FIRMWARE_HDR *)_MemoryRequest((void *)gpbNTXFW_paddr, gdwNTXFW_size, "ntxfw_p");

	if(ntx_firmware_parse_fw_buf((NTX_FIRMWARE_HDR *)gptNTXFW,gdwNTXFW_size,ntxfw_item_proc)<0) {
		gpbNTXFW_paddr = 0;
		gptNTXFW = 0;
		gdwNTXFW_size = 0;
		return 0;
	}
	else {
		printk("%s() ntxfw_p=%p,vaddr=%p,size=%d,name=\"%s\",items=%d\n",__FUNCTION__,
			gpbNTXFW_paddr,gptNTXFW,(int)gdwNTXFW_size,gptNTXFW->szFirmwareName,(int)gptNTXFW->wFirmwareItems);
		return 1;
	}

}
static int _MYINIT_TEXT ntxfw_size_setup(char *str)
{
	gdwNTXFW_size = (unsigned long)simple_strtoul(str,NULL,0);
	printk("%s() ntxfw_szie=%d\n",__FUNCTION__,(int)gdwNTXFW_size);
	return 1;
}


static void _parse_cmdline(void)
{
	static int iParseCnt = 0;
	char *pcPatternStart,*pcPatternVal,*pcPatternValEnd,cTempStore;
	unsigned long ulPatternLen;

	char *szParsePatternA[]={"hwcfg_sz=","hwcfg_p=","boot_port=","ram_console_p=","ntxfw_sz=","ntxfw_p="};
	int ((*pfnDispatchA[])(char *str))={hwcfg_size_setup,hwcfg_p_setup,boot_port_setup,ram_console_p_setup ,ntxfw_size_setup,ntxfw_p_setup};

	int i;
	char *pszCmdLineBuf;


	if(iParseCnt++>0) {
		printk("%s : cmdline parse already done .\n",__FUNCTION__);
		return ;
	}
	//printk("%s():cmdline(%d)=%s\n",__FUNCTION__,strlen(saved_command_line),saved_command_line);

	pszCmdLineBuf = kmalloc(strlen(saved_command_line)+1,GFP_KERNEL);
	//ASSERT(pszCmdLineBuf);
	strcpy(pszCmdLineBuf,saved_command_line);
	printk("%s():cp cmdline=%s\n",__FUNCTION__,pszCmdLineBuf);

	for(i=0;i<sizeof(szParsePatternA)/sizeof(szParsePatternA[0]);i++) {
		ulPatternLen = strlen(szParsePatternA[i]);
		pcPatternStart = strstr(pszCmdLineBuf,szParsePatternA[i]);
		if(pcPatternStart) {
			pcPatternVal=pcPatternStart + ulPatternLen ;
			pcPatternValEnd = strchr(pcPatternVal,' ');
			cTempStore='\0';
			if(pcPatternValEnd) {
				cTempStore = *pcPatternValEnd;
				*pcPatternValEnd = '\0';
			}
			//printk("%s():pattern \"%s\" ,val=\"%s\"\n",__FUNCTION__,szParsePatternA[i],pcPatternVal);
			pfnDispatchA[i](pcPatternVal);
			if(pcPatternValEnd) {
				*pcPatternValEnd = cTempStore;
			}
		}
		else
			printk ("[%s-%d] %s not found !!!\n",__func__,__LINE__,szParsePatternA[i]);
	}
	if (NULL == gptHWCFG) {
		printk ("[%s-%d] personal initial hw config.\n",__func__,__LINE__);
		gptHWCFG = (NTX_HWCONFIG *)kmalloc(sizeof(NTX_HWCONFIG), GFP_KERNEL);
		gptHWCFG->m_val.bTouchCtrl = 8;
	}
}

//static int max17135_regulator_init(struct max17135 *max17135);
static const struct esdhc_platform_data mx6q_ntx_sd1_data __initconst = {
	.always_present = 1,
	.keep_power_at_suspend = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_PERMANENT,
};

static const struct esdhc_platform_data mx6q_ntx_sd2_data __initconst = {
	.keep_power_at_suspend = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_CONTROLLER,
	.runtime_pm = 1,
};

static const struct esdhc_platform_data mx6q_ntx_sd3_data __initconst = {
	.always_present = 1,
	.keep_power_at_suspend = 1,
	.support_8bit = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_PERMANENT,
};

static const struct esdhc_platform_data mx6q_ntx_sd4_data __initconst = {
    .cd_gpio		= MX6DL_WIFI_3V3,
	.wp_gpio 		= -1,
	.keep_power_at_suspend	= 1,
	.delay_line		= 0,
	.cd_type = ESDHC_CD_WIFI_PWR,
};

static const struct anatop_thermal_platform_data
	mx6q_ntx_anatop_thermal_data __initconst = {
		.name = "anatop_thermal",
};

static const struct imxuart_platform_data mx6dl_ntx_uart4_data __initconst = {
	.flags      = IMXUART_HAVE_RTSCTS | IMXUART_SDMA /*| IMXUART_USE_DCEDTE*/,
	.dma_req_rx = MX6Q_DMA_REQ_UART4_RX,
	.dma_req_tx = MX6Q_DMA_REQ_UART4_TX,
};

static const struct imxuart_platform_data mx6dl_ntx_uart5_data __initconst = {
	.flags      = IMXUART_HAVE_RTSCTS | IMXUART_SDMA /*| IMXUART_USE_DCEDTE*/,
	.dma_req_rx = MX6Q_DMA_REQ_UART5_RX,
	.dma_req_tx = MX6Q_DMA_REQ_UART5_TX,
};

static inline void mx6q_ntx_init_uart(void)
{
	imx6q_add_imx_uart(0, NULL);
    printk ("Initial UART5 for bluetooth.\n");
	imx6q_add_imx_uart(3, &mx6dl_ntx_uart4_data); /* UART4 */
	imx6q_add_imx_uart(4, &mx6dl_ntx_uart5_data); /* Bluetooth UART5 */
}

#define mV_to_uV(mV) (mV * 1000)
#define uV_to_mV(uV) (uV / 1000)
#define V_to_uV(V) (mV_to_uV(V * 1000))
#define uV_to_V(uV) (uV_to_mV(uV) / 1000)
#if 0
static struct regulator_consumer_supply display_consumers[] = {
	{
		/* MAX17135 */
		.supply = "DISPLAY",
	},
};

static struct regulator_consumer_supply vcom_consumers[] = {
	{
		/* MAX17135 */
		.supply = "VCOM",
	},
};

static struct regulator_consumer_supply v3p3_consumers[] = {
	{
		/* MAX17135 */
		.supply = "V3P3",
	},
};

static struct regulator_init_data max17135_init_data[] = {
	{
		.constraints = {
			.name = "DISPLAY",
			.valid_ops_mask =  REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(display_consumers),
		.consumer_supplies = display_consumers,
	}, {
		.constraints = {
			.name = "GVDD",
			.min_uV = V_to_uV(20),
			.max_uV = V_to_uV(20),
		},
	}, {
		.constraints = {
			.name = "GVEE",
			.min_uV = V_to_uV(-22),
			.max_uV = V_to_uV(-22),
		},
	}, {
		.constraints = {
			.name = "HVINN",
			.min_uV = V_to_uV(-22),
			.max_uV = V_to_uV(-22),
		},
	}, {
		.constraints = {
			.name = "HVINP",
			.min_uV = V_to_uV(20),
			.max_uV = V_to_uV(20),
		},
	}, {
		.constraints = {
			.name = "VCOM",
			.min_uV = mV_to_uV(-4325),
			.max_uV = mV_to_uV(-500),
			.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE |
			REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(vcom_consumers),
		.consumer_supplies = vcom_consumers,
	}, {
		.constraints = {
			.name = "VNEG",
			.min_uV = V_to_uV(-15),
			.max_uV = V_to_uV(-15),
		},
	}, {
		.constraints = {
			.name = "VPOS",
			.min_uV = V_to_uV(15),
			.max_uV = V_to_uV(15),
		},
	}, {
		.constraints = {
			.name = "V3P3",
			.valid_ops_mask =  REGULATOR_CHANGE_STATUS,
		},
		.num_consumer_supplies = ARRAY_SIZE(v3p3_consumers),
		.consumer_supplies = v3p3_consumers,
	},
};

static struct platform_device max17135_sensor_device = {
	.name = "max17135_sensor",
	.id = 0,
};

static struct max17135_platform_data max17135_pdata __initdata = {
	.vneg_pwrup = 1,
	.gvee_pwrup = 1,
	.vpos_pwrup = 2,
	.gvdd_pwrup = 1,
	.gvdd_pwrdn = 1,
	.vpos_pwrdn = 2,
	.gvee_pwrdn = 1,
	.vneg_pwrdn = 1,
	.gpio_pmic_pwrgood = ntx_EPDC_PWRSTAT,
	.gpio_pmic_vcom_ctrl = ntx_EPDC_VCOM,
	.gpio_pmic_wakeup = ntx_EPDC_PMIC_WAKE,
	.gpio_pmic_v3p3 = ntx_EPDC_PWRCTRL0,
	.gpio_pmic_intr = ntx_EPDC_PMIC_INT,
	.regulator_init = max17135_init_data,
	.init = max17135_regulator_init,
};

static int __init max17135_regulator_init(struct max17135 *max17135)
{
	struct max17135_platform_data *pdata = &max17135_pdata;
	int i, ret;

	if (!epdc_enabled) {
		printk(KERN_DEBUG
			"max17135_regulator_init abort: EPDC not enabled\n");
		return 0;
	}

	max17135->gvee_pwrup = pdata->gvee_pwrup;
	max17135->vneg_pwrup = pdata->vneg_pwrup;
	max17135->vpos_pwrup = pdata->vpos_pwrup;
	max17135->gvdd_pwrup = pdata->gvdd_pwrup;
	max17135->gvdd_pwrdn = pdata->gvdd_pwrdn;
	max17135->vpos_pwrdn = pdata->vpos_pwrdn;
	max17135->vneg_pwrdn = pdata->vneg_pwrdn;
	max17135->gvee_pwrdn = pdata->gvee_pwrdn;

	max17135->max_wait = pdata->vpos_pwrup + pdata->vneg_pwrup +
		pdata->gvdd_pwrup + pdata->gvee_pwrup;

	max17135->gpio_pmic_pwrgood = pdata->gpio_pmic_pwrgood;
	max17135->gpio_pmic_vcom_ctrl = pdata->gpio_pmic_vcom_ctrl;
	max17135->gpio_pmic_wakeup = pdata->gpio_pmic_wakeup;
	max17135->gpio_pmic_v3p3 = pdata->gpio_pmic_v3p3;
	max17135->gpio_pmic_intr = pdata->gpio_pmic_intr;

	gpio_request(max17135->gpio_pmic_wakeup, "epdc-pmic-wake");
	gpio_direction_output(max17135->gpio_pmic_wakeup, 0);

	gpio_request(max17135->gpio_pmic_vcom_ctrl, "epdc-vcom");
	gpio_direction_output(max17135->gpio_pmic_vcom_ctrl, 0);

	gpio_request(max17135->gpio_pmic_v3p3, "epdc-v3p3");
	gpio_direction_output(max17135->gpio_pmic_v3p3, 0);

	gpio_request(max17135->gpio_pmic_intr, "epdc-pmic-int");
	gpio_direction_input(max17135->gpio_pmic_intr);

	gpio_request(max17135->gpio_pmic_pwrgood, "epdc-pwrstat");
	gpio_direction_input(max17135->gpio_pmic_pwrgood);

	max17135->vcom_setup = false;
	max17135->init_done = false;

	for (i = 0; i < MAX17135_NUM_REGULATORS; i++) {
		ret = max17135_register_regulator(max17135, i,
			&pdata->regulator_init[i]);
		if (ret != 0) {
			printk(KERN_ERR"max17135 regulator init failed: %d\n",
				ret);
			return ret;
		}
	}

	/*
	 * TODO: We cannot enable full constraints for now, since
	 * it results in the PFUZE regulators being disabled
	 * at the end of boot, which disables critical regulators.
	 */
	/*regulator_has_full_constraints();*/

	return 0;
}
#endif

/* cyttsp */
#define CYTTSP5_USE_I2C
/* #define CYTTSP5_USE_SPI */

#ifdef CYTTSP5_USE_I2C
#define CYTTSP5_I2C_TCH_ADR 0x24
#define CYTTSP5_LDR_TCH_ADR 0x24
#define CYTTSP5_I2C_IRQ_GPIO 14  // 1_14
#define CYTTSP5_I2C_RST_GPIO 15  // 1_15
#endif


#ifndef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT

#define CYTTSP5_HID_DESC_REGISTER 1

#define CY_VKEYS_X 720
#define CY_VKEYS_Y 1280
#define CY_MAXX 880
#define CY_MAXY 1280
#define CY_MINX 0
#define CY_MINY 0

#define CY_ABS_MIN_X CY_MINX
#define CY_ABS_MIN_Y CY_MINY
#define CY_ABS_MAX_X CY_MAXX
#define CY_ABS_MAX_Y CY_MAXY
#define CY_ABS_MIN_P 0
#define CY_ABS_MAX_P 255
#define CY_ABS_MIN_W 0
#define CY_ABS_MAX_W 255
#define CY_PROXIMITY_MIN_VAL	0
#define CY_PROXIMITY_MAX_VAL	1

#define CY_ABS_MIN_T 0

#define CY_ABS_MAX_T 15

/* Button to keycode conversion */
static u16 cyttsp5_btn_keys[] = {
	/* use this table to map buttons to keycodes (see input.h) */
	KEY_HOMEPAGE,		/* 172 */ /* Previously was KEY_HOME (102) */
				/* New Android versions use KEY_HOMEPAGE */
	KEY_MENU,		/* 139 */
	KEY_BACK,		/* 158 */
	KEY_SEARCH,		/* 217 */
	KEY_VOLUMEDOWN,		/* 114 */
	KEY_VOLUMEUP,		/* 115 */
	KEY_CAMERA,		/* 212 */
	KEY_POWER		/* 116 */
};

static struct touch_settings cyttsp5_sett_btn_keys = {
	.data = (uint8_t *)&cyttsp5_btn_keys[0],
	.size = ARRAY_SIZE(cyttsp5_btn_keys),
	.tag = 0,
};

static struct cyttsp5_core_platform_data _cyttsp5_core_platform_data = {
	.irq_gpio = CYTTSP5_I2C_IRQ_GPIO,
	.rst_gpio = CYTTSP5_I2C_RST_GPIO,
	.hid_desc_register = CYTTSP5_HID_DESC_REGISTER,
	.xres = cyttsp5_xres,
	.init = cyttsp5_init,
	.power = cyttsp5_power,
	.detect = cyttsp5_detect,
	.irq_stat = cyttsp5_irq_stat,
	.sett = {
		NULL,	/* Reserved */
		NULL,	/* Command Registers */
		NULL,	/* Touch Report */
		NULL,	/* Parade Data Record */
		NULL,	/* Test Record */
		NULL,	/* Panel Configuration Record */
		NULL,   /* &cyttsp5_sett_param_regs, */
		NULL,	/* &cyttsp5_sett_param_size, */
		NULL,	/* Reserved */
		NULL,	/* Reserved */
		NULL,	/* Operational Configuration Record */
		NULL, /* &cyttsp5_sett_ddata, *//* Design Data Record */
		NULL, /* &cyttsp5_sett_mdata, *//* Manufacturing Data Record */
		NULL,	/* Config and Test Registers */
		&cyttsp5_sett_btn_keys,	/* button-to-keycode table */
	},
	.flags = CY_CORE_FLAG_RESTORE_PARAMETERS,
	.easy_wakeup_gesture = CY_CORE_EWG_NONE,
};

static const int16_t cyttsp5_abs[] = {
	ABS_MT_POSITION_X, CY_ABS_MIN_X, CY_ABS_MAX_X, 0, 0,
	ABS_MT_POSITION_Y, CY_ABS_MIN_Y, CY_ABS_MAX_Y, 0, 0,
	ABS_MT_PRESSURE, CY_ABS_MIN_P, CY_ABS_MAX_P, 0, 0,
	CY_IGNORE_VALUE, CY_ABS_MIN_W, CY_ABS_MAX_W, 0, 0,
	ABS_MT_TRACKING_ID, CY_ABS_MIN_T, CY_ABS_MAX_T, 0, 0,
	ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0,
	ABS_MT_TOUCH_MINOR, 0, 255, 0, 0,
	ABS_MT_ORIENTATION, -127, 127, 0, 0,
	ABS_MT_TOOL_TYPE, 0, MT_TOOL_MAX, 0, 0,
	ABS_MT_DISTANCE, 0, 255, 0, 0,	/* Used with hover */
};

static struct touch_framework cyttsp5_framework = {
	.abs = (uint16_t *)&cyttsp5_abs[0],
	.size = ARRAY_SIZE(cyttsp5_abs),
	.enable_vkeys = 0,
};

static struct cyttsp5_mt_platform_data _cyttsp5_mt_platform_data = {
	.frmwrk = &cyttsp5_framework,
	.flags = CY_MT_FLAG_INV_X,
	.inp_dev_name = CYTTSP5_MT_NAME,
	.vkeys_x = CY_VKEYS_X,
	.vkeys_y = CY_VKEYS_Y,
};

static struct cyttsp5_btn_platform_data _cyttsp5_btn_platform_data = {
	.inp_dev_name = CYTTSP5_BTN_NAME,
};

static const int16_t cyttsp5_prox_abs[] = {
	ABS_DISTANCE, CY_PROXIMITY_MIN_VAL, CY_PROXIMITY_MAX_VAL, 0, 0,
};

static struct touch_framework cyttsp5_prox_framework = {
	.abs = (uint16_t *)&cyttsp5_prox_abs[0],
	.size = ARRAY_SIZE(cyttsp5_prox_abs),
};

static struct cyttsp5_proximity_platform_data
		_cyttsp5_proximity_platform_data = {
	.frmwrk = &cyttsp5_prox_framework,
	.inp_dev_name = CYTTSP5_PROXIMITY_NAME,
};

static struct cyttsp5_platform_data _cyttsp5_platform_data = {
	.core_pdata = &_cyttsp5_core_platform_data,
	.mt_pdata = &_cyttsp5_mt_platform_data,
	.loader_pdata = &_cyttsp5_loader_platform_data,
	.btn_pdata = &_cyttsp5_btn_platform_data,
	.prox_pdata = &_cyttsp5_proximity_platform_data,
};

#endif /* !CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT */
#if 0
static ssize_t cyttsp5_virtualkeys_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf,
		__stringify(EV_KEY) ":"
		__stringify(KEY_BACK) ":1360:90:160:180"
		":" __stringify(EV_KEY) ":"
		__stringify(KEY_MENU) ":1360:270:160:180"
		":" __stringify(EV_KEY) ":"
		__stringify(KEY_HOMEPAGE) ":1360:450:160:180"
		":" __stringify(EV_KEY) ":"
		__stringify(KEY_SEARCH) ":1360:630:160:180"
		"\n");
}

static struct kobj_attribute cyttsp5_virtualkeys_attr = {
	.attr = {
		.name = "virtualkeys.cyttsp5_mt",
		.mode = S_IRUGO,
	},
	.show = &cyttsp5_virtualkeys_show,
};

static struct attribute *cyttsp5_properties_attrs[] = {
	&cyttsp5_virtualkeys_attr.attr,
	NULL
};

static struct attribute_group cyttsp5_properties_attr_group = {
	.attrs = cyttsp5_properties_attrs,
};

static void __init ntx_cyttsp5_init(void)
#ifndef CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT
{
	struct kobject *properties_kobj;
	int ret = 0;

	/* Initialize muxes for GPIO pins */
	mxc_iomux_v3_setup_pad(MX6DL_PAD_SD2_DAT1__GPIO_1_14);
	if(2 !=gptHWCFG->m_val.bUIStyle)
	{
		properties_kobj = kobject_create_and_add("board_properties", NULL);
		if (properties_kobj)
			ret = sysfs_create_group(properties_kobj,
				&cyttsp5_properties_attr_group);
		if (!properties_kobj || ret)
			pr_err("%s: failed to create board_properties\n", __func__);
	}
}
#else /* CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT */
{
	mxc_iomux_v3_setup_pad(MX6DL_PAD_SD2_DAT1__GPIO_1_14);
}
#endif /* CONFIG_TOUCHSCREEN_CYPRESS_CYTTSP5_DEVICETREE_SUPPORT */
#endif

static struct i2c_board_info i2c_cyttsp_binfo = {
	.type = CYTTSP5_I2C_NAME,
	.addr = 0x24,
 	.irq = CYTTSP5_I2C_IRQ_GPIO,
	.platform_data = &_cyttsp5_platform_data,
};

static struct i2c_board_info i2c_elan_touch_binfo = {
	 .type = "elan-touch",
	 .addr = 0x15,
};

static struct i2c_board_info i2c_gt9xx_touch_binfo = {
	 .type = "Goodix-TS",
	 .addr = 0x14,
};

static struct i2c_board_info i2c_wacom_binfo = {
	.type = "wacom_i2c",
	.addr = 0x09,
};

static struct ricoh619_rtc_platform_data ricoh_rtc_data = {
	.time = {
		.tm_year = 1970,
		.tm_mon = 0,
		.tm_mday = 1,
		.tm_hour = 0,
		.tm_min = 0,
		.tm_sec = 0,
	},
};

static struct ricoh619_battery_platform_data ricoh_battery_data = {
//	.irq 		= RICOH619_IRQ_BASE,
	.alarm_vol_mv 	= 3400,
	// .adc_channel = RICOH619_ADC_CHANNEL_VBAT,
	.multiple	= 100, //100%
	.monitor_time 	= 60,
		/* some parameter is depend of battery type */
	.type[0] = {
		.ch_vfchg 	= 0xFF,	/* VFCHG	= 0 - 4 (4.05v, 4.10v, 4.15v, 4.20v, 4.35v) */
		.ch_vrchg 	= 0xFF,	/* VRCHG	= 0 - 4 (3.85v, 3.90v, 3.95v, 4.00v, 4.10v) */
		.ch_vbatovset 	= 0xFF,	/* VBATOVSET	= 0 or 1 (0 : 4.38v(up)/3.95v(down) 1: 4.53v(up)/4.10v(down)) */
		.ch_ichg 	= 0xFF,	/* ICHG		= 0 - 0x1D (100mA - 3000mA) */
		.ch_ilim_adp 	= 0xFF,	/* ILIM_ADP	= 0 - 0x1D (100mA - 3000mA) */
		.ch_ilim_usb 	= 0xFF,	/* ILIM_USB	= 0 - 0x1D (100mA - 3000mA) */
		.ch_icchg 	= 0,	/* ICCHG	= 0 - 3 (50mA 100mA 150mA 200mA) */
		.fg_target_vsys = 0,	/* This value is the target one to DSOC=0% */
		.fg_target_ibat = 0, /* This value is the target one to DSOC=0% */
		.fg_poff_vbat 	= 3520, 	/* setting value of 0 per Vbat */
		.jt_en 		= 0,	/* JEITA Enable	  = 0 or 1 (1:enable, 0:disable) */
		.jt_hw_sw 	= 1,	/* JEITA HW or SW = 0 or 1 (1:HardWare, 0:SoftWare) */
		.jt_temp_h 	= 50,	/* degree C */
		.jt_temp_l 	= 12,	/* degree C */
		.jt_vfchg_h 	= 0x03,	/* VFCHG High  	= 0 - 4 (4.05v, 4.10v, 4.15v, 4.20v, 4.35v) */
		.jt_vfchg_l 	= 0,	/* VFCHG High  	= 0 - 4 (4.05v, 4.10v, 4.15v, 4.20v, 4.35v) */
		.jt_ichg_h 	= 0x0D,	/* VFCHG Low  	= 0 - 4 (4.05v, 4.10v, 4.15v, 4.20v, 4.35v) */
		.jt_ichg_l 	= 0x09,	/* ICHG Low   	= 0 - 0x1D (100mA - 3000mA) */
	},
	/*
	.type[1] = {
		.ch_vfchg = 0x0,
		.ch_vrchg = 0x0,
		.ch_vbatovset = 0x0,
		.ch_ichg = 0x0,
		.ch_ilim_adp = 0x0,
		.ch_ilim_usb = 0x0,
		.ch_icchg = 0x00,
		.fg_target_vsys = 3300,//3000,
		.fg_target_ibat = 1000,//1000,
		.jt_en = 0,
		.jt_hw_sw = 1,
		.jt_temp_h = 40,
		.jt_temp_l = 10,
		.jt_vfchg_h = 0x0,
		.jt_vfchg_l = 0,
		.jt_ichg_h = 0x01,
		.jt_ichg_l = 0x01,
	},
	*/

/*  JEITA Parameter
*
*          VCHG
*            |
* jt_vfchg_h~+~~~~~~~~~~~~~~~~~~~+
*            |                   |
* jt_vfchg_l-| - - - - - - - - - +~~~~~~~~~~+
*            |    Charge area    +          |
*  -------0--+-------------------+----------+--- Temp
*            !                   +
*          ICHG
*            |                   +
*  jt_ichg_h-+ - -+~~~~~~~~~~~~~~+~~~~~~~~~~+
*            +    |              +          |
*  jt_ichg_l-+~~~~+   Charge area           |
*            |    +              +          |
*         0--+----+--------------+----------+--- Temp
*            0   jt_temp_l      jt_temp_h   55
*/
};

#define RICOH_REG(_id, _name, _sname)				\
{								\
	.id		= RICOH619_ID_##_id,			\
	.name		= "ricoh61x-regulator",			\
	.platform_data	= &pdata_##_name##_##_sname,		\
}

static struct regulator_consumer_supply ricoh619_dc1_supply_0[] = {
	REGULATOR_SUPPLY("VDDSOC", NULL),
};
static struct regulator_consumer_supply ricoh619_dc2_supply_0[] = {
	REGULATOR_SUPPLY("vdd_core1_3v3", NULL),
};
static struct regulator_consumer_supply ricoh619_dc3_supply_0[] = {
	REGULATOR_SUPPLY("VDDCORE", NULL),
};
static struct regulator_consumer_supply ricoh619_dc4_supply_0[] = {
	REGULATOR_SUPPLY("vdd_core4_1v2", NULL),
};
static struct regulator_consumer_supply ricoh619_dc5_supply_0[] = {
	REGULATOR_SUPPLY("vdd_core4_1v8", NULL),
};
static struct regulator_consumer_supply ricoh619_ldo1_supply_0[] = {
	REGULATOR_SUPPLY("vdd_ir_3v3", NULL),
};
static struct regulator_consumer_supply ricoh619_ldo2_supply_0[] = {
};
static struct regulator_consumer_supply ricoh619_ldo3_supply_0[] = {
	REGULATOR_SUPPLY("vdd_core5_1v2", NULL),
};
static struct regulator_consumer_supply ricoh619_ldo4_supply_0[] = {
};
static struct regulator_consumer_supply ricoh619_ldo5_supply_0[] = {
	REGULATOR_SUPPLY("vdd_spd_3v3", NULL),
//	REGULATOR_SUPPLY("vmmc", "sdhci-esdhc-imx.3"),
};
static struct regulator_consumer_supply ricoh619_ldo6_supply_0[] = {
	REGULATOR_SUPPLY("vdd_ddr_0v6", NULL),
};
static struct regulator_consumer_supply ricoh619_ldo7_supply_0[] = {
	REGULATOR_SUPPLY("vdd_pwm", "0-0007"),
	REGULATOR_SUPPLY("vdd_fl_0_pwm", "0-0043"),
	REGULATOR_SUPPLY("vdd_fl_pwm", "2-0043"),
	REGULATOR_SUPPLY("vdd_fl_lm3630a", "0-0036"),
};
static struct regulator_consumer_supply ricoh619_ldo8_supply_0[] = {
	REGULATOR_SUPPLY("ldo_1v8", NULL),
};
static struct regulator_consumer_supply ricoh619_ldo9_supply_0[] = {
};
static struct regulator_consumer_supply ricoh619_ldo10_supply_0[] = {
};
static struct regulator_consumer_supply ricoh619_ldortc1_supply_0[] = {
	REGULATOR_SUPPLY("vdd_rtc_3v3", NULL),
};
static struct regulator_consumer_supply ricoh619_ldortc2_supply_0[] = {
};

#define RICOH_PDATA_INIT(_name, _sname, _minmv, _maxmv, _supply_reg, _always_on, \
	_boot_on, _apply_uv, _init_uV, _init_enable, _init_apply, _flags,      \
	_ext_contol, _sleep_mV) \
	static struct ricoh619_regulator_platform_data pdata_##_name##_##_sname = \
	{								\
		.regulator = {						\
			.constraints = {				\
				.min_uV = (_minmv)*1000,		\
				.max_uV = (_maxmv)*1000,		\
				.valid_modes_mask = (REGULATOR_MODE_NORMAL |  \
						     REGULATOR_MODE_STANDBY), \
				.valid_ops_mask = (REGULATOR_CHANGE_MODE |    \
						   REGULATOR_CHANGE_STATUS |  \
						   REGULATOR_CHANGE_VOLTAGE), \
				.always_on = _always_on,		\
				.boot_on = _boot_on,			\
				.apply_uV = _apply_uv,			\
			},						\
			.num_consumer_supplies =			\
				ARRAY_SIZE(ricoh619_##_name##_supply_##_sname),	\
			.consumer_supplies = ricoh619_##_name##_supply_##_sname, \
			.supply_regulator = _supply_reg,		\
		},							\
		.init_uV =  _init_uV * 1000,				\
		.init_enable = _init_enable,				\
		.init_apply = _init_apply,				\
		.sleep_uV = (_sleep_mV)*1000,				\
		.flags = _flags,					\
		.ext_pwr_req = _ext_contol,				\
	}

RICOH_PDATA_INIT(dc1, 0,	950,  1500, 0, 1, 1, 0, 1400, 1, 1, 0, 0, 950);	// Core2_1V3
RICOH_PDATA_INIT(dc2, 0,	0,  0, 0, 1, 1, 0, -1, 1, 1, 0, 0, 0);	// Core3_3V3
RICOH_PDATA_INIT(dc3, 0,	950,  1500, 0, 1, 1, 0, 1425, 1, 1, 0, 0, 950);	// Core2_1V3_ARM
RICOH_PDATA_INIT(dc4, 0,	0,  0, 0, 1, 1, 0, -1, 1, 1, 0, 0, 0);	// Core4_1V2
RICOH_PDATA_INIT(dc5, 0,	0,  0, 0, 1, 1, 0, -1, 1, 1, 0, 0, 0);	// Core4_1V8

RICOH_PDATA_INIT(ldo1, 0,	0, 0, 0, 1, 1, 0, -1, 1, 1, 0, 0, 0);		// IR_3V3
RICOH_PDATA_INIT(ldo2, 0,	0, 0, 0, 1, 1, 0, -1, 1, 1, 0, 0, 0);		// Core1_3V3*
RICOH_PDATA_INIT(ldo3, 0,	0, 0, 0, 1, 1, 0, -1, 1, 1, 0, 0, 0);		// Core5_1V2
RICOH_PDATA_INIT(ldo4, 0,	0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0);		// Reserved
RICOH_PDATA_INIT(ldo5, 0,	0, 0, 0, 1, 1, 0, -1, 1, 1, 0, 0, 0);		// SPD_3V3
RICOH_PDATA_INIT(ldo6, 0,	0, 0, 0, 1, 1, 0, -1, 1, 1, 0, 0, 0);		// DDR_0V6
RICOH_PDATA_INIT(ldo7, 0,	0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0); 		// VDD_PWM
RICOH_PDATA_INIT(ldo8, 0,	0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0);		// ldo_1v8
//RICOH_PDATA_INIT(ldo8, 0,	3300, 3300, 0, 1, 1, 0, 3300, 1, 1, 0, 0, 3300);		// ldo_1v8 output 3V3
RICOH_PDATA_INIT(ldo9, 0,	0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0);		// Reserved
RICOH_PDATA_INIT(ldo10, 0,	0, 0, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0);		// Reserved
RICOH_PDATA_INIT(ldortc1, 0,0, 0, 0, 1, 1, 0, -1, 1, 1, -1, -1, -1);
RICOH_PDATA_INIT(ldortc2, 0,0, 0, 0, 0, 0, 0, -1, 0, 1, -1, -1, -1);

#define RICOH619_DEV_REG 		\
	RICOH_REG(DC1, dc1, 0),		\
	RICOH_REG(DC2, dc2, 0),		\
	RICOH_REG(DC3, dc3, 0),		\
	RICOH_REG(DC4, dc4, 0),		\
	RICOH_REG(DC5, dc5, 0),		\
	RICOH_REG(LDO1, ldo1, 0),	\
	RICOH_REG(LDO2, ldo2, 0),	\
	RICOH_REG(LDO3, ldo3, 0),	\
	RICOH_REG(LDO4, ldo4, 0),	\
	RICOH_REG(LDO5, ldo5, 0),	\
	RICOH_REG(LDO6, ldo6, 0),	\
	RICOH_REG(LDO7, ldo7, 0),	\
	RICOH_REG(LDO8, ldo8, 0),	\
	RICOH_REG(LDO9, ldo9, 0),	\
	RICOH_REG(LDO10, ldo10, 0),	\
	RICOH_REG(LDORTC1, ldortc1, 0),	\
	RICOH_REG(LDORTC2, ldortc2, 0)

static struct	ricoh619_subdev_info ricoh619_sub_data[] = {
	RICOH619_DEV_REG,
	{
		.name           = "ricoh619-battery",
		.id				= -1,
		.platform_data = &ricoh_battery_data,
	},
	{
		.name           = "rtc_ricoh619",
		.id				= 0,
		.platform_data = &ricoh_rtc_data,
	},
};

#if 0
static struct	ricoh619_subdev_info ricoh619_sub_data_no_bat[] = {
	RICOH619_DEV_REG,
	{
		.name           = "rtc_ricoh619",
		.id				= 0,
		.platform_data = &ricoh_rtc_data,
	},
};
#endif

#define RICOH_GPIO_INIT(_init_apply, _output_mode, _output_val, _led_mode, _led_func) \
	{									\
		.output_mode_en = _output_mode,	\
		.output_val		= _output_val,	\
		.init_apply		= _init_apply,	\
		.led_mode		= _led_mode,	\
		.led_func		= _led_func,	\
	}
static struct ricoh619_gpio_init_data ricoh_gpio_data[] = {
	RICOH_GPIO_INIT(false, false, 0, 0, 0),
	RICOH_GPIO_INIT(false, false, 0, 0, 0),
	RICOH_GPIO_INIT(false, false, 0, 0, 0),
	RICOH_GPIO_INIT(false, false, 0, 0, 0),
};

static struct ricoh619_platform_data ntx_ricoh_data = {
	.num_subdevs = ARRAY_SIZE(ricoh619_sub_data),
	.subdevs = ricoh619_sub_data,
	.gpio_base		= 7*32,
	.gpio_init_data		= ricoh_gpio_data,
	.num_gpioinit_data	= ARRAY_SIZE(ricoh_gpio_data),
	.enable_shutdown_pin 	= true,
};

static struct i2c_board_info i2c_sysmp_ricoh619_binfo = {
	.type = "ricoh619",
	.addr = 0x32,
	.platform_data = &ntx_ricoh_data,
};

static struct imxi2c_platform_data mx6q_ntx_i2c_data = {
	.bitrate = 400000,
};

static struct imxi2c_platform_data mx6q_ntx_i2c_pmu_data = {
	.bitrate = 100000,
};

static struct i2c_board_info mxc_i2c0_board_info[] __initdata = {
};

static struct i2c_board_info mxc_i2c1_board_info[] __initdata = {
};

static struct i2c_board_info mxc_i2c2_board_info[] __initdata = {
};

static int epdc_get_pins(void)
{
	int ret = 0;

	/* Claim GPIOs for EPDC pins - used during power up/down */
	ret |= gpio_request(ntx_EPDC_SDDO_0, "epdc_d0");
	ret |= gpio_request(ntx_EPDC_SDDO_1, "epdc_d1");
	ret |= gpio_request(ntx_EPDC_SDDO_2, "epdc_d2");
	ret |= gpio_request(ntx_EPDC_SDDO_3, "epdc_d3");
	ret |= gpio_request(ntx_EPDC_SDDO_4, "epdc_d4");
	ret |= gpio_request(ntx_EPDC_SDDO_5, "epdc_d5");
	ret |= gpio_request(ntx_EPDC_SDDO_6, "epdc_d6");
	ret |= gpio_request(ntx_EPDC_SDDO_7, "epdc_d7");
	ret |= gpio_request(ntx_EPDC_SDDO_8, "epdc_d8");
	ret |= gpio_request(ntx_EPDC_SDDO_9, "epdc_d9");
	ret |= gpio_request(ntx_EPDC_SDDO_10, "epdc_d10");
	ret |= gpio_request(ntx_EPDC_SDDO_11, "epdc_d11");
	ret |= gpio_request(ntx_EPDC_SDDO_12, "epdc_d12");
	ret |= gpio_request(ntx_EPDC_SDDO_13, "epdc_d13");
	ret |= gpio_request(ntx_EPDC_SDDO_14, "epdc_d14");
	ret |= gpio_request(ntx_EPDC_SDDO_15, "epdc_d15");
	ret |= gpio_request(ntx_EPDC_GDCLK, "epdc_gdclk");
	ret |= gpio_request(ntx_EPDC_GDSP, "epdc_gdsp");
	ret |= gpio_request(ntx_EPDC_GDOE, "epdc_gdoe");
	ret |= gpio_request(ntx_EPDC_GDRL, "epdc_gdrl");
	ret |= gpio_request(ntx_EPDC_SDCLK, "epdc_sdclk");
	ret |= gpio_request(ntx_EPDC_SDOE, "epdc_sdoe");
	ret |= gpio_request(ntx_EPDC_SDLE, "epdc_sdle");
	ret |= gpio_request(ntx_EPDC_SDSHR, "epdc_sdshr");
	ret |= gpio_request(ntx_EPDC_BDR0, "epdc_bdr0");
	ret |= gpio_request(ntx_EPDC_SDCE0, "epdc_sdce0");
	ret |= gpio_request(ntx_EPDC_SDCE1, "epdc_sdce1");
	//ret |= gpio_request(ntx_EPDC_SDCE2, "epdc_sdce2");

	return ret;
}

static void epdc_put_pins(void)
{
	gpio_free(ntx_EPDC_SDDO_0);
	gpio_free(ntx_EPDC_SDDO_1);
	gpio_free(ntx_EPDC_SDDO_2);
	gpio_free(ntx_EPDC_SDDO_3);
	gpio_free(ntx_EPDC_SDDO_4);
	gpio_free(ntx_EPDC_SDDO_5);
	gpio_free(ntx_EPDC_SDDO_6);
	gpio_free(ntx_EPDC_SDDO_7);
	gpio_free(ntx_EPDC_SDDO_8);
	gpio_free(ntx_EPDC_SDDO_9);
	gpio_free(ntx_EPDC_SDDO_10);
	gpio_free(ntx_EPDC_SDDO_11);
	gpio_free(ntx_EPDC_SDDO_12);
	gpio_free(ntx_EPDC_SDDO_13);
	gpio_free(ntx_EPDC_SDDO_14);
	gpio_free(ntx_EPDC_SDDO_15);
	gpio_free(ntx_EPDC_GDCLK);
	gpio_free(ntx_EPDC_GDSP);
	gpio_free(ntx_EPDC_GDOE);
	gpio_free(ntx_EPDC_GDRL);
	gpio_free(ntx_EPDC_SDCLK);
	gpio_free(ntx_EPDC_SDOE);
	gpio_free(ntx_EPDC_SDLE);
	gpio_free(ntx_EPDC_SDSHR);
	gpio_free(ntx_EPDC_BDR0);
	gpio_free(ntx_EPDC_SDCE0);
	gpio_free(ntx_EPDC_SDCE1);
	//gpio_free(ntx_EPDC_SDCE2);
}

static void epdc_enable_pins(void)
{
	/* Configure MUX settings to enable EPDC use */
	mxc_iomux_v3_setup_multiple_pads(mx6dl_ntx_epdc_enable_pads, \
				ARRAY_SIZE(mx6dl_ntx_epdc_enable_pads));

	gpio_direction_input(ntx_EPDC_SDDO_0);
	gpio_direction_input(ntx_EPDC_SDDO_1);
	gpio_direction_input(ntx_EPDC_SDDO_2);
	gpio_direction_input(ntx_EPDC_SDDO_3);
	gpio_direction_input(ntx_EPDC_SDDO_4);
	gpio_direction_input(ntx_EPDC_SDDO_5);
	gpio_direction_input(ntx_EPDC_SDDO_6);
	gpio_direction_input(ntx_EPDC_SDDO_7);

	gpio_direction_input(ntx_EPDC_SDDO_8);
	gpio_direction_input(ntx_EPDC_SDDO_9);
	gpio_direction_input(ntx_EPDC_SDDO_10);
	gpio_direction_input(ntx_EPDC_SDDO_11);
	gpio_direction_input(ntx_EPDC_SDDO_12);
	gpio_direction_input(ntx_EPDC_SDDO_13);
	gpio_direction_input(ntx_EPDC_SDDO_14);
	gpio_direction_input(ntx_EPDC_SDDO_15);


	gpio_direction_input(ntx_EPDC_GDCLK);
	gpio_direction_input(ntx_EPDC_GDSP);
	gpio_direction_input(ntx_EPDC_GDOE);
	gpio_direction_input(ntx_EPDC_GDRL);
	gpio_direction_input(ntx_EPDC_SDCLK);
	gpio_direction_input(ntx_EPDC_SDOE);
	gpio_direction_input(ntx_EPDC_SDLE);
	gpio_direction_input(ntx_EPDC_SDSHR);
	gpio_direction_input(ntx_EPDC_BDR0);
	gpio_direction_input(ntx_EPDC_SDCE0);
	gpio_direction_input(ntx_EPDC_SDCE1);
	//gpio_direction_input(ntx_EPDC_SDCE2);
}

static void epdc_disable_pins(void)
{
	/* Configure MUX settings for EPDC pins to
	 * GPIO and drive to 0. */
	mxc_iomux_v3_setup_multiple_pads(mx6dl_ntx_epdc_disable_pads, \
				ARRAY_SIZE(mx6dl_ntx_epdc_disable_pads));

	gpio_direction_output(ntx_EPDC_SDDO_0, 0);
	gpio_direction_output(ntx_EPDC_SDDO_1, 0);
	gpio_direction_output(ntx_EPDC_SDDO_2, 0);
	gpio_direction_output(ntx_EPDC_SDDO_3, 0);
	gpio_direction_output(ntx_EPDC_SDDO_4, 0);
	gpio_direction_output(ntx_EPDC_SDDO_5, 0);
	gpio_direction_output(ntx_EPDC_SDDO_6, 0);
	gpio_direction_output(ntx_EPDC_SDDO_7, 0);

	gpio_direction_output(ntx_EPDC_SDDO_8, 0);
	gpio_direction_output(ntx_EPDC_SDDO_9, 0);
	gpio_direction_output(ntx_EPDC_SDDO_10, 0);
	gpio_direction_output(ntx_EPDC_SDDO_11, 0);
	gpio_direction_output(ntx_EPDC_SDDO_12, 0);
	gpio_direction_output(ntx_EPDC_SDDO_13, 0);
	gpio_direction_output(ntx_EPDC_SDDO_14, 0);
	gpio_direction_output(ntx_EPDC_SDDO_15, 0);

	gpio_direction_output(ntx_EPDC_GDCLK, 0);
	gpio_direction_output(ntx_EPDC_GDSP, 0);
	gpio_direction_output(ntx_EPDC_GDOE, 0);
	gpio_direction_output(ntx_EPDC_GDRL, 0);
	gpio_direction_output(ntx_EPDC_SDCLK, 0);
	gpio_direction_output(ntx_EPDC_SDOE, 0);
	gpio_direction_output(ntx_EPDC_SDLE, 0);
	gpio_direction_output(ntx_EPDC_SDSHR, 0);
	gpio_direction_output(ntx_EPDC_BDR0, 0);
	gpio_direction_output(ntx_EPDC_SDCE0, 0);
	gpio_direction_output(ntx_EPDC_SDCE1, 0);
	//gpio_direction_output(ntx_EPDC_SDCE2, 0);
}

#include "ntx_epd_modes.h"

static struct imx_epdc_fb_platform_data epdc_data = {
	.epdc_mode = panel_modes,
	.num_modes = ARRAY_SIZE(panel_modes),
	.get_pins = epdc_get_pins,
	.put_pins = epdc_put_pins,
	.enable_pins = epdc_enable_pins,
	.disable_pins = epdc_disable_pins,
};

typedef void (*usb_insert_handler) (char inserted);
usb_insert_handler mxc_misc_report_usb;

static void mxc_register_usb_plug(void* pk_cb)
{
//	pmic_event_callback_t usb_plug_event;

//	usb_plug_event.param = (void *)1;
//	usb_plug_event.func = (void *)pk_cb;
//	pmic_event_subscribe(EVENT_VBUSVI, usb_plug_event);
	if (gIsCustomerUi)
		mxc_misc_report_usb = pk_cb;
	DBG_MSG("%s(),pk_cb=%p\n",__FUNCTION__,pk_cb);

}

static void imx6q_ntx_usbotg_vbus(bool on)
{
}

static void __init imx6q_ntx_init_usb(void)
{

	imx_otg_base = MX6_IO_ADDRESS(MX6Q_USB_OTG_BASE_ADDR);
	/* disable external charger detect,
	 * or it will affect signal quality at dp .
	 */
	mx6_set_otghost_vbus_func(imx6q_ntx_usbotg_vbus);
}

static struct viv_gpu_platform_data imx6q_gpu_pdata __initdata = {
	.reserved_mem_size = SZ_128M + SZ_64M - SZ_16M,
};

static struct imx_asrc_platform_data imx_asrc_data = {
	.channel_bits = 4,
	.clk_map_ver = 2,
};

static struct ipuv3_fb_platform_data ntx_fb_data[] = {
	{ /*fb0*/
	.disp_dev = "ldb",
	.interface_pix_fmt = IPU_PIX_FMT_RGB666,
	.mode_str = "LDB-XGA",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	}, {
	.disp_dev = "hdmi",
	.interface_pix_fmt = IPU_PIX_FMT_RGB24,
	.mode_str = "1920x1080M@60",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	}, {
	.disp_dev = "ldb",
	.interface_pix_fmt = IPU_PIX_FMT_RGB666,
	.mode_str = "LDB-XGA",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	},
};

/* On mx6x ntx board i2c2 iomux with hdmi ddc,
 * the pins default work at i2c2 function,
 when hdcp enable, the pins should work at ddc function */

static struct fsl_mxc_ldb_platform_data ldb_data = {
	.ipu_id = 1,
	.disp_id = 1,
	.ext_ref = 1,
	.mode = LDB_SEP1,
	.sec_ipu_id = 1,
	.sec_disp_id = 0,
};

static struct imx_ipuv3_platform_data ipu_data[] = {
	{
	.rev = 4,
	.csi_clk[0] = "clko_clk",
	.bypass_reset = false,
	}, {
	.rev = 4,
	.csi_clk[0] = "clko_clk",
	.bypass_reset = false,
	},
};

#if defined(CONFIG_ION)
static struct ion_platform_data imx_ion_data = {
	.nr = 1,
	.heaps = {
		{
		.id = 0,
		.type = ION_HEAP_TYPE_CARVEOUT,
		.name = "vpu_ion",
		.size = SZ_64M,
		},
	},
};
#endif

struct imx_vout_mem {
	resource_size_t res_mbase;
	resource_size_t res_msize;
};

static struct imx_vout_mem vout_mem __initdata = {
	.res_msize = SZ_128M,
};

extern void ntx_gpio_suspend (void);
extern void ntx_gpio_resume (void);

static void ntx_suspend_enter(void)
{
	/* suspend preparation */
	ntx_gpio_suspend ();
}

static void ntx_suspend_exit(void)
{
	/* resume restore */
	ntx_gpio_resume ();
}
static const struct pm_platform_data mx6q_ntx_pm_data __initconst = {
	.name = "imx_pm",
	.suspend_enter = ntx_suspend_enter,
	.suspend_exit = ntx_suspend_exit,
};

static struct regulator_consumer_supply ntx_vmmc_consumers[] = {
	REGULATOR_SUPPLY("vmmc", "sdhci-esdhc-imx.1"),
	REGULATOR_SUPPLY("vmmc", "sdhci-esdhc-imx.2"),
	REGULATOR_SUPPLY("vmmc", "sdhci-esdhc-imx.3"),
};

static struct regulator_init_data ntx_vmmc_init = {
	.num_consumer_supplies = ARRAY_SIZE(ntx_vmmc_consumers),
	.consumer_supplies = ntx_vmmc_consumers,
};

static struct fixed_voltage_config ntx_vmmc_reg_config = {
	.supply_name		= "vmmc",
	.microvolts		= 3300000,
	.gpio			= -1,
	.init_data		= &ntx_vmmc_init,
};

static struct platform_device ntx_vmmc_reg_devices = {
	.name	= "reg-fixed-voltage",
	.id	= 3,
	.dev	= {
		.platform_data = &ntx_vmmc_reg_config,
	},
};

volatile unsigned gMX6SL_PWR_SW;

#if defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
#define GPIO_BUTTON(gpio_num, ev_code, act_low, descr, wake, debounce)	\
{								\
	.gpio		= gpio_num,				\
	.type		= EV_KEY,				\
	.code		= ev_code,				\
	.active_low	= act_low,				\
	.desc		= "btn " descr,				\
	.wakeup		= wake,					\
	.debounce_interval = debounce,				\
}

static struct gpio_keys_button ntx_buttons[] = {
	GPIO_BUTTON(IMX_GPIO_NR(4, 9), KEY_POWER, 1, "power", 1, 1),
};

static struct gpio_keys_button gpio_keys_RETURN_HOME_MENU[] = {
#ifdef CONFIG_ANDROID//[
	GPIO_BUTTON(IMX_GPIO_NR(1, 12), KEY_HOME, 1, "home", 1,1),			// KEY2
#else //][!CONFIG_ANDROID
	GPIO_BUTTON(IMX_GPIO_NR(1, 12), 61, 1, "home", 1,1),			// KEY2
#endif //] CONFIG_ANDROID
	GPIO_BUTTON(IMX_GPIO_NR(1, 10), KEY_MENU, 1, "menu", 1,1),			// KEY1
	GPIO_BUTTON(IMX_GPIO_NR(1, 2), KEY_ESC, 1, "return", 1,1),			// KEY3
//#ifdef CONFIG_ANDROID //[
	GPIO_BUTTON(IMX_GPIO_NR(4, 9), KEY_POWER, 1, "power", 1, 1),
//#endif //]CONFIG_ANDROID
};

static struct gpio_keys_platform_data ntx_gpio_key_data = {
	.buttons	= ntx_buttons,
	.nbuttons	= ARRAY_SIZE(ntx_buttons),
};

static struct platform_device imx6q_button_device = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources  = 0,
	.dev		= {
		.platform_data = &ntx_gpio_key_data,
	}
};

static void __init imx6q_add_device_buttons(void)
{
	int i;


	switch(gptHWCFG->m_val.bKeyPad) { //key pad define through bKeyPad in hwconfig
		case 17: // RETURN+HOME+MENU
			ntx_gpio_key_data.buttons = gpio_keys_RETURN_HOME_MENU;
			ntx_gpio_key_data.nbuttons = ARRAY_SIZE(gpio_keys_RETURN_HOME_MENU);
			// setup keys I/O mux/pad .
			mxc_iomux_v3_setup_pad(MX6DL_PAD_SD2_CLK__GPIO_1_10_KEYIPU);// KEY1
			mxc_iomux_v3_setup_pad(MX6DL_PAD_SD2_DAT3__GPIO_1_12_KEYIPU);// KEY2
			mxc_iomux_v3_setup_pad(MX6DL_PAD_GPIO_2__GPIO_1_2_KEYIPU);// KEY3
			break;
		default :
			break;
	}


	for(i=0;i<ntx_gpio_key_data.nbuttons;i++) {
		if(0==strcmp(ntx_gpio_key_data.buttons[i].desc,"btn power")) {
			ntx_gpio_key_data.buttons[i].gpio = gMX6SL_PWR_SW;
			if(0==gptHWCFG->m_val.bUIStyle) {
				printk("%s(),Ebrmain remote power key in gpio keys \n",__FUNCTION__);
				ntx_gpio_key_data.nbuttons-=1;
			}
		}
	}
	platform_device_register(&imx6q_button_device);
}
#else
static void __init imx6q_add_device_buttons(void) {}
#endif




static struct platform_device ntx_light_ldm = {
	.name = "pmic_light",
	.id = 1,
};


static struct mxc_dvfs_platform_data ntx_dvfscore_data = {
#ifdef CONFIG_MX6_INTER_LDO_BYPASS
	.reg_id = "VDDCORE",
	.soc_id	= "VDDSOC",
#else
	.reg_id = "cpu_vddgp",
	.soc_id = "cpu_vddsoc",
	.pu_id = "cpu_vddvpu",
#endif
	.clk1_id = "cpu_clk",
	.clk2_id = "gpc_dvfs_clk",
	.gpc_cntr_offset = MXC_GPC_CNTR_OFFSET,
	.ccm_cdcr_offset = MXC_CCM_CDCR_OFFSET,
	.ccm_cacrr_offset = MXC_CCM_CACRR_OFFSET,
	.ccm_cdhipr_offset = MXC_CCM_CDHIPR_OFFSET,
	.prediv_mask = 0x1F800,
	.prediv_offset = 11,
	.prediv_val = 3,
	.div3ck_mask = 0xE0000000,
	.div3ck_offset = 29,
	.div3ck_val = 2,
	.emac_val = 0x08,
	.upthr_val = 25,
	.dnthr_val = 9,
	.pncthr_val = 33,
	.upcnt_val = 10,
	.dncnt_val = 10,
	.delay_time = 80,
};

static void __init fixup_mxc_board(struct machine_desc *desc, struct tag *tags,
				   char **cmdline, struct meminfo *mi)
{
}



void *g_wifi_sd_host;
irq_handler_t g_cd_irq;

void ntx_register_wifi_cd (irq_handler_t handler, void *data)
{
	printk ("[%s-%d] register g_cd_irq \n",__func__,__LINE__);
	g_wifi_sd_host = data;
	g_cd_irq = handler;
}


static DEFINE_MUTEX(ntx_wifi_power_mutex);
static int gi_wifi_power_status = 0;

int _ntx_get_wifi_power_status(void)
{
	int iWifiPowerStatus;

	mutex_lock(&ntx_wifi_power_mutex);
	iWifiPowerStatus = gi_wifi_power_status;
	mutex_unlock(&ntx_wifi_power_mutex);

	return iWifiPowerStatus;
}

int get_wifi_power_status(void)
{
	return (gi_wifi_power_status&1)?1:0;
}

int _ntx_wifi_power_ctrl (int isWifiEnable)
{
	int iHWID;
	int iOldStatus;

	iOldStatus = gi_wifi_power_status;
	printk("Wifi / BT power control %d\n", isWifiEnable);
    if(isWifiEnable == 0){
		gpio_direction_output (gMX6DL_WIFI_3V3,1);	// turn off Wifi_3V3_on
		msleep(10);
        gi_wifi_power_status=0;
    } 
	else {
        gpio_direction_output (gMX6DL_WIFI_3V3, 0);
        printk("Set gMX6DL_WIFI_3V3 to low \n");
		
        if (isWifiEnable & 0x02) {
            printk("set uart5 pins as uart function\n");
            mxc_iomux_v3_setup_multiple_pads(mx6dl_ntx_uart5_pads, ARRAY_SIZE(mx6dl_ntx_uart5_pads));
            gpio_direction_output (gMX6DL_BT_EN, 1);
            gi_wifi_power_status |= 0x02;
        }

        if (isWifiEnable & 0x01) {
            gpio_free (MX6DL_SD4_CLK );
            gpio_free (MX6DL_SD4_CMD );
            gpio_free (MX6DL_SD4_DAT0);
            gpio_free (MX6DL_SD4_DAT1);
            gpio_free (MX6DL_SD4_DAT2);
            gpio_free (MX6DL_SD4_DAT3);
            mxc_iomux_v3_setup_multiple_pads(mx6dl_ntx_sd4_wifi_pads, ARRAY_SIZE(mx6dl_ntx_sd4_wifi_pads));
            gpio_direction_input (gMX6DL_WIFI_INT);

            if (iOldStatus & 0x01) {
                printk ("Wifi already on.\n");
            }
            if(gMX6DL_WIFI_RST!=(unsigned int)(-1)) {
                gpio_direction_output (gMX6DL_WIFI_RST, 1);	// turn on wifi_RST
            }
            gi_wifi_power_status |= 0x01;
        }
        msleep(30);

    }
    if (g_cd_irq) {
		if ((iOldStatus & 0x01) != (isWifiEnable & 1)) {		// call mmc detect if wifi status changed.
			struct sdhci_host *host;
			host = (struct sdhci_host*)g_wifi_sd_host;
			printk("[%s-%d] registered.\n",__func__,__LINE__);
			mmc_detect_change(host->mmc, msecs_to_jiffies(500));
			msleep(600);
		}
	}
	else {
		printk("[%s-%d] not registered.\n",__func__,__LINE__);
	}
    if((isWifiEnable & 1) == 0){
        gi_wifi_power_status &= ~0x01;
		if(gMX6DL_WIFI_RST!=(unsigned int)(-1)) {
			gpio_direction_output (gMX6DL_WIFI_RST, 0);
		}
        mxc_iomux_v3_setup_multiple_pads(mx6dl_ntx_sd4_gpio_pads, ARRAY_SIZE(mx6dl_ntx_sd4_gpio_pads));
        gpio_request (MX6DL_SD4_CLK	, "MX6DL_SD4_CLK" );
		gpio_request (MX6DL_SD4_CMD	, "MX6DL_SD4_CMD" );
		gpio_request (MX6DL_SD4_DAT0, "MX6DL_SD4_DAT0");
		gpio_request (MX6DL_SD4_DAT1, "MX6DL_SD4_DAT1");
		gpio_request (MX6DL_SD4_DAT2, "MX6DL_SD4_DAT2");
		gpio_request (MX6DL_SD4_DAT3, "MX6DL_SD4_DAT3");
		gpio_direction_output (MX6DL_SD4_CLK , 0);
		gpio_direction_output (MX6DL_SD4_CMD , 0);
		gpio_direction_output (MX6DL_SD4_DAT0, 0);
		gpio_direction_output (MX6DL_SD4_DAT1, 0);
		gpio_direction_output (MX6DL_SD4_DAT2, 0);
		gpio_direction_output (MX6DL_SD4_DAT3, 0);
    }
    if((isWifiEnable & 2) == 0){
        gi_wifi_power_status &= ~0x02;
        mxc_iomux_v3_setup_multiple_pads(mx6dl_ntx_uart5_gpio_pads, ARRAY_SIZE(mx6dl_ntx_uart5_gpio_pads));
        gpio_direction_output (gMX6DL_BT_EN, 0);
	}
    printk("%s() end.\n",__FUNCTION__);
	return iOldStatus;
}

void ntx_wifi_power_ctrl(int iIsWifiEnable)
{
	mutex_lock(&ntx_wifi_power_mutex);
	if (11 == gptHWCFG->m_val.bWifi || 12 == gptHWCFG->m_val.bWifi || 14 == gptHWCFG->m_val.bWifi) { 
		if (iIsWifiEnable)
			_ntx_wifi_power_ctrl(gi_wifi_power_status | 1);
		else
			_ntx_wifi_power_ctrl(gi_wifi_power_status & ~1);
	} else {
		_ntx_wifi_power_ctrl(iIsWifiEnable);
	}
	mutex_unlock(&ntx_wifi_power_mutex);
}

void ntx_bt_power_ctrl(int iIsBTEnable)
{
	mutex_lock(&ntx_wifi_power_mutex);
	if (iIsBTEnable)
		_ntx_wifi_power_ctrl(gi_wifi_power_status | 2);
	else
		_ntx_wifi_power_ctrl(gi_wifi_power_status & ~2);
	mutex_unlock(&ntx_wifi_power_mutex);
}

EXPORT_SYMBOL(ntx_wifi_power_ctrl);

static int mx6sl_bt_power_change(int enable)
{
	ntx_bt_power_ctrl(enable);
	return 0;
}

static struct platform_device mxc_bt_rfkill = {
	.name = "mxc_bt_rfkill",
};

static struct imx_bt_rfkill_platform_data mxc_bt_rfkill_data = {
	.power_change = mx6sl_bt_power_change,
};

void ntx_ite8951_power(int iIsON)
{
	if(14==gptHWCFG->m_val.bDisplayCtrl) {
	}
}

void ntx_lte_power(int iIsON)
{
	if(4==gptHWCFG->m_val.bMobile) {
		//SIM7100
	}
}

void ntx_lte_reset(void)
{
	if(4==gptHWCFG->m_val.bMobile) {
		//SIM7100
	}
}

void ntx_lte_flightmode(int iIsON)
{
	if(4==gptHWCFG->m_val.bMobile) {
		//SIM7100
	}
}

volatile unsigned gMX6SL_ON_LED;
volatile unsigned gMX6SL_CHG_LED;
volatile unsigned gMX6SL_ACT_LED;
volatile unsigned gMX6SL_IR_TOUCH_INT;
volatile unsigned gMX6SL_IR_TOUCH_RST;
volatile unsigned gMX6SL_NTX_ACIN_PG;
volatile unsigned gMX6SL_FL_PWR_EN;
volatile unsigned gMX6SL_FL_W_H_EN;
volatile unsigned gMX6SL_FL_PWR_EN;
volatile unsigned gMX6SL_NTX_CHG;
volatile int giISD_3V3_ON_Ctrl = -1;
volatile unsigned gMX6SL_WIFI_INT;

void ntx_wacom_reset(bool on) {
	gpio_direction_output (MX6DL_WACOM_RST, on);
}

int ntx_check_suspend (void)
{
	if(0!=gptHWCFG->m_val.bTouchCtrl) {
		if((17==gptHWCFG->m_val.bTouchCtrl||18==gptHWCFG->m_val.bTouchCtrl) && gSleep_Mode_Suspend) {
			// Goodix( before enter sleep mode ,  gMX6SL_IR_TOUCH_INT must be set low) Reverse the  judgment
			return gpio_get_value(gMX6SL_IR_TOUCH_INT)?1:0;
		}
		return gpio_get_value(gMX6SL_IR_TOUCH_INT)?0:1;
	}
	else {
		return 0;
	}
}

static void ntx_gpio_init(void)
{
	gMX6SL_PWR_SW = IMX_GPIO_NR(4, 9);
	if(0==gptHWCFG->m_val.bUIStyle) {
		gpio_request (gMX6SL_PWR_SW, "MX6SL_PWR_SW");
		gpio_direction_input (gMX6SL_PWR_SW);
	}

	gMX6SL_IR_TOUCH_INT = IMX_GPIO_NR(1, 14);
	gMX6SL_IR_TOUCH_RST = IMX_GPIO_NR(1, 15);

	gpio_request (gMX6SL_IR_TOUCH_INT, "MX6SL_IR_TOUCH_INT");
	gpio_direction_input (gMX6SL_IR_TOUCH_INT);

	gpio_request (gMX6SL_IR_TOUCH_RST, "MX6SL_IR_TOUCH_RST");
	gpio_direction_output (gMX6SL_IR_TOUCH_RST, 0);
	mdelay (10);
	gpio_direction_input (gMX6SL_IR_TOUCH_RST);

	gMX6SL_NTX_ACIN_PG = IMX_GPIO_NR(1, 11);
	gpio_request (gMX6SL_NTX_ACIN_PG, "MX6SL_NTX_ACIN_PG");
	gpio_direction_input (gMX6SL_NTX_ACIN_PG);

	gMX6SL_CHG_LED = IMX_GPIO_NR(4, 20);	// non-used pad instead.
	if ((77==gptHWCFG->m_val.bPCB) && (0x20 <= gptHWCFG->m_val.bPCB_REV)) {
		// EA0Q0x A2 PCBA
		gMX6SL_ACT_LED = IMX_GPIO_NR(4, 7);
		gMX6SL_ON_LED = IMX_GPIO_NR(4, 7);
		mxc_iomux_v3_setup_pad(MX6DL_PAD_EIM_D25__GPIO_3_25);
		gMX6DL_WIFI_3V3 = IMX_GPIO_NR(3, 25);
	}
	else {
		gMX6SL_ACT_LED = IMX_GPIO_NR(1, 13);
		gMX6SL_ON_LED = IMX_GPIO_NR(1, 13);
	}

	gpio_request (gMX6SL_ACT_LED, "MX6SL_ACT_LED");
	gpio_direction_input (gMX6SL_ACT_LED);
	if (gMX6SL_ACT_LED != gMX6SL_ON_LED) {
		gpio_request (gMX6SL_ON_LED, "MX6SL_ON_LED");
		gpio_direction_output (gMX6SL_ON_LED, 0);
	}

    mxc_iomux_v3_setup_pad(MX6DL_PAD_SD4_DAT6__GPIO_2_14);
	if(gMX6DL_WIFI_RST!=(unsigned int)(-1)) {
		gpio_request (gMX6DL_WIFI_RST, "MX6DL_WIFI_RST");
	}
	gpio_request (gMX6DL_WIFI_3V3, "MX6DL_WIFI_3V3");
	gpio_request (gMX6DL_WIFI_INT, "MX6DL_WIFI_INT");
	gpio_direction_input (gMX6DL_WIFI_INT);

    gMX6DL_BT_EN = IMX_GPIO_NR(1, 4);
    gpio_request (gMX6DL_BT_EN, "MX6DL_BT_EN");

    gMX6DL_BT_INT = IMX_GPIO_NR(2, 15);
    gpio_request (gMX6DL_BT_INT, "MX6DL_BT_INT");
    gpio_direction_input (gMX6DL_BT_INT);

	if(gMX6SL_CHG_LED!=gMX6SL_ON_LED) {
		gpio_request (gMX6SL_CHG_LED, "MX6SL_CHG_LED");
		//gpio_direction_input (gMX6SL_CHG_LED);
	}

		if(10==gptHWCFG->m_val.bBattery) {
			// 1200mA battery .
			if(NTXHWCFG_TST_FLAG(gptHWCFG->m_val.bEPD_Flags,1)) {
				// LPTFT .
				ricoh_battery_data.alarm_vol_mv = 3550;		// set battery critical to 3.55V
				ricoh_battery_data.type[0].fg_poff_vbat = 3600;		// set battery 0% to 3.6V
			}
			else {
				ricoh_battery_data.alarm_vol_mv = 3670;		// set battery critical to 3.76V
				ricoh_battery_data.type[0].fg_poff_vbat = 3730;		// set battery 0% to 3.73V
			}
		}
		else if(8==gptHWCFG->m_val.bBattery) {
			// 3000mA battery .
			if(77==gptHWCFG->m_val.bPCB) {
				// EA0Q0X .
				ricoh_battery_data.type[0].ch_vfchg = 4;
				ricoh_battery_data.type[0].ch_vrchg = 4;
			}
			printk(KERN_ERR " ****** battery critical value must be update (3000mA) ****** \n");
			if(NTXHWCFG_TST_FLAG(gptHWCFG->m_val.bEPD_Flags,1)) {
				// LPTFT .
				printk(KERN_ERR " ****** battery critical value (3.55V) not update ****** \n");
				ricoh_battery_data.alarm_vol_mv = 3550;		// set battery critical to 3.55V
				ricoh_battery_data.type[0].fg_poff_vbat = 3600;		// set battery 0% to 3.6V
			}
			else {
				ricoh_battery_data.alarm_vol_mv = 3670;		// set battery critical to 3.76V
				ricoh_battery_data.type[0].fg_poff_vbat = 3730;		// set battery 0% to 3.73V
			}
		}
		else if(15==gptHWCFG->m_val.bBattery) {
			// set VFCHG to 4.35V
			printk(KERN_ERR " ****** Set battery full value 4.35V ****** \n");
			ricoh_battery_data.type[0].ch_vfchg = 4;
			ricoh_battery_data.type[0].ch_vrchg = 4;
			ricoh_battery_data.type[0].jt_vfchg_h = 4;
			ricoh_battery_data.type[0].ch_vbatovset = 1;	// set VBATOVSET
			if(77==gptHWCFG->m_val.bPCB) {
				// EA0Q0X .
				printk(KERN_ERR " ****** battery critical value (3.55V) not update ****** \n");
				ricoh_battery_data.alarm_vol_mv = 3550;		// set battery critical to 3.55V
				ricoh_battery_data.type[0].fg_poff_vbat = 3600;		// set battery 0% to 3.6V
			}
		}

	if (1==gptHWCFG->m_val.bPMIC) {
		int pmu_int = IMX_GPIO_NR(4, 10);
		gpio_request(pmu_int, "PMU-int");
		gpio_direction_input (pmu_int);
		i2c_sysmp_ricoh619_binfo.irq = gpio_to_irq(pmu_int);
	}
	printk ("[%s-%d] i2c_sysmp_ricoh619_binfo.irq %d\n", __func__, __LINE__, i2c_sysmp_ricoh619_binfo.irq);
	ntx_wifi_power_ctrl (0);
}

int ntx_wifi_platform_set_power(int val) {
	if(1==val) {
		ntx_wifi_power_ctrl (1);
	}
	else {
#if 1
		ntx_wifi_power_ctrl (0);
#else
		printk("%s() : power off skipped !!\n",__FUNCTION__);
#endif
	}
	return 0;
}

static struct wifi_platform_data ntx_wifi_platform_data = {
	.set_power = ntx_wifi_platform_set_power,
//	.set_reset = ntx_wifi_platform_set_reset,
//	.set_card = ntx_wifi_platform_set_reset,
};


static struct resource ntx_bcmdhd_res[] = {
	{
		//.name = "bcmdhd_wlan_irq",
		//.name = "bcm4329_wlan_irq",
		//.start = ,
		//.end = ,
		//.flags = IORESOURCE_IRQ,
	},
};
static struct platform_device ntx_device_bcmdhd = {
	//.name           = "bcmdhd_wlan",
	.name           = "bcm4329_wlan",
	.dev            = {
		.platform_data = &ntx_wifi_platform_data,
	}
};


/*!
 * Board specific initialization.
 */
static void __init mx6_ntx_board_init(void)
{
	int i;
	struct clk *clko, *clko2;
	struct clk *new_parent;
	int rate;

	mxc_iomux_v3_setup_multiple_pads(mx6dl_ntx_pads,
			ARRAY_SIZE(mx6dl_ntx_pads));

	_parse_cmdline();

	ntx_gpio_init ();

	gp_reg_id = ntx_dvfscore_data.reg_id;
	soc_reg_id = ntx_dvfscore_data.soc_id;
#ifndef CONFIG_MX6_INTER_LDO_BYPASS
	pu_reg_id = ntx_dvfscore_data.pu_id;
	printk ("[%s-%d]...\n", __func__, __LINE__);
//	mx6_cpu_regulator_init();
#endif
	mx6q_ntx_init_uart();

	/*
	 * MX6DL/Solo only supports single IPU
	 * The following codes are used to change ipu id
	 * and display id information for MX6DL/Solo. Then
	 * register 1 IPU device and up to 2 displays for
	 * MX6DL/Solo
	 */
	if (cpu_is_mx6dl()) {
		ldb_data.ipu_id = 0;
		ldb_data.disp_id = 1;
	}

	imx6q_add_ipuv3(0, &ipu_data[0]);
	if (cpu_is_mx6q()) {
		imx6q_add_ipuv3(1, &ipu_data[1]);
		for (i = 0; i < 4 && i < ARRAY_SIZE(ntx_fb_data); i++)
			imx6q_add_ipuv3fb(i, &ntx_fb_data[i]);
	} else
		for (i = 0; i < 2 && i < ARRAY_SIZE(ntx_fb_data); i++)
			imx6q_add_ipuv3fb(i, &ntx_fb_data[i]);


//	imx6q_add_imx_caam();

	imx6q_add_imx_i2c(0, &mx6q_ntx_i2c_data);
	imx6q_add_imx_i2c(1, &mx6q_ntx_i2c_pmu_data);
	imx6q_add_imx_i2c(2, &mx6q_ntx_i2c_data);
	i2c_register_board_info(0, mxc_i2c0_board_info,
			ARRAY_SIZE(mxc_i2c0_board_info));
	i2c_register_board_info(1, mxc_i2c1_board_info,
			ARRAY_SIZE(mxc_i2c1_board_info));
	i2c_register_board_info(2, mxc_i2c2_board_info,
			ARRAY_SIZE(mxc_i2c2_board_info));

	if(1==gptHWCFG->m_val.bPMIC){ // [ Ricoh PMIC
		// RC5T619 .

		if (4==gptHWCFG->m_val.bRamType || 10==gptHWCFG->m_val.bRamType) {
			// LPDDR3/DDR3 .

			// Core4_1V2 .
			pdata_dc4_0.regulator.constraints.always_on = 0;
			pdata_dc4_0.regulator.constraints.boot_on = 0;
			pdata_dc4_0.init_enable = 0;
			pdata_dc4_0.init_apply = 1;
			// Core5_1V2
			pdata_ldo3_0.regulator.constraints.always_on = 0;
			pdata_ldo3_0.regulator.constraints.boot_on = 0;
			pdata_ldo3_0.init_enable = 0;
			pdata_ldo3_0.init_apply = 1;
			// DDR_0V6
			pdata_ldo6_0.regulator.constraints.always_on = 0;
			pdata_ldo6_0.regulator.constraints.boot_on = 0;
			pdata_ldo6_0.init_enable = 0;
			pdata_ldo6_0.init_apply = 1;
		}

		if(!NTXHWCFG_TST_FLAG(gptHWCFG->m_val.bPCB_Flags,4)) {
			// Panel is designed for low voltage .
			printk("ldo8_1v8 ouput 3v3\n");
			pdata_ldo8_0.regulator.constraints.min_uV = 3300*1000;
			pdata_ldo8_0.regulator.constraints.max_uV = 3300*1000;
			//pdata_ldo8_0.regulator.constraints.always_on = 1;
			//pdata_ldo8_0.regulator.constraints.boot_on = 1;
			pdata_ldo8_0.init_uV = 3300*1000;
			//pdata_ldo8_0.init_enable = 1;
			pdata_ldo8_0.sleep_uV = 3300*1000;
		}


		if(0==gptHWCFG->m_val.bFrontLight) {
			// FL_3V3 disabled .
			pdata_ldo7_0.regulator.constraints.always_on = 0;
			pdata_ldo7_0.regulator.constraints.boot_on = 0;
			pdata_ldo7_0.init_enable = 0;
			pdata_ldo7_0.init_apply = 1;
		}

		// LDO_1V8 not used .
		pdata_ldo8_0.regulator.constraints.always_on = 0;
		pdata_ldo8_0.regulator.constraints.boot_on = 0;
		pdata_ldo8_0.init_enable = 0;
		pdata_ldo8_0.init_apply = 1;
		pdata_dc2_0.sleep_uV = 3000*1000;	// core3_3v3
//		pdata_ldo2_0.sleep_uV = 3000*1000;	// core1_3v3 (VDD_SNVS_IN)

		// PCB is designed for low voltage .
		ntx_ricoh_data.irq_base = irq_alloc_descs (-1, 0, RICOH61x_NR_IRQS, (int)"RICOH61x");
		if (0 < ntx_ricoh_data.irq_base) {
			ricoh_battery_data.irq = ntx_ricoh_data.irq_base;
			ricoh_rtc_data.irq = ntx_ricoh_data.irq_base;
			printk ("[%s-%d] irq_alloc_descs return %d for %d RICOH61x\n",__func__, __LINE__, ntx_ricoh_data.irq_base, RICOH61x_NR_IRQS);
		}
		else {
			printk ("[%s-%d] RICOH61x irq_alloc_descs failed with %d\n",__func__, __LINE__, ntx_ricoh_data.irq_base);
		}
		if (54==gptHWCFG->m_val.bPCB) { // ED0Q1x
			ricoh_battery_data.type[0].jt_en = 1;
		}
		i2c_register_board_info(1,&i2c_sysmp_ricoh619_binfo,1);
	//	platform_device_register(&ricoh_device_rtc);
	//	pm_power_off = ricoh619_power_off;
		// I2C3 set 400kHz for faster suspending .
		mx6q_ntx_i2c_pmu_data.bitrate = 400000;
	}//] Ricoh PMIC

	if (4==gptHWCFG->m_val.bTouchType) {
		// 	i2c_register_board_info(1,&i2c_zforce_ir_touch_binfo,1);
	}
	else if (3==gptHWCFG->m_val.bTouchType) {
		// C touch type .
		if(17==gptHWCFG->m_val.bTouchCtrl || 18==gptHWCFG->m_val.bTouchCtrl) { // GTXX
			i2c_gt9xx_touch_binfo.irq = gpio_to_irq(gMX6SL_IR_TOUCH_INT);
			i2c_register_board_info(2,&i2c_gt9xx_touch_binfo ,1);
		}
		else if(14==gptHWCFG->m_val.bTouchCtrl) { // CYTT21X
			_cyttsp5_core_platform_data.irq_gpio = gMX6SL_IR_TOUCH_INT;
			_cyttsp5_core_platform_data.rst_gpio = gMX6SL_IR_TOUCH_RST;
			i2c_cyttsp_binfo.irq = gMX6SL_IR_TOUCH_INT;
			i2c_register_board_info(2,&i2c_cyttsp_binfo,1);
		}
		else { // Elan
			i2c_elan_touch_binfo.platform_data = gMX6SL_IR_TOUCH_INT;
			i2c_elan_touch_binfo.irq = gpio_to_irq(gMX6SL_IR_TOUCH_INT);
			i2c_register_board_info(2,&i2c_elan_touch_binfo ,1);
		}
	}
	else {
		printk("TouchType %d do not support yet ! no touch driver will be loaded \n",(int) gptHWCFG->m_val.bTouchType);
	}
	if(2==gptHWCFG->m_val.bTouch2Ctrl) {
		gpio_request (MX6DL_WACOM_PDCT, "WACOM_PDCT");
		gpio_direction_input (MX6DL_WACOM_PDCT);
		gpio_request (MX6DL_WACOM_FWE, "WACOM_FWE");
		gpio_direction_output (MX6DL_WACOM_FWE, 0);
		gpio_request (MX6DL_WACOM_RST, "WACOM_RST");
		ntx_wacom_reset(0);

	 	gpio_request (MX6DL_WACOM_INT, "WACOM_INT");
		gpio_direction_input (MX6DL_WACOM_INT);
		i2c_wacom_binfo.irq = gpio_to_irq(MX6DL_WACOM_INT);

		// Wacom Digitizer
		i2c_register_board_info(2,&i2c_wacom_binfo,1);
	}

	imx6q_add_anatop_thermal_imx(1, &mx6q_ntx_anatop_thermal_data);

	imx6q_add_pm_imx(0, &mx6q_ntx_pm_data);

	/* Move sd4 to first because sd4 connect to emmc.
	   Mfgtools want emmc is mmcblk0 and other sd card is mmcblk1.
	*/
	if (0 == giBootPort) {
		imx6q_add_sdhci_usdhc_imx(0, &mx6q_ntx_sd1_data);
		imx6q_add_sdhci_usdhc_imx(2, &mx6q_ntx_sd3_data);
	}
	else {
		imx6q_add_sdhci_usdhc_imx(2, &mx6q_ntx_sd3_data);
		imx6q_add_sdhci_usdhc_imx(0, &mx6q_ntx_sd1_data);
	}
	imx6q_add_sdhci_usdhc_imx(3, &mx6q_ntx_sd4_data);
#ifdef CONFIG_MXC_GPU_VIV//[
	if(2==gptHWCFG->m_val.bUIStyle||2==gptHWCFG->m_val.bGPU)
	{
		// android models needs GPU || GPU specified 'MX6SL' .
		imx_add_viv_gpu(&imx6_gpu_data, &imx6q_gpu_pdata);
	}
#endif//] CONFIG_MXC_GPU_VIV
	imx6q_ntx_init_usb();
	imx6q_add_vpu();
	platform_device_register(&ntx_vmmc_reg_devices);
	imx_asrc_data.asrc_core_clk = clk_get(NULL, "asrc_clk");
	imx_asrc_data.asrc_audio_clk = clk_get(NULL, "asrc_serial_clk");
	imx6q_add_asrc(&imx_asrc_data);

#if 0
	imx6q_add_mxc_pwm(0);
#endif
	imx6q_add_otp();
	imx6q_add_viim();
	imx6q_add_imx2_wdt(0, NULL);
	imx6q_add_dma();

	imx6q_add_dvfs_core(&ntx_dvfscore_data);
#ifdef CONFIG_MX6_INTER_LDO_BYPASS
	printk ("[%s-%d] INTER_LDO_BYPASS mode\n", __func__, __LINE__);
	enable_ldo_mode = LDO_MODE_BYPASSED;
#endif
	imx6q_add_device_buttons();

//	imx6q_add_hdmi_soc();
//	imx6q_add_hdmi_soc_dai();

	if (cpu_is_mx6dl()) {
		imx6dl_add_imx_pxp();
		imx6dl_add_imx_pxp_client();
		if (epdc_enabled) {
			__iomem void *base;
//			mxc_register_device(&max17135_sensor_device, NULL);
			imx6dl_add_imx_epdc(&epdc_data);
			/* Enable real time channel of MMDC for EPDC */
			base = ioremap(GPV1_BASE_ADDR, SZ_1M);
			__raw_writeb(0xF, base + 76 * 0x1000 + 0x100);
			__raw_writeb(0xF, base + 76 * 0x1000 + 0x104);
			iounmap(base);
		}
	}
	/*
	ret = gpio_request_array(mx6q_ntx_flexcan_gpios,
			ARRAY_SIZE(mx6q_ntx_flexcan_gpios));
	if (ret)
		pr_err("failed to request flexcan1-gpios: %d\n", ret);
	else
		imx6q_add_flexcan0(&mx6q_ntx_flexcan0_pdata);
	*/

#if 0
	clko2 = clk_get(NULL, "clko2_clk");
	if (IS_ERR(clko2))
		pr_err("can't get CLKO2 clock.\n");

	new_parent = clk_get(NULL, "osc_clk");
	if (!IS_ERR(new_parent)) {
		clk_set_parent(clko2, new_parent);
		clk_put(new_parent);
	}
	rate = clk_round_rate(clko2, 24000000);
	clk_set_rate(clko2, rate);
	clk_enable(clko2);

	/* Camera and audio use osc clock */
	clko = clk_get(NULL, "clko_clk");
	if (!IS_ERR(clko))
		clk_set_parent(clko, clko2);
#endif
	/* Register charger chips */
//	platform_device_register(&ntx_max8903_charger_1);
	imx6q_add_busfreq();

	imx6_add_armpmu();
	imx6q_add_perfmon(0);
	imx6q_add_perfmon(1);
	imx6q_add_perfmon(2);

	platform_device_register(&ntx_light_ldm);

	if(0!=gptHWCFG->m_val.bWifi) {
    		int ret ;

    		printk("%s(): \"%s\" device registed !!\n",
    				__func__,ntx_device_bcmdhd.name);

    		ntx_bcmdhd_res[0].name = "bcmdhd_wlan_irq";
    		//ntx_bcmdhd_res[0].name = "bcm4329_wlan_irq";
    //		ntx_bcmdhd_res[0].start = gpio_to_irq(gMX6SL_WIFI_INT);
    		ntx_bcmdhd_res[0].start = gMX6DL_WIFI_INT;
    		ntx_bcmdhd_res[0].end = ntx_bcmdhd_res[0].start;
    		ntx_bcmdhd_res[0].flags = IORESOURCE_IRQ;
    		ret = platform_device_add_resources(&ntx_device_bcmdhd,
    			 	ntx_bcmdhd_res, ARRAY_SIZE(ntx_bcmdhd_res));
    		if(ret) {
    			printk(KERN_ERR"%s(): adding resources for %s failed !!!\n",
    					__func__,ntx_bcmdhd_res[0].name);
    		}
    		platform_device_register(&ntx_device_bcmdhd);
    	}

	if (11 == gptHWCFG->m_val.bWifi || 12 == gptHWCFG->m_val.bWifi || 14 == gptHWCFG->m_val.bWifi) {
		mxc_register_device(&mxc_bt_rfkill, &mxc_bt_rfkill_data);
	}

}

extern void __iomem *twd_base;
static void __init mx6_ntx_timer_init(void)
{
	struct clk *uart_clk;
#ifdef CONFIG_LOCAL_TIMERS
	twd_base = ioremap(LOCAL_TWD_ADDR, SZ_256);
	BUG_ON(!twd_base);
#endif
	mx6_clocks_init(32768, 24000000, 0, 0);

	uart_clk = clk_get_sys("imx-uart.0", NULL);
	early_console_setup(UART1_BASE_ADDR, uart_clk);
}

static struct sys_timer mx6_ntx_timer = {
	.init   = mx6_ntx_timer_init,
};

static void __init mx6q_ntx_reserve(void)
{
	phys_addr_t phys;
	int i;

#if defined(CONFIG_MXC_GPU_VIV) || defined(CONFIG_MXC_GPU_VIV_MODULE)
	if (imx6q_gpu_pdata.reserved_mem_size) {
		phys = memblock_alloc_base(imx6q_gpu_pdata.reserved_mem_size,
					   SZ_4K, SZ_2G);
		memblock_remove(phys, imx6q_gpu_pdata.reserved_mem_size);
		imx6q_gpu_pdata.reserved_mem_base = phys;
	}
#endif

#if defined(CONFIG_ION)
	if (imx_ion_data.heaps[0].size) {
		phys = memblock_alloc(imx_ion_data.heaps[0].size, SZ_4K);
		memblock_remove(phys, imx_ion_data.heaps[0].size);
		imx_ion_data.heaps[0].base = phys;
	}
#endif

	for (i = 0; i < ARRAY_SIZE(ntx_fb_data); i++)
		if (ntx_fb_data[i].res_size[0]) {
			/* reserve for background buffer */
			phys = memblock_alloc(ntx_fb_data[i].res_size[0],
						SZ_4K);
			memblock_remove(phys, ntx_fb_data[i].res_size[0]);
			ntx_fb_data[i].res_base[0] = phys;
		}
	if (vout_mem.res_msize) {
		phys = memblock_alloc_base(vout_mem.res_msize,
					   SZ_4K, SZ_1G);
		memblock_remove(phys, vout_mem.res_msize);
		vout_mem.res_mbase = phys;
	}
}

/*
 * initialize __mach_desc_MX6Q_ntx data structure.
 */
MACHINE_START(MX6DL_NTX, "Freescale i.MX 6Quad/DualLite/Solo NTX Board")
	/* Maintainer: Freescale Semiconductor, Inc. */
	.boot_params = MX6_PHYS_OFFSET + 0x100,
	.fixup = fixup_mxc_board,
	.map_io = mx6_map_io,
	.init_irq = mx6_init_irq,
	.init_machine = mx6_ntx_board_init,
	.timer = &mx6_ntx_timer,
	.reserve = mx6q_ntx_reserve,
MACHINE_END
