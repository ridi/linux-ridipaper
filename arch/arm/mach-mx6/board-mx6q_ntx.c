/*
 * Copyright (C) 2012-2013 Freescale Semiconductor, Inc. All Rights Reserved.
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
#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/mtd/partitions.h>
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
#include <linux/mmc/sdhci.h>

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
#include <mach/mxc_ir.h>

#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#include "usb.h"
#include "devices-imx6q.h"
#include "crm_regs.h"
#include "cpu_op-mx6.h"
#include "board-mx6q_ntx.h"
#include "board-mx6dl_sabresd.h"
#include <mach/imx_rfkill.h>
#include <../drivers/misc/ntx-misc.h>

#include "ntx_hwconfig.h"

#define NTX_RGMII_RST	IMX_GPIO_NR(2, 19)
#define NTX_RGMII_INT	IMX_GPIO_NR(2, 21)

#define NTX_MSP_INT		IMX_GPIO_NR(3, 19)
#define NTX_HDMI_PW_EN	IMX_GPIO_NR(3, 22)

#define NTX_POWER_OFF	IMX_GPIO_NR(1, 2)
//#define NTX_ON_LED		IMX_GPIO_NR(4, 5)

#define NTX_WIFI_3V3_ON	IMX_GPIO_NR(1, 6)
#define NTX_WIFI_RST	IMX_GPIO_NR(1, 7)
#define NTX_WIFI_INT	IMX_GPIO_NR(1, 8)

#define NTX_CASH_OPEN	IMX_GPIO_NR(7, 13)
#define NTX_CASH_12V	IMX_GPIO_NR(1, 5)
//#define NTX_CASH_N12V_EN	IMX_GPIO_NR(3, 31)
//#define NTX_CASH_24V	IMX_GPIO_NR(2, 17)
#define NTX_CASH_N12V_EN	IMX_GPIO_NR(3, 20)
#define NTX_CASH_24V	IMX_GPIO_NR(4, 5)

#define NTX_AD_AMP_CTRL	IMX_GPIO_NR(2, 18)

#define NTX_DB_PWR_ON	IMX_GPIO_NR(1, 1)

#define NTX_RS232_RST	IMX_GPIO_NR(5, 2)
#define NTX_TOUCH_RESET	IMX_GPIO_NR(2, 28)
#define NTX_PWR_EN2		IMX_GPIO_NR(5, 4)
#define NTX_USBHUB1_RST	IMX_GPIO_NR(2, 22)
#define NTX_USBHUB2_RST	IMX_GPIO_NR(3, 27)
#define NTX_VMAX_12V_EN		IMX_GPIO_NR(3, 31)

#define NTX_SD4_CLK 	IMX_GPIO_NR(7, 10)
#define NTX_SD4_CMD 	IMX_GPIO_NR(7, 9)
#define NTX_SD4_DAT0	IMX_GPIO_NR(2, 9)
#define NTX_SD4_DAT1	IMX_GPIO_NR(2, 10)
#define NTX_SD4_DAT2	IMX_GPIO_NR(2, 11)
#define NTX_SD4_DAT3	IMX_GPIO_NR(2, 12)

#define NTX_USB_OTG_ID		IMX_GPIO_NR(3, 26) 	// always low for host only.
#define NTX_VGA_BLANK	IMX_GPIO_NR(3, 29)
#define NTX_VGA_PSAVE	IMX_GPIO_NR(3, 30)

#define NTX_LCD_BL_EN		IMX_GPIO_NR(1, 4)

#define MX6_ENET_IRQ		NTX_RGMII_INT
//#define IOMUX_OBSRV_MUX1_OFFSET	0x3c
//#define OBSRV_MUX1_MASK			0x3f
//#define OBSRV_MUX1_ENET_IRQ		0x9

static struct clk *sata_clk;
//static struct clk *clko;
//static int mma8451_position;
//static int mag3110_position = 1;
//static int max11801_mode = 1;
static int caam_enabled;

extern char *gp_reg_id;
extern char *soc_reg_id;
extern char *pu_reg_id;
extern int epdc_enabled;

//static int max17135_regulator_init(struct max17135 *max17135);

static const struct esdhc_platform_data mx6q_ntx_sd1_data __initconst = {
	.always_present = 1,
	.keep_power_at_suspend = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_PERMANENT,
};

static const struct esdhc_platform_data mx6q_ntx_sd2_data __initconst = {
//	.cd_gpio = NTX_SD2_CD,
//	.wp_gpio = NTX_SD2_WP,
	.keep_power_at_suspend = 1,
	.support_8bit = 1,
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
	.cd_gpio		= NTX_WIFI_3V3_ON,
	.wp_gpio = -1,
	.keep_power_at_suspend = 1,
	.delay_line = 0,
	.cd_type = ESDHC_CD_WIFI_PWR,
};

static const struct anatop_thermal_platform_data
	mx6q_ntx_anatop_thermal_data __initconst = {
		.name = "anatop_thermal",
};


#define _MYINIT_DATA	
#define _MYINIT_TEXT	
volatile static unsigned char _MYINIT_DATA *gpbHWCFG_paddr;
//volatile unsigned char *gpbHWCFG_vaddr;
volatile unsigned long _MYINIT_DATA gdwHWCFG_size;
volatile NTX_HWCONFIG *gptHWCFG;

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


static int _MYINIT_TEXT hwcfg_p_setup(char *str)
{
	gpbHWCFG_paddr = (unsigned char *)simple_strtoul(str,NULL,0);
	if(NULL==gptHWCFG) {
		gptHWCFG = (NTX_HWCONFIG *)_MemoryRequest((void *)gpbHWCFG_paddr, gdwHWCFG_size, "hwcfg_p");
		if(!gptHWCFG) {
			return 0;
		}
	}
	printk("%s() hwcfg_p=%p,vaddr=%p,size=%d\n",__FUNCTION__,
		gpbHWCFG_paddr,gptHWCFG,(int)gdwHWCFG_size);
		
	if(NtxHwCfg_ChkCfgHeaderEx((NTX_HWCONFIG *)gptHWCFG,1)>=0) {
		//printk("%s() ntx_hwconfig load success !!\n",__FUNCTION__);
		printk("%s() pcba=\"%s\" !!\n",__FUNCTION__,NtxHwCfg_GetCfgFldStrVal((NTX_HWCONFIG *)gptHWCFG,HWCFG_FLDIDX_PCB));
	}
	else {
		printk("%s() ntx_hwconfig check fail !!\n",__FUNCTION__);
	}
	
	return 1;
}

static int _MYINIT_TEXT hwcfg_size_setup(char *str)
{
	gdwHWCFG_size = (unsigned long)simple_strtoul(str,NULL,0);
	printk("%s() hwcfg_szie=%d\n",__FUNCTION__,(int)gdwHWCFG_size);
	return 1;
}

static void _parse_cmdline(void)
{
	static int iParseCnt = 0;
	char *pcPatternStart,*pcPatternVal,*pcPatternValEnd,cTempStore;
	unsigned long ulPatternLen;

	char *szParsePatternA[]={"hwcfg_sz=","hwcfg_p="};
	int ((*pfnDispatchA[])(char *str))={hwcfg_size_setup,hwcfg_p_setup };
		
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
	//printk("%s():cp cmdline=%s\n",__FUNCTION__,pszCmdLineBuf);
	
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
	}
}



static inline void mx6q_ntx_init_uart(void)
{
	imx6q_add_imx_uart(3, NULL);
	imx6q_add_imx_uart(2, NULL);
	imx6q_add_imx_uart(1, NULL);
	imx6q_add_imx_uart(0, NULL);
}

static int mx6q_ntx_fec_phy_init(struct phy_device *phydev)
{
//	unsigned short val;
	printk ("[%s-%d] reset phy ...\n",__func__, __LINE__);
	mxc_iomux_v3_setup_multiple_pads (mx6q_ntx_rgmii_rx_gpio_pads, 
		ARRAY_SIZE(mx6q_ntx_rgmii_rx_gpio_pads));
	gpio_request (IMX_GPIO_NR(6, 24), "phy_ad2");
	gpio_request (IMX_GPIO_NR(6, 25), "selrgv");
	gpio_request (IMX_GPIO_NR(6, 27), "tx_delay");
	gpio_request (IMX_GPIO_NR(6, 28), "an_0");
	gpio_request (IMX_GPIO_NR(6, 29), "an_1");
	gpio_direction_output(IMX_GPIO_NR(6, 24), 0); 	// phy_ad2
	gpio_direction_output(IMX_GPIO_NR(6, 25), 0);   // selrgv  0: 2.5V RGMII
	gpio_direction_output(IMX_GPIO_NR(6, 27), 1);   // tx_delay	1: 2ns delay
	gpio_direction_output(IMX_GPIO_NR(6, 28), 1);   // an_0  11 : auto negotiation
	gpio_direction_output(IMX_GPIO_NR(6, 29), 1);   // an_1
	
	gpio_direction_output(NTX_RGMII_RST, 0);
	msleep (40);
	gpio_direction_output(NTX_RGMII_RST, 1);
	msleep (40);
	
	gpio_free(IMX_GPIO_NR(6, 24));
	gpio_free(IMX_GPIO_NR(6, 25));
	gpio_free(IMX_GPIO_NR(6, 27));
	gpio_free(IMX_GPIO_NR(6, 28));
	gpio_free(IMX_GPIO_NR(6, 29));
	mxc_iomux_v3_setup_multiple_pads (mx6q_ntx_rgmii_rx_pads, 
		ARRAY_SIZE(mx6q_ntx_rgmii_rx_pads));

	/* set 100M, full duplex, auto negotiation */
	phy_write(phydev, 0x00, 0x9120);
//	printk ("[%s-%d] iner %X, insr %X\n",__func__, __LINE__, phy_read(phydev, 0x12), phy_read(phydev, 0x13));
	
#if 0
	// disable EEE LED mode
	phy_write(phydev, 0x1F, 0x5);
	phy_write(phydev, 0x5, 0x8b82);
	phy_write(phydev, 0x6, 0x052b);
	phy_write(phydev, 0x1F, 0);
#endif	
	
 	// set led
	phy_write(phydev, 0x1F, 0x7);   	// switch to ExtPage 0x2C
	phy_write(phydev, 0x1E, 0x2c); 
 	phy_write(phydev, 0x1A, 0x10); 		// led0 transmit 
	phy_write(phydev, 0x1C, 0x347); 	// led2 1000M (low active), led1 100M / 10M 
 	phy_write(phydev, 0x1F, 0);
 	// set led
	phy_write(phydev, 0x1F, 0x7);   	// switch to ExtPage 0x2C
	phy_write(phydev, 0x1E, 0xA0); 
	phy_write(phydev, 0x1A, 0x0); 
 	phy_write(phydev, 0x1F, 0);
	return 0;
}

static struct fec_platform_data fec_data __initdata = {
	.init = mx6q_ntx_fec_phy_init,
	.phy = PHY_INTERFACE_MODE_RGMII, 
	.gpio_irq = -1,
};

#if 0
static int mx6q_ntx_spi_cs[] = {
	NTX_ECSPI1_CS0,
};

static const struct spi_imx_master mx6q_ntx_spi_data __initconst = {
	.chipselect     = mx6q_ntx_spi_cs,
	.num_chipselect = ARRAY_SIZE(mx6q_ntx_spi_cs),
};

static struct spi_board_info imx6_ntx_spi_nor_device[] __initdata = {
};

static void spi_device_init(void)
{
	spi_register_board_info(imx6_ntx_spi_nor_device,
				ARRAY_SIZE(imx6_ntx_spi_nor_device));
}
#endif

static struct imx_ssi_platform_data mx6_ntx_ssi_pdata = {
	.flags = IMX_SSI_DMA | IMX_SSI_SYN,
};

static struct mxc_audio_platform_data mx6_ntx_audio_data;
static struct clk *clko;

static int mx6_ntx_audio_clk_enable(int enable)
{
	if (enable)
		clk_enable(clko);
	else
		clk_disable(clko);
	return 0;
}

#define NTX_AUD4_TXD	IMX_GPIO_NR(1, 13)
int mx6_ntx_audio_amp_enable(int enable)
{
	if (enable) {
		mxc_iomux_v3_setup_pad (MX6Q_PAD_SD2_DAT2__AUDMUX_AUD4_TXD);
		gpio_free (NTX_AUD4_TXD);
		gpio_direction_output(NTX_AD_AMP_CTRL,1);
	}
	else {
		gpio_request (NTX_AUD4_TXD, NULL);
		gpio_direction_output(NTX_AUD4_TXD, 0);
		mxc_iomux_v3_setup_pad (MX6Q_PAD_SD2_DAT2__GPIO_1_13);
		// amp_ctrl need 180ms delay after setting 0 and need 100ms delay after setting 1.
//		gpio_direction_output(NTX_AD_AMP_CTRL,0);
	}

	return 0;
}

static int mx6_ntx_audio_init(void)
{
	int rate;

	clko = clk_get(NULL, "clko_clk");
	if (IS_ERR(clko)) {
		pr_err("can't get CLKO clock.\n");
		return PTR_ERR(clko);
	}
	rate = clk_round_rate(clko, 24000000);
	printk ("[%s-%d] clock rate %d...\n",__func__,__LINE__,rate);

	clk_set_rate(clko, rate);
//	clk_enable(clko);
	mx6_ntx_audio_data.sysclk = rate;
	return 0;
}

static struct mxc_audio_platform_data mx6_ntx_audio_data = {
	.ssi_num = 1,
	.src_port = 2,
	.ext_port = 4,
	.init = mx6_ntx_audio_init,
	.hp_gpio = -1,
	.clock_enable = mx6_ntx_audio_clk_enable,
	.amp_enable = mx6_ntx_audio_amp_enable,
};

static struct platform_device mx6_ntx_audio5623_device = {
	.name = "imx-alc5623",
};
static struct platform_device mx6_ntx_audio5640_device = {
	.name = "imx-alc5640",
};

static struct platform_device ntx_device_rtc = {
	.name           = "ntx_misc_rtc",
	.id				= 0,
	.dev            = {
		.platform_data = (void*)-1,
	}
};

static struct imxi2c_platform_data mx6q_ntx_i2c_data = {
	.bitrate = 100000,
};

#if 0
static struct fsl_mxc_lightsensor_platform_data ls_data = {
	.rext = 499,	/* calibration: 499K->700K */
};
#endif

static struct i2c_board_info mxc_i2c0_board_info[] __initdata = {
	{
		.type = "msp430",
		.addr = 0x43,
		.irq = gpio_to_irq(NTX_MSP_INT),
	},
};

static struct i2c_board_info mxc_i2c1_board_info[] __initdata = {
	{
		I2C_BOARD_INFO("mxc_hdmi_i2c", 0x50),
	},
};

static struct i2c_board_info mxc_i2c2_board_info[] __initdata = {
	{
		I2C_BOARD_INFO("alc5623", 0x1A),
	},
};

static struct ntx_misc_platform_data ntx_misc_info;

static struct platform_device ntx_charger = {
	.name	= "pmic_battery",
	.id = 1,
	.dev            = {
		.platform_data = &ntx_misc_info,
	}
};

#if 0
static int epdc_get_pins(void)
{
	int ret = 0;

	/* Claim GPIOs for EPDC pins - used during power up/down */
	ret |= gpio_request(NTX_EPDC_SDDO_0, "epdc_d0");
	ret |= gpio_request(NTX_EPDC_SDDO_1, "epdc_d1");
	ret |= gpio_request(NTX_EPDC_SDDO_2, "epdc_d2");
	ret |= gpio_request(NTX_EPDC_SDDO_3, "epdc_d3");
	ret |= gpio_request(NTX_EPDC_SDDO_4, "epdc_d4");
	ret |= gpio_request(NTX_EPDC_SDDO_5, "epdc_d5");
	ret |= gpio_request(NTX_EPDC_SDDO_6, "epdc_d6");
	ret |= gpio_request(NTX_EPDC_SDDO_7, "epdc_d7");
	ret |= gpio_request(NTX_EPDC_GDCLK, "epdc_gdclk");
	ret |= gpio_request(NTX_EPDC_GDSP, "epdc_gdsp");
	ret |= gpio_request(NTX_EPDC_GDOE, "epdc_gdoe");
	ret |= gpio_request(NTX_EPDC_GDRL, "epdc_gdrl");
	ret |= gpio_request(NTX_EPDC_SDCLK, "epdc_sdclk");
	ret |= gpio_request(NTX_EPDC_SDOE, "epdc_sdoe");
	ret |= gpio_request(NTX_EPDC_SDLE, "epdc_sdle");
	ret |= gpio_request(NTX_EPDC_SDSHR, "epdc_sdshr");
	ret |= gpio_request(NTX_EPDC_BDR0, "epdc_bdr0");
	ret |= gpio_request(NTX_EPDC_SDCE0, "epdc_sdce0");
	ret |= gpio_request(NTX_EPDC_SDCE1, "epdc_sdce1");
	ret |= gpio_request(NTX_EPDC_SDCE2, "epdc_sdce2");

	return ret;
}

static void epdc_put_pins(void)
{
	gpio_free(NTX_EPDC_SDDO_0);
	gpio_free(NTX_EPDC_SDDO_1);
	gpio_free(NTX_EPDC_SDDO_2);
	gpio_free(NTX_EPDC_SDDO_3);
	gpio_free(NTX_EPDC_SDDO_4);
	gpio_free(NTX_EPDC_SDDO_5);
	gpio_free(NTX_EPDC_SDDO_6);
	gpio_free(NTX_EPDC_SDDO_7);
	gpio_free(NTX_EPDC_GDCLK);
	gpio_free(NTX_EPDC_GDSP);
	gpio_free(NTX_EPDC_GDOE);
	gpio_free(NTX_EPDC_GDRL);
	gpio_free(NTX_EPDC_SDCLK);
	gpio_free(NTX_EPDC_SDOE);
	gpio_free(NTX_EPDC_SDLE);
	gpio_free(NTX_EPDC_SDSHR);
	gpio_free(NTX_EPDC_BDR0);
	gpio_free(NTX_EPDC_SDCE0);
	gpio_free(NTX_EPDC_SDCE1);
	gpio_free(NTX_EPDC_SDCE2);
}

static void epdc_enable_pins(void)
{
	/* Configure MUX settings to enable EPDC use */
	mxc_iomux_v3_setup_multiple_pads(mx6dl_sabresd_epdc_enable_pads, \
				ARRAY_SIZE(mx6dl_sabresd_epdc_enable_pads));

	gpio_direction_input(NTX_EPDC_SDDO_0);
	gpio_direction_input(NTX_EPDC_SDDO_1);
	gpio_direction_input(NTX_EPDC_SDDO_2);
	gpio_direction_input(NTX_EPDC_SDDO_3);
	gpio_direction_input(NTX_EPDC_SDDO_4);
	gpio_direction_input(NTX_EPDC_SDDO_5);
	gpio_direction_input(NTX_EPDC_SDDO_6);
	gpio_direction_input(NTX_EPDC_SDDO_7);
	gpio_direction_input(NTX_EPDC_GDCLK);
	gpio_direction_input(NTX_EPDC_GDSP);
	gpio_direction_input(NTX_EPDC_GDOE);
	gpio_direction_input(NTX_EPDC_GDRL);
	gpio_direction_input(NTX_EPDC_SDCLK);
	gpio_direction_input(NTX_EPDC_SDOE);
	gpio_direction_input(NTX_EPDC_SDLE);
	gpio_direction_input(NTX_EPDC_SDSHR);
	gpio_direction_input(NTX_EPDC_BDR0);
	gpio_direction_input(NTX_EPDC_SDCE0);
	gpio_direction_input(NTX_EPDC_SDCE1);
	gpio_direction_input(NTX_EPDC_SDCE2);
}

static void epdc_disable_pins(void)
{
	/* Configure MUX settings for EPDC pins to
	 * GPIO and drive to 0. */
	mxc_iomux_v3_setup_multiple_pads(mx6dl_sabresd_epdc_disable_pads, \
				ARRAY_SIZE(mx6dl_sabresd_epdc_disable_pads));

	gpio_direction_output(NTX_EPDC_SDDO_0, 0);
	gpio_direction_output(NTX_EPDC_SDDO_1, 0);
	gpio_direction_output(NTX_EPDC_SDDO_2, 0);
	gpio_direction_output(NTX_EPDC_SDDO_3, 0);
	gpio_direction_output(NTX_EPDC_SDDO_4, 0);
	gpio_direction_output(NTX_EPDC_SDDO_5, 0);
	gpio_direction_output(NTX_EPDC_SDDO_6, 0);
	gpio_direction_output(NTX_EPDC_SDDO_7, 0);
	gpio_direction_output(NTX_EPDC_GDCLK, 0);
	gpio_direction_output(NTX_EPDC_GDSP, 0);
	gpio_direction_output(NTX_EPDC_GDOE, 0);
	gpio_direction_output(NTX_EPDC_GDRL, 0);
	gpio_direction_output(NTX_EPDC_SDCLK, 0);
	gpio_direction_output(NTX_EPDC_SDOE, 0);
	gpio_direction_output(NTX_EPDC_SDLE, 0);
	gpio_direction_output(NTX_EPDC_SDSHR, 0);
	gpio_direction_output(NTX_EPDC_BDR0, 0);
	gpio_direction_output(NTX_EPDC_SDCE0, 0);
	gpio_direction_output(NTX_EPDC_SDCE1, 0);
	gpio_direction_output(NTX_EPDC_SDCE2, 0);
}

static struct fb_videomode e60_v110_mode = {
	.name = "E60_V110",
	.refresh = 50,
	.xres = 800,
	.yres = 600,
	.pixclock = 18604700,
	.left_margin = 8,
	.right_margin = 178,
	.upper_margin = 4,
	.lower_margin = 10,
	.hsync_len = 20,
	.vsync_len = 4,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};
static struct fb_videomode e60_v220_mode = {
	.name = "E60_V220",
	.refresh = 85,
	.xres = 800,
	.yres = 600,
	.pixclock = 30000000,
	.left_margin = 8,
	.right_margin = 164,
	.upper_margin = 4,
	.lower_margin = 8,
	.hsync_len = 4,
	.vsync_len = 1,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
	.refresh = 85,
	.xres = 800,
	.yres = 600,
};
static struct fb_videomode e060scm_mode = {
	.name = "E060SCM",
	.refresh = 85,
	.xres = 800,
	.yres = 600,
	.pixclock = 26666667,
	.left_margin = 8,
	.right_margin = 100,
	.upper_margin = 4,
	.lower_margin = 8,
	.hsync_len = 4,
	.vsync_len = 1,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};
static struct fb_videomode e97_v110_mode = {
	.name = "E97_V110",
	.refresh = 50,
	.xres = 1200,
	.yres = 825,
	.pixclock = 32000000,
	.left_margin = 12,
	.right_margin = 128,
	.upper_margin = 4,
	.lower_margin = 10,
	.hsync_len = 20,
	.vsync_len = 4,
	.sync = 0,
	.vmode = FB_VMODE_NONINTERLACED,
	.flag = 0,
};

static struct imx_epdc_fb_mode panel_modes[] = {
	{
		&e60_v110_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		428,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		1,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e60_v220_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		465,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		9,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e060scm_mode,
		4,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		419,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		5,      /* gdclk_offs */
		1,      /* num_ce */
	},
	{
		&e97_v110_mode,
		8,      /* vscan_holdoff */
		10,     /* sdoed_width */
		20,     /* sdoed_delay */
		10,     /* sdoez_width */
		20,     /* sdoez_delay */
		632,    /* gdclk_hp_offs */
		20,     /* gdsp_offs */
		0,      /* gdoe_offs */
		1,      /* gdclk_offs */
		3,      /* num_ce */
	}
};

static struct imx_epdc_fb_platform_data epdc_data = {
	.epdc_mode = panel_modes,
	.num_modes = ARRAY_SIZE(panel_modes),
	.get_pins = epdc_get_pins,
	.put_pins = epdc_put_pins,
	.enable_pins = epdc_enable_pins,
	.disable_pins = epdc_disable_pins,
};
#endif

static void imx6q_ntx_usbotg_vbus(bool on)
{
#if 0
	if (on)
		gpio_set_value(NTX_USB_OTG_PWR, 1);
	else
		gpio_set_value(NTX_USB_OTG_PWR, 0);
#endif
}

static void imx6q_ntx_host1_vbus(bool on)
{
#if 0
	if (on)
		gpio_set_value(NTX_USB_H1_PWR, 1);
	else
		gpio_set_value(NTX_USB_H1_PWR, 0);
#endif
}

static void __init imx6q_ntx_init_usb(void)
{
	int ret = 0;

	imx_otg_base = MX6_IO_ADDRESS(MX6Q_USB_OTG_BASE_ADDR);
#if 0
	/* disable external charger detect,
	 * or it will affect signal quality at dp .
	 */
	ret = gpio_request(NTX_USB_OTG_PWR, "usb-pwr");
	if (ret) {
		pr_err("failed to get GPIO NTX_USB_OTG_PWR: %d\n",
			ret);
		return;
	}
	gpio_direction_output(NTX_USB_OTG_PWR, 0);
	/* keep USB host1 VBUS always on */
	ret = gpio_request(NTX_USB_H1_PWR, "usb-h1-pwr");
	if (ret) {
		pr_err("failed to get GPIO NTX_USB_H1_PWR: %d\n",
			ret);
		return;
	}
	gpio_direction_output(NTX_USB_H1_PWR, 0);
#endif
	
	if (board_is_mx6_reva())  	// USB OTG ID select GPIO_1 
		mxc_iomux_set_gpr_register(1, 13, 1, 1);
	else	// USB OTG ID select ENET_RX_ER 
		mxc_iomux_set_gpr_register(1, 13, 1, 0);

	mx6_set_otghost_vbus_func(imx6q_ntx_usbotg_vbus);
	mx6_set_host1_vbus_func(imx6q_ntx_host1_vbus);

}

/* HW Initialization, if return 0, initialization is successful. */
static int mx6q_ntx_sata_init(struct device *dev, void __iomem *addr)
{
	u32 tmpdata;
	int ret = 0;
	struct clk *clk;

	sata_clk = clk_get(dev, "imx_sata_clk");
	if (IS_ERR(sata_clk)) {
		dev_err(dev, "no sata clock.\n");
		return PTR_ERR(sata_clk);
	}
	ret = clk_enable(sata_clk);
	if (ret) {
		dev_err(dev, "can't enable sata clock.\n");
		goto put_sata_clk;
	}

	/* Set PHY Paremeters, two steps to configure the GPR13,
	 * one write for rest of parameters, mask of first write is 0x07FFFFFD,
	 * and the other one write for setting the mpll_clk_off_b
	 *.rx_eq_val_0(iomuxc_gpr13[26:24]),
	 *.los_lvl(iomuxc_gpr13[23:19]),
	 *.rx_dpll_mode_0(iomuxc_gpr13[18:16]),
	 *.sata_speed(iomuxc_gpr13[15]),
	 *.mpll_ss_en(iomuxc_gpr13[14]),
	 *.tx_atten_0(iomuxc_gpr13[13:11]),
	 *.tx_boost_0(iomuxc_gpr13[10:7]),
	 *.tx_lvl(iomuxc_gpr13[6:2]),
	 *.mpll_ck_off(iomuxc_gpr13[1]),
	 *.tx_edgerate_0(iomuxc_gpr13[0]),
	 */
	tmpdata = readl(IOMUXC_GPR13);
	writel(((tmpdata & ~0x07FFFFFD) | 0x0593A044), IOMUXC_GPR13);

	/* enable SATA_PHY PLL */
	tmpdata = readl(IOMUXC_GPR13);
	writel(((tmpdata & ~0x2) | 0x2), IOMUXC_GPR13);

	/* Get the AHB clock rate, and configure the TIMER1MS reg later */
	clk = clk_get(NULL, "ahb");
	if (IS_ERR(clk)) {
		dev_err(dev, "no ahb clock.\n");
		ret = PTR_ERR(clk);
		goto release_sata_clk;
	}
	tmpdata = clk_get_rate(clk) / 1000;
	clk_put(clk);

#ifdef CONFIG_SATA_AHCI_PLATFORM
	ret = sata_init(addr, tmpdata);
	if (ret == 0)
		return ret;
#else
	usleep_range(1000, 2000);
	/* AHCI PHY enter into PDDQ mode if the AHCI module is not enabled */
	tmpdata = readl(addr + PORT_PHY_CTL);
	writel(tmpdata | PORT_PHY_CTL_PDDQ_LOC, addr + PORT_PHY_CTL);
	pr_info("No AHCI save PWR: PDDQ %s\n", ((readl(addr + PORT_PHY_CTL)
					>> 20) & 1) ? "enabled" : "disabled");
#endif

release_sata_clk:
	/* disable SATA_PHY PLL */
	writel((readl(IOMUXC_GPR13) & ~0x2), IOMUXC_GPR13);
	clk_disable(sata_clk);
put_sata_clk:
	clk_put(sata_clk);

	return ret;
}

#ifdef CONFIG_SATA_AHCI_PLATFORM
static void mx6q_ntx_sata_exit(struct device *dev)
{
	clk_disable(sata_clk);
	clk_put(sata_clk);
}

static struct ahci_platform_data mx6q_ntx_sata_data = {
	.init = mx6q_ntx_sata_init,
	.exit = mx6q_ntx_sata_exit,
};
#endif

#if 0
static void mx6q_ntx_flexcan0_switch(int enable)
{
	if (enable) {
		gpio_set_value(NTX_CAN1_STBY, 1);
	} else {
		gpio_set_value(NTX_CAN1_STBY, 0);
	}
}

static const struct flexcan_platform_data
	mx6q_ntx_flexcan0_pdata __initconst = {
	.transceiver_switch = mx6q_ntx_flexcan0_switch,
};
#endif

static struct viv_gpu_platform_data imx6q_gpu_pdata __initdata = {
	.reserved_mem_size = SZ_128M + SZ_64M - SZ_16M,
};

static struct imx_asrc_platform_data imx_asrc_data = {
	.channel_bits = 4,
	.clk_map_ver = 2,
};

#if 0
static void mx6_reset_mipi_dsi(void)
{
	gpio_set_value(NTX_DISP_PWR_EN, 1);
	gpio_set_value(NTX_DISP_RST_B, 1);
	udelay(10);
	gpio_set_value(NTX_DISP_RST_B, 0);
	udelay(50);
	gpio_set_value(NTX_DISP_RST_B, 1);

	/*
	 * it needs to delay 120ms minimum for reset complete
	 */
	msleep(120);
}

static struct mipi_dsi_platform_data mipi_dsi_pdata = {
	.ipu_id		= 1,
	.disp_id	= 1,
	.lcd_panel	= "TRULY-WVGA",
	.reset		= mx6_reset_mipi_dsi,
};
#endif

static struct ipuv3_fb_platform_data ntx_fb_data[] = {
	{ /*fb0*/
	.disp_dev = "ldb",
	.interface_pix_fmt = IPU_PIX_FMT_RGB666,
	.mode_str = "LDB-WXGA",
	.default_bpp = 32,
	.int_clk = false,
	}, {
	.disp_dev = "lcd",
	.interface_pix_fmt = IPU_PIX_FMT_RGB24,
	.mode_str = "LCD-XGA",
	.default_bpp = 32,
	.int_clk = false,
	}, {
	.disp_dev = "hdmi",
	.interface_pix_fmt = IPU_PIX_FMT_RGB24,
	.mode_str = "1920x1080M@60",
	.default_bpp = 32,
	.int_clk = false,
	.late_init = false,
	},
};

static void hdmi_init(int ipu_id, int disp_id)
{
	int hdmi_mux_setting;

	printk ("[%s-%d] ipu %d, di %d\n", __func__, __LINE__, ipu_id, disp_id);
	if ((ipu_id > 1) || (ipu_id < 0)) {
		pr_err("Invalid IPU select for HDMI: %d. Set to 0\n", ipu_id);
		ipu_id = 0;
	}

	if ((disp_id > 1) || (disp_id < 0)) {
		pr_err("Invalid DI select for HDMI: %d. Set to 0\n", disp_id);
		disp_id = 0;
	}

	/* Configure the connection between IPU1/2 and HDMI */
	hdmi_mux_setting = 2*ipu_id + disp_id;

	/* GPR3, bits 2-3 = HDMI_MUX_CTL */
	mxc_iomux_set_gpr_register(3, 2, 2, hdmi_mux_setting);

	/* Set HDMI event as SDMA event2 while Chip version later than TO1.2 */
	if (hdmi_SDMA_check())
		mxc_iomux_set_gpr_register(0, 0, 1, 1);
}

/* On mx6x ntx board i2c2 iomux with hdmi ddc,
 * the pins default work at i2c2 function,
 when hdcp enable, the pins should work at ddc function */
static void hdmi_enable_ddc_pin(void)
{
	if (cpu_is_mx6dl())
		mxc_iomux_v3_setup_multiple_pads(mx6dl_sabresd_hdmi_ddc_pads,
			ARRAY_SIZE(mx6dl_sabresd_hdmi_ddc_pads));
	else
		mxc_iomux_v3_setup_multiple_pads(mx6q_ntx_hdmi_ddc_pads,
			ARRAY_SIZE(mx6q_ntx_hdmi_ddc_pads));
	printk ("[%s-%d] ...\n", __func__, __LINE__);
}

static void hdmi_disable_ddc_pin(void)
{
	if (cpu_is_mx6dl())
		mxc_iomux_v3_setup_multiple_pads(mx6dl_sabresd_i2c2_pads,
			ARRAY_SIZE(mx6dl_sabresd_i2c2_pads));
	else
		mxc_iomux_v3_setup_multiple_pads(mx6q_ntx_i2c2_pads,
			ARRAY_SIZE(mx6q_ntx_i2c2_pads));
	printk ("[%s-%d] ...\n", __func__, __LINE__);
}

static struct fsl_mxc_hdmi_platform_data hdmi_data = {
	.init = hdmi_init,
	.enable_pins = hdmi_enable_ddc_pin,
	.disable_pins = hdmi_disable_ddc_pin,
	.phy_reg_vlev = 0x0294,
	.phy_reg_cksymtx = 0x800d,
};

static struct fsl_mxc_hdmi_core_platform_data hdmi_core_data = {
	.ipu_id = 1,
	.disp_id = 1,
};

static struct fsl_mxc_lcd_platform_data lcdif_data = {
	.ipu_id = 0,
	.disp_id = 0,
	.default_ifmt = IPU_PIX_FMT_RGB24,
};

static struct fsl_mxc_ldb_platform_data ldb_data = {
	.ipu_id = 1,
	.disp_id = 0,
	.ext_ref = 1,
	.mode = LDB_SIN0,
};

#if 0
static struct max8903_pdata charger1_data = {
	.dok = NTX_CHARGE_DOK_B,
	.uok = NTX_CHARGE_UOK_B,
	.chg = NTX_CHARGE_CHG_1_B,
	.flt = NTX_CHARGE_FLT_1_B,
	.dcm_always_high = true,
	.dc_valid = true,
	.usb_valid = true,
};

static struct platform_device ntx_max8903_charger_1 = {
	.name	= "max8903-charger",
	.id	= 1,
	.dev	= {
		.platform_data = &charger1_data,
	},
};
#endif

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

static struct ion_platform_data imx_ion_data = {
	.nr = 1,
	.heaps = {
		{
		.id = 0,
		.type = ION_HEAP_TYPE_CARVEOUT,
		.name = "vpu_ion",
		.size = SZ_16M,
		.cacheable = 0,
		},
	},
};

#if 0
static struct fsl_mxc_capture_platform_data capture_data[] = {
	{
		.csi = 0,
		.ipu = 0,
		.mclk_source = 0,
		.is_mipi = 0,
	}, {
		.csi = 1,
		.ipu = 0,
		.mclk_source = 0,
		.is_mipi = 1,
	},
};
#endif

void *g_wifi_sd_host;
irq_handler_t g_cd_irq;

void ntx_register_wifi_cd (irq_handler_t handler, void *data)
{
	printk ("[%s-%d] register g_cd_irq \n",__func__,__LINE__);
	g_wifi_sd_host = data;
	g_cd_irq = handler;
}

static DEFINE_MUTEX(ntx_wifi_power_mutex);
static int gi_wifi_power_status = -1;

int _ntx_get_wifi_power_status(void)
{
	int iWifiPowerStatus;

	mutex_lock(&ntx_wifi_power_mutex);
	iWifiPowerStatus = gi_wifi_power_status;
	mutex_unlock(&ntx_wifi_power_mutex);

	return iWifiPowerStatus;
}

int _ntx_wifi_power_ctrl (int isWifiEnable)
{
	int iHWID;
	int iOldStatus;

	mutex_lock(&ntx_wifi_power_mutex);
	iOldStatus = gi_wifi_power_status;
	printk("Wifi / BT power control %d\n", isWifiEnable);
	if(isWifiEnable == 0){
		gpio_direction_output (NTX_WIFI_RST, 0);
		gpio_direction_input (NTX_WIFI_3V3_ON);	// turn off Wifi_3V3_on

		msleep(10);

		gi_wifi_power_status=0;
	}
	else {
		gpio_free (NTX_SD4_CLK );
		gpio_free (NTX_SD4_CMD );
		gpio_free (NTX_SD4_DAT0);
		gpio_free (NTX_SD4_DAT1);
		gpio_free (NTX_SD4_DAT2);
		gpio_free (NTX_SD4_DAT3);
		mxc_iomux_v3_setup_multiple_pads(mx6q_ntx_sd4_wifi_pads, ARRAY_SIZE(mx6q_ntx_sd4_wifi_pads));			
		gpio_direction_output (NTX_WIFI_RST, 0);	// turn on wifi_RST
		msleep(10);

		gpio_direction_output (NTX_WIFI_3V3_ON, 0);	// turn on Wifi_3V3_on
		msleep(20);

		gpio_direction_input (NTX_WIFI_INT);
		msleep(10);
		gpio_direction_output (NTX_WIFI_RST, 1);	// turn on wifi_RST
		msleep(100);
#ifdef _WIFI_ALWAYS_ON_
		enable_irq_wake(gpio_to_irq(NTX_WIFI_INT));
#endif
		gi_wifi_power_status=1;
	}

#if 0
	if (g_cd_irq) {
		struct sdhci_host *host;

		host = (struct sdhci_host *) g_wifi_sd_host;
		//g_cd_irq (0, g_wifi_sd_host);
		//schedule_timeout (100);
		//msleep(1000);
		mmc_detect_change(host->mmc, msecs_to_jiffies(10));
		msleep(2000);
	}
	else {
		printk ("[%s-%d] not registered.\n",__func__,__LINE__);
	}
#endif

	if(isWifiEnable == 0){ // switch PIN function to GPIO
		// sdio port disable ...
#if 1
		mxc_iomux_v3_setup_multiple_pads(mx6q_ntx_sd4_gpio_pads, ARRAY_SIZE(mx6q_ntx_sd4_gpio_pads));
		gpio_request (NTX_SD4_CLK , "NTX_SD4_CLK" );
		gpio_request (NTX_SD4_CMD , "NTX_SD4_CMD" );
		gpio_request (NTX_SD4_DAT0, "NTX_SD4_DAT0");
		gpio_request (NTX_SD4_DAT1, "NTX_SD4_DAT1");
		gpio_request (NTX_SD4_DAT2, "NTX_SD4_DAT2");
		gpio_request (NTX_SD4_DAT3, "NTX_SD4_DAT3");
		gpio_direction_output (NTX_SD4_CLK , 0);
		gpio_direction_output (NTX_SD4_CMD , 0);
		gpio_direction_output (NTX_SD4_DAT0, 0);
		gpio_direction_output (NTX_SD4_DAT1, 0);
		gpio_direction_output (NTX_SD4_DAT2, 0);
		gpio_direction_output (NTX_SD4_DAT3, 0);
#else
		gpio_direction_output (NTX_WIFI_RST, 1);
		gpio_direction_output (NTX_WIFI_3V3_ON, 0);	// turn off Wifi_3V3_on
#endif
	}
	printk("%s() end.\n",__FUNCTION__);
	mutex_unlock(&ntx_wifi_power_mutex);
	return iOldStatus;
}

void ntx_wifi_power_ctrl(int iIsWifiEnable)
{
#if 0
	_ntx_wifi_power_ctrl(iIsWifiEnable);
#else
	printk ("ntx_wifi_power_ctrl (%d)\n", iIsWifiEnable);
	if (!iIsWifiEnable)
		return;
#if 0
	gpio_direction_output (NTX_WIFI_RST, 0);
	msleep (100);
	gpio_direction_output (NTX_WIFI_RST, 1);
#else
	_ntx_wifi_power_ctrl (0);
	msleep (500);
	_ntx_wifi_power_ctrl (1);
#endif
#endif
}

EXPORT_SYMBOL(ntx_wifi_power_ctrl);

static void mx6q_sd_bt_reset(void)
{
	printk(KERN_INFO "mx6q_sd_bt_reset");
}

static int mx6q_sd_bt_power_change(int status)
{
	if (status)
		mx6q_sd_bt_reset();
	return 0;
}

static struct platform_device mxc_bt_rfkill = {
	.name = "mxc_bt_rfkill",
};

static struct imx_bt_rfkill_platform_data mxc_bt_rfkill_data = {
	.power_change = mx6q_sd_bt_power_change,
};

struct imx_vout_mem {
	resource_size_t res_mbase;
	resource_size_t res_msize;
};

static struct imx_vout_mem vout_mem __initdata = {
	.res_msize = 0,
};

static void ntx_suspend_enter(void)
{
	/* suspend preparation */
	/* Disable AUX 5V */
//	gpio_set_value(NTX_AUX_5V_EN, 0);
	gpio_direction_output (NTX_HDMI_PW_EN,0);
}

static void ntx_suspend_exit(void)
{
	/* resume restore */
	gpio_direction_output (NTX_HDMI_PW_EN,1);
	/* Enable AUX 5V */
//	gpio_set_value(NTX_AUX_5V_EN, 1);
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

static int __init imx6q_init_audio(void)
{
#if 0
	if (board_is_mx6_reva()) {
		mxc_register_device(&mx6_ntx_audio_wm8958_device,
				    &wm8958_data);
		imx6q_add_imx_ssi(1, &mx6_ntx_ssi_pdata);

		mxc_wm8958_init();
	} else {
		platform_device_register(&ntx_vwm8962_reg_devices);
		mxc_register_device(&mx6_ntx_audio_wm8962_device,
				    &wm8962_data);
		imx6q_add_imx_ssi(1, &mx6_ntx_ssi_pdata);

		mxc_wm8962_init();
	}
#endif
	if(2==gptHWCFG->m_val.bAudioCodec) {
		// ALC5640 codec .
		mxc_register_device(&mx6_ntx_audio5640_device,
			 &mx6_ntx_audio_data);
	}
	else {
		// ALC5623 codec .
		mxc_register_device(&mx6_ntx_audio5623_device,
			 &mx6_ntx_audio_data);
	}
	imx6q_add_imx_ssi(1, &mx6_ntx_ssi_pdata);


	return 0;
}

#if 0
static void gps_power_on(bool on)
{
	/* Enable/disable aux_3v15 */
	gpio_request(NTX_AUX_3V15_EN, "aux_3v15_en");
	gpio_direction_output(NTX_AUX_3V15_EN, 1);
	gpio_set_value(NTX_AUX_3V15_EN, on);
	gpio_free(NTX_AUX_3V15_EN);
	/*Enable/disable gps_en*/
	gpio_request(NTX_GPS_EN, "gps_en");
	gpio_direction_output(NTX_GPS_EN, 1);
	gpio_set_value(NTX_GPS_EN, on);
	gpio_free(NTX_GPS_EN);
}
#endif

#if defined(CONFIG_LEDS_TRIGGER) || defined(CONFIG_LEDS_GPIO)

#define GPIO_LED(gpio_led, name_led, act_low, state_suspend, trigger)	\
{									\
	.gpio			= gpio_led,				\
	.name			= name_led,				\
	.active_low		= act_low,				\
	.retain_state_suspended = state_suspend,			\
	.default_state		= 0,					\
	.default_trigger	= trigger,		\
}

/* use to show a external power source is connected
 * GPIO_LED(NTX_CHARGE_DONE, "chg_detect", 0, 1, "ac-online"),
 */
static struct gpio_led imx6q_gpio_leds[] = {
//	GPIO_LED(NTX_ON_LED, "on_led", 0, 1, "heartbeat"),
//	GPIO_LED(NTX_ON_LED, "on_led", 0, 1, "default-on"),
};

static struct gpio_led_platform_data imx6q_gpio_leds_data = {
	.leds		= imx6q_gpio_leds,
	.num_leds	= ARRAY_SIZE(imx6q_gpio_leds),
};

static struct platform_device imx6q_gpio_led_device = {
	.name		= "leds-gpio",
	.id		= -1,
	.num_resources  = 0,
	.dev		= {
		.platform_data = &imx6q_gpio_leds_data,
	}
};

/* For BT_PWD_L is conflict with charger's LED trigger gpio on ntx_revC.
 * add mutual exclusion here to be decided which one to be used by board config
 */
static void __init imx6q_add_device_gpio_leds(void)
{
	platform_device_register(&imx6q_gpio_led_device);
}
#else
static void __init imx6q_add_device_gpio_leds(void) {}
#endif

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

static struct gpio_keys_button new_ntx_buttons[] = {
//	GPIO_BUTTON(NTX_VOLUME_UP, KEY_VOLUMEUP, 1, "volume-up", 0, 1),
//	GPIO_BUTTON(NTX_VOLUME_DN, KEY_VOLUMEDOWN, 1, "volume-down", 0, 1),
	GPIO_BUTTON(NTX_POWER_OFF, KEY_POWER, 1, "power-key", 1, 1),
};

static struct gpio_keys_platform_data new_ntx_button_data = {
	.buttons	= new_ntx_buttons,
	.nbuttons	= ARRAY_SIZE(new_ntx_buttons),
};

static struct platform_device ntx_button_device = {
	.name		= "gpio-keys",
	.id		= -1,
	.num_resources  = 0,
};

static void __init imx6q_add_device_buttons(void)
{
	platform_device_add_data(&ntx_button_device,
				&new_ntx_button_data,
				sizeof(new_ntx_button_data));

	platform_device_register(&ntx_button_device);
}
#else
static void __init imx6q_add_device_buttons(void) {}
#endif

static struct platform_pwm_backlight_data mx6_ntx_pwm_backlight_data = {
	.pwm_id = 0,
	.max_brightness = 248,
	.dft_brightness = 128,
	.pwm_period_ns = 50000,
};

#ifdef CONFIG_HAVE_EPIT
static struct platform_ir_data mx6_ntx_ir_data = {
    .pwm_id = 1,
    .epit_id = 0,
    .gpio_id = 0,
};
#endif

static struct mxc_dvfs_platform_data ntx_dvfscore_data = {
	.reg_id = "cpu_vddgp",
	.soc_id	= "cpu_vddsoc",
	.pu_id = "cpu_vddvpu",
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
	char *str;
	struct tag *t;
	int i = 0;
	struct ipuv3_fb_platform_data *pdata_fb = ntx_fb_data;

	for_each_tag(t, tags) {
		if (t->hdr.tag == ATAG_CMDLINE) {
			str = t->u.cmdline.cmdline;
			str = strstr(str, "fbmem=");
			if (str != NULL) {
				str += 6;
				pdata_fb[i++].res_size[0] = memparse(str, &str);
				while (*str == ',' &&
					i < ARRAY_SIZE(ntx_fb_data)) {
					str++;
					pdata_fb[i++].res_size[0] = memparse(str, &str);
				}
			}
			/* ION reserved memory */
			str = t->u.cmdline.cmdline;
			str = strstr(str, "ionmem=");
			if (str != NULL) {
				str += 7;
				imx_ion_data.heaps[0].size = memparse(str, &str);
			}
			/* Primary framebuffer base address */
			str = t->u.cmdline.cmdline;
			str = strstr(str, "fb0base=");
			if (str != NULL) {
				str += 8;
				pdata_fb[0].res_base[0] =
						simple_strtol(str, &str, 16);
			}
			/* GPU reserved memory */
			str = t->u.cmdline.cmdline;
			str = strstr(str, "gpumem=");
			if (str != NULL) {
				str += 7;
				imx6q_gpu_pdata.reserved_mem_size = memparse(str, &str);
			}
			break;
		}
	}
}

#if 0
static struct mipi_csi2_platform_data mipi_csi2_pdata = {
	.ipu_id	 = 1,
	.csi_id = 1,
	.v_channel = 0,
	.lanes = 2,
	.dphy_clk = "mipi_pllref_clk",
	.pixel_clk = "emi_clk",
};
#endif

static int __init caam_setup(char *__unused)
{
	caam_enabled = 1;
	return 1;
}
early_param("caam", caam_setup);

#if 0
#define SNVS_LPCR 0x38
static void mx6_snvs_poweroff(void)
{

	void __iomem *mx6_snvs_base =  MX6_IO_ADDRESS(MX6Q_SNVS_BASE_ADDR);
	u32 value;
	value = readl(mx6_snvs_base + SNVS_LPCR);
	/*set TOP and DP_EN bit*/
	writel(value | 0x60, mx6_snvs_base + SNVS_LPCR);
}
#endif

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

/*!
 * Board specific initialization.
 */
static void __init mx6_ntx_board_init(void)
{
	int i;
//	int ret;
	struct clk *clko, *clko2;
	struct clk *new_parent;
	int rate;
	struct platform_device *voutdev;

	_parse_cmdline();

	mxc_iomux_v3_setup_multiple_pads(mx6q_ntx_pads,
		ARRAY_SIZE(mx6q_ntx_pads));

	mxc_iomux_set_gpr_register(1, 21, 1, 1);
	
	gp_reg_id = ntx_dvfscore_data.reg_id;
	soc_reg_id = ntx_dvfscore_data.soc_id;
	pu_reg_id = ntx_dvfscore_data.pu_id;
	mx6q_ntx_init_uart();
	imx6x_add_ram_console();

	gpio_request(NTX_VMAX_12V_EN, "vmax_12v_en");
	gpio_direction_output(NTX_VMAX_12V_EN, 1);

	/*add bt support*/
//	mxc_register_device(&mxc_bt_rfkill, &mxc_bt_rfkill_data);
	imx6q_add_mxc_hdmi_core(&hdmi_core_data);

	imx6q_add_ipuv3(0, &ipu_data[0]);
	imx6q_add_ipuv3(1, &ipu_data[1]);
	for (i = 0; i < 4 && i < ARRAY_SIZE(ntx_fb_data); i++)
		imx6q_add_ipuv3fb(i, &ntx_fb_data[i]);

	imx6q_add_vdoa();
//	imx6q_add_mipi_dsi(&mipi_dsi_pdata);
	imx6q_add_lcdif(&lcdif_data);
	mxc_iomux_set_gpr_register(3, 6, 2, 2); 	// select ipu1-di0 for lvds0
	imx6q_add_ldb(&ldb_data);
	voutdev = imx6q_add_v4l2_output(0);
	if (vout_mem.res_msize && voutdev) {
		dma_declare_coherent_memory(&voutdev->dev,
					    vout_mem.res_mbase,
					    vout_mem.res_mbase,
					    vout_mem.res_msize,
					    (DMA_MEMORY_MAP |
					     DMA_MEMORY_EXCLUSIVE));
	}
//	imx6q_add_v4l2_capture(0, &capture_data[0]);
//	imx6q_add_v4l2_capture(1, &capture_data[1]);
//	imx6q_add_mipi_csi2(&mipi_csi2_pdata);
//	imx6q_add_imx_snvs_rtc();
	
	if (1 == caam_enabled)
		imx6q_add_imx_caam();

//	imx6q_add_device_gpio_leds();

	imx6q_add_imx_i2c(0, &mx6q_ntx_i2c_data);
	imx6q_add_imx_i2c(1, &mx6q_ntx_i2c_data);
	imx6q_add_imx_i2c(2, &mx6q_ntx_i2c_data);
	i2c_register_board_info(0, mxc_i2c0_board_info,
			ARRAY_SIZE(mxc_i2c0_board_info));
	i2c_register_board_info(1, mxc_i2c1_board_info,
			ARRAY_SIZE(mxc_i2c1_board_info));
	i2c_register_board_info(2, mxc_i2c2_board_info,
			ARRAY_SIZE(mxc_i2c2_board_info));
			
	platform_device_register(&ntx_device_rtc);
	
	/* SPI */
//	imx6q_add_ecspi(0, &mx6q_ntx_spi_data);
//	spi_device_init();

	gpio_request(NTX_PWR_EN2, "pwr_en2");
	gpio_direction_output(NTX_PWR_EN2, 1);

	gpio_request(NTX_HDMI_PW_EN, "hdmi_pw_en");
	gpio_direction_output(NTX_HDMI_PW_EN, 1);
	imx6q_add_mxc_hdmi(&hdmi_data);

	gpio_request(NTX_WIFI_RST, "wifi_rst");
	gpio_direction_output(NTX_WIFI_RST, 0);
	gpio_request(NTX_WIFI_3V3_ON, "wifi_3v3_on");
	gpio_request(NTX_WIFI_INT, "wifi_int");
	gpio_direction_input(NTX_WIFI_INT);
	_ntx_wifi_power_ctrl (0);

	gpio_request(NTX_RS232_RST, "rs232_rst");
	gpio_direction_output(NTX_RS232_RST, 1);
	gpio_request(NTX_USBHUB1_RST, "usb_hub1_rst");
	gpio_direction_input(NTX_USBHUB1_RST);
	gpio_request(NTX_USBHUB2_RST, "usb_hub2_rst");
	gpio_direction_input(NTX_USBHUB2_RST);
	gpio_request(NTX_RGMII_RST, "rgmii_rst");
	gpio_direction_output(NTX_RGMII_RST, 1);
	
	gpio_request(NTX_VGA_BLANK, "vga_blank");
	gpio_direction_output(NTX_VGA_BLANK, 1);
	gpio_request(NTX_VGA_PSAVE, "vga_psave");
	gpio_direction_output(NTX_VGA_PSAVE, 1);
	gpio_request(NTX_LCD_BL_EN, "lcd_bl_en");
	gpio_direction_output(NTX_LCD_BL_EN, 1);

	imx6q_add_anatop_thermal_imx(1, &mx6q_ntx_anatop_thermal_data);
	imx6_init_fec(fec_data);
//#ifdef CONFIG_MX6_ENET_IRQ_TO_GPIO
	/* Make sure the IOMUX_OBSRV_MUX1 is set to ENET_IRQ. */
//	mxc_iomux_set_specialbits_register(IOMUX_OBSRV_MUX1_OFFSET,
//		OBSRV_MUX1_ENET_IRQ, OBSRV_MUX1_MASK);
//#endif

	imx6q_add_pm_imx(0, &mx6q_ntx_pm_data);

	gpio_request(IMX_GPIO_NR(3, 12), "boot_emmc");
	gpio_direction_input(IMX_GPIO_NR(3, 12));
	
	if(gpio_get_value (IMX_GPIO_NR(3, 12))) {
		printk ("[[[[ Boot from eMMC ]]]]\n");	
		imx6q_add_sdhci_usdhc_imx(2, &mx6q_ntx_sd3_data);
		imx6q_add_sdhci_usdhc_imx(0, &mx6q_ntx_sd1_data);
	}
	else {
		printk ("[[[[ Boot from sd ]]]]\n");	
		imx6q_add_sdhci_usdhc_imx(0, &mx6q_ntx_sd1_data);
		imx6q_add_sdhci_usdhc_imx(2, &mx6q_ntx_sd3_data);
	}
	imx6q_add_sdhci_usdhc_imx(3, &mx6q_ntx_sd4_data);
	imx_add_viv_gpu(&imx6_gpu_data, &imx6q_gpu_pdata);
	imx6q_ntx_init_usb();
	/* SATA is not supported by MX6DL/Solo */
	if (cpu_is_mx6q()) {
#ifdef CONFIG_SATA_AHCI_PLATFORM
		imx6q_add_ahci(0, &mx6q_ntx_sata_data);
#else
		mx6q_ntx_sata_init(NULL,
			(void __iomem *)ioremap(MX6Q_SATA_BASE_ADDR, SZ_4K));
#endif
	}
	imx6q_add_vpu();
	imx6q_init_audio();
	platform_device_register(&ntx_vmmc_reg_devices);
	imx_asrc_data.asrc_core_clk = clk_get(NULL, "asrc_clk");
	imx_asrc_data.asrc_audio_clk = clk_get(NULL, "asrc_serial_clk");
	imx6q_add_asrc(&imx_asrc_data);

	/*
	 * Disable HannStar touch panel CABC function,
	 * this function turns the panel's backlight automatically
	 * according to the content shown on the panel which
	 * may cause annoying unstable backlight issue.
	 */
#if 0
	gpio_request(NTX_CABC_EN0, "cabc-en0");
	gpio_direction_output(NTX_CABC_EN0, 0);
	gpio_request(NTX_CABC_EN1, "cabc-en1");
	gpio_direction_output(NTX_CABC_EN1, 0);
#endif

#ifdef CONFIG_HAVE_EPIT
	imx6q_add_mxc_epit(0);
	imx6q_add_mxc_epit(1);
#endif

	imx6q_add_mxc_pwm(0);
	imx6q_add_mxc_pwm(1);
	imx6q_add_mxc_pwm(2);
	imx6q_add_mxc_pwm(3);
	imx6q_add_mxc_pwm_backlight(0, &mx6_ntx_pwm_backlight_data);

	imx6q_add_otp();
	imx6q_add_viim();
	imx6q_add_imx2_wdt(0, NULL);
	imx6q_add_dma();

	imx6q_add_dvfs_core(&ntx_dvfscore_data);

	if (imx_ion_data.heaps[0].size)
		imx6q_add_ion(0, &imx_ion_data,
			sizeof(imx_ion_data) + sizeof(struct ion_platform_heap));

	imx6q_add_device_buttons();

#if 0
	/* enable sensor 3v3 and 1v8 */
	gpio_request(NTX_SENSOR_EN, "sensor-en");
	gpio_direction_output(NTX_SENSOR_EN, 1);

	/* enable ecompass intr */
	gpio_request(NTX_eCOMPASS_INT, "ecompass-int");
	gpio_direction_input(NTX_eCOMPASS_INT);
	/* enable light sensor intr */
	gpio_request(NTX_ALS_INT, "als-int");
	gpio_direction_input(NTX_ALS_INT);
#endif

//	mxc_iomux_v3_setup_multiple_pads(mx6q_ntx_uart_pads,
//		ARRAY_SIZE(mx6q_ntx_uart_pads));

	gpio_request(NTX_DB_PWR_ON, "ntx_db_pwr_on");
	gpio_direction_output(NTX_DB_PWR_ON,1);
	gpio_request(NTX_CASH_12V, "ntx_cash_12v");
	gpio_direction_output(NTX_CASH_12V, 1);
	gpio_request(NTX_CASH_N12V_EN, "ntx_cash_N12v_en");
	gpio_direction_output(NTX_CASH_N12V_EN, 1);
	gpio_request(NTX_CASH_24V, "ntx_cash_24v");
	gpio_direction_output(NTX_CASH_24V, 1);
	gpio_request(NTX_CASH_OPEN, "ntx_cash_open");
	gpio_direction_input(NTX_CASH_OPEN);
	ntx_misc_info.acin_gpio     = 0;
	ntx_misc_info.chg_gpio      = 0;
	ntx_misc_info.cd_12V_gpio      = NTX_CASH_12V;
	ntx_misc_info.cd_N12V_EN_gpio      = NTX_CASH_N12V_EN;
	ntx_misc_info.cd_24V_gpio      = NTX_CASH_24V;
	ntx_misc_info.cd_open_gpio     = NTX_CASH_OPEN;
	platform_device_register(&ntx_charger);

	gpio_request(NTX_AD_AMP_CTRL, "ntx_ad_amp_ctrl");
	gpio_direction_output(NTX_AD_AMP_CTRL,1);
	gpio_request(NTX_TOUCH_RESET, "ntx_touch_rst");
	gpio_direction_output(NTX_TOUCH_RESET, 0);
	
	imx6q_add_hdmi_soc();
	imx6q_add_hdmi_soc_dai();

	/*
	ret = gpio_request_array(mx6q_ntx_flexcan_gpios,
			ARRAY_SIZE(mx6q_ntx_flexcan_gpios));
	if (ret)
		pr_err("failed to request flexcan1-gpios: %d\n", ret);
	else
		imx6q_add_flexcan0(&mx6q_ntx_flexcan0_pdata);
	*/

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

	/* Enable Aux_5V */
//	gpio_request(NTX_AUX_5V_EN, "aux_5v_en");
//	gpio_direction_output(NTX_AUX_5V_EN, 1);
//	gpio_set_value(NTX_AUX_5V_EN, 1);

//	gps_power_on(true);
	/* Register charger chips */
//	platform_device_register(&ntx_max8903_charger_1);
//	pm_power_off = mx6_snvs_poweroff;
	imx6q_add_busfreq();

	imx6_add_armpmu();
	imx6q_add_perfmon(0);
	imx6q_add_perfmon(1);
	imx6q_add_perfmon(2);
	
	_ntx_wifi_power_ctrl (1);
	gpio_direction_output(NTX_TOUCH_RESET, 1);
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
	early_console_setup(UART2_BASE_ADDR, uart_clk);
}

static struct sys_timer mx6_ntx_timer = {
	.init   = mx6_ntx_timer_init,
};

static void __init mx6q_ntx_reserve(void)
{
	phys_addr_t phys;
	int i, fb0_reserved = 0, fb_array_size;

	/*
	 * Reserve primary framebuffer memory if its base address
	 * is set by kernel command line.
	 */
	fb_array_size = ARRAY_SIZE(ntx_fb_data);
	if (fb_array_size > 0 && ntx_fb_data[0].res_base[0] &&
	    ntx_fb_data[0].res_size[0]) {
		if (ntx_fb_data[0].res_base[0] > SZ_2G)
			printk(KERN_INFO"UI Performance downgrade with FB phys address %x!\n",
			    ntx_fb_data[0].res_base[0]);
		memblock_reserve(ntx_fb_data[0].res_base[0],
				 ntx_fb_data[0].res_size[0]);
		memblock_remove(ntx_fb_data[0].res_base[0],
				ntx_fb_data[0].res_size[0]);
		ntx_fb_data[0].late_init = true;
		ipu_data[ldb_data.ipu_id].bypass_reset = true;
		fb0_reserved = 1;
	}
	for (i = fb0_reserved; i < fb_array_size; i++)
		if (ntx_fb_data[i].res_size[0]) {
			/* Reserve for other background buffer. */
			phys = memblock_alloc_base(ntx_fb_data[i].res_size[0],
						SZ_4K, SZ_2G);
			memblock_remove(phys, ntx_fb_data[i].res_size[0]);
			ntx_fb_data[i].res_base[0] = phys;
		}

#ifdef CONFIG_ANDROID_RAM_CONSOLE
	phys = memblock_alloc_base(SZ_1M, SZ_4K, SZ_1G);
	memblock_remove(phys, SZ_1M);
	memblock_free(phys, SZ_1M);
	ram_console_resource.start = phys;
	ram_console_resource.end   = phys + SZ_1M - 1;
#endif

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

	if (vout_mem.res_msize) {
		phys = memblock_alloc_base(vout_mem.res_msize,
					   SZ_4K, SZ_1G);
		memblock_remove(phys, vout_mem.res_msize);
		vout_mem.res_mbase = phys;
	}
}

/*
 * initialize __mach_desc_MX6Q_NTX data structure.
 */
MACHINE_START(MX6Q_NTX, "Freescale i.MX 6Quad/DualLite/Solo NTX Board")
	/* Maintainer: Freescale Semiconductor, Inc. */
	.boot_params = MX6_PHYS_OFFSET + 0x100,
	.fixup = fixup_mxc_board,
	.map_io = mx6_map_io,
	.init_irq = mx6_init_irq,
	.init_machine = mx6_ntx_board_init,
	.timer = &mx6_ntx_timer,
	.reserve = mx6q_ntx_reserve,
MACHINE_END
