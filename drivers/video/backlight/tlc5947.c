/*
* Simple driver for Texas Instruments TLC5947 Backlight driver chip
* Copyright (C) 2012 Texas Instruments
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
*/
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/spi/spi.h>
#include <linux/backlight.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/platform_data/tlc5947.h>

#include "../../../arch/arm/mach-mx6/ntx_hwconfig.h"
#include "../../../arch/arm/mach-mx6/ntx_firmware.h"

#define DEFAULT_ON_RAMP_LVL	0
#define DEFAULT_OFF_RAMP_LVL	0
#define DEFAULT_UP_RAMP_LVL	0
#define DEFAULT_DN_RAMP_LVL	0

struct tlc5947_chip {
	struct device *dev;
#if 0
	struct delayed_work work;
	int irq;
	struct workqueue_struct *irqthread;
#endif
	struct spi_device *spi;
	struct backlight_device *bled;

	int gpio_power_on;
	int gpio_xlat;
	int gpio_blank;

	unsigned short out[24];
};

extern volatile NTX_HWCONFIG *gptHWCFG;
extern int gSleep_Mode_Suspend;

static struct tlc5947_chip *gpchip;

static int tlc5947_send (struct spi_device *spi, unsigned short *pBuf)
{
	struct spi_message msg;
	struct spi_transfer xfer = {
		.len		= 24*sizeof(unsigned short),
		.bits_per_word = 12,
		.tx_buf		= pBuf,
	};
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	return spi_sync(spi, &msg);
}

static int tlc5947_update (struct tlc5947_chip *pchip) 
{
	int isChipOn = 0;
	int i;
	unsigned short buf[24];
	static int isPowerOn;

	memset (buf, 0, 24*sizeof(unsigned short));
	for (i=0; i<8; i++) {
		if (pchip->out[i]) {
			isChipOn = 1;
		}
		buf[23-i] = pchip->out[i];
	}
	if (isChipOn) {
		gpio_direction_output (pchip->gpio_power_on, 1);
		gpio_direction_output (pchip->gpio_xlat, 0);
		if (!isPowerOn) {
			gpio_direction_output (pchip->gpio_blank, 1);
			msleep(20);
		}
		tlc5947_send (pchip->spi, buf);
		gpio_direction_output (pchip->gpio_xlat, 1);
		msleep(20);
		gpio_direction_output (pchip->gpio_xlat, 0);
		gpio_direction_output (pchip->gpio_blank, 0);
	}
	else {
		gpio_direction_output (pchip->gpio_blank, 0);
		gpio_direction_output (pchip->gpio_power_on, 0);
		gpio_direction_output (pchip->gpio_xlat, 0);
		gpio_direction_output (pchip->gpio_blank, 0);
	}
	isPowerOn = isChipOn;
}

/* initialize chip */
static int tlc5947_chip_init(struct tlc5947_chip *pchip)
{
	int rval;

	/* set boost control */
	memset (pchip->out, 0, 24*sizeof(unsigned short));
	tlc5947_update (pchip);

	return rval;
}

/* update and get brightness */
static int tlc5947_update_status(struct backlight_device *bl)
{
	int ret;
	int i;
	struct tlc5947_chip *pchip = bl_get_data(bl);

	printk("%s(%d) %s brgitness %d\n",__FUNCTION__,__LINE__,__FUNCTION__, bl->props.brightness);

	for (i=0; i<8; i++)
		pchip->out[i] = bl->props.brightness;
	tlc5947_update (pchip);

	return bl->props.brightness;
}

static int tlc5947_get_brightness(struct backlight_device *bl)
{
	int brightness, rval;
	struct tlc5947_chip *pchip = bl_get_data(bl);

	bl->props.brightness = brightness;
	return bl->props.brightness;
}

static const struct backlight_ops tlc5947_ops = {
	.update_status = tlc5947_update_status,
	.get_brightness = tlc5947_get_brightness,
};

static ssize_t out_gs_get(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct tlc5947_chip *pchip = dev_get_drvdata(dev);
	sprintf (buf, "%d %d %d %d %d %d %d %d", \
		pchip->out[0], pchip->out[1], pchip->out[2], pchip->out[3], \
		pchip->out[4], pchip->out[5], pchip->out[6], pchip->out[7] );
	return strlen (buf);
}

static ssize_t out_gs_set(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct tlc5947_chip *pchip = dev_get_drvdata(dev);

	if (count) {
		char channel = buf[0]-'0';
		if (8 > channel) {
			int duty = simple_strtol(&buf[2], NULL, 10);
			printk ("Set channel %d to %d\n", channel, duty);
			pchip->out[channel] = duty;
			tlc5947_update (pchip);
		}
		else {
			printk ("Wrong hannel No.\n");
		}
	}
	else {
		printk ("echo \"ch duty\" to set duty to channel.\n");
	}
	return count;
}

static DEVICE_ATTR (out, 0644, out_gs_get, out_gs_set);

static int tlc5947_backlight_register(struct tlc5947_chip *pchip)
{
	struct backlight_properties props;
	int rval;
	
	props.type = BACKLIGHT_RAW;
	props.brightness = 0;
	props.max_brightness = 4096;

	pchip->bled =
		backlight_device_register(TLC5947_NAME, pchip->dev, pchip,
							       &tlc5947_ops, &props);
	if (IS_ERR(pchip->bled))
		return PTR_ERR(pchip->bled);

	rval = device_create_file(&pchip->bled->dev, &dev_attr_out);
	if (rval < 0) {
		dev_err(&pchip->bled->dev, "fail : tlc5947 out create.\n");
		return rval;
	}

	return 0;
}

static int tlc5947_probe(struct spi_device *spi)
{
	struct tlc5947_platform_data *pdata = spi->dev.platform_data;
	struct tlc5947_chip *pchip;
	int rval;

	pchip = devm_kzalloc(&spi->dev, sizeof(struct tlc5947_chip),
			     GFP_KERNEL);
	if (!pchip)
		return -ENOMEM;
	pchip->dev = &spi->dev;
	spi->bits_per_word = 12;
	spi->mode = SPI_MODE_0; 	// POL=0, PHA=0

	rval = spi_setup(spi);
	if (rval < 0) {
		dev_err (&pchip->dev, "spi setup error!");
		return -ENOMEM;
	}
	pchip->spi = spi;
	pchip->gpio_power_on = pdata->gpio_power_on;
	pchip->gpio_xlat = pdata->gpio_xlat;
	pchip->gpio_blank = pdata->gpio_blank;

	gpio_request (pchip->gpio_power_on, "TLC5947_EN");
	gpio_request (pchip->gpio_xlat, "TLC5947_XLAT");
	gpio_request (pchip->gpio_blank, "TLC5947_BLANK");

	/* backlight register */
	rval = tlc5947_backlight_register(pchip);
	if (rval < 0) {
		dev_err(&spi->dev, "fail : backlight register.\n");
		return rval;
	}

	rval = tlc5947_chip_init(pchip);
	if (rval < 0) {
		dev_err(&spi->dev, "fail : init chip\n");
		return rval;
	}

	dev_set_drvdata(&spi->dev, pchip);

	gpchip = pchip;
	dev_info(&spi->dev, "TLC5947 backlight register OK.\n");
	return 0;
}

static int tlc5947_remove(struct spi_device *spi)
{
	int rval;
	struct tlc5947_chip *pchip = dev_get_drvdata(&spi->dev);

	return 0;
}

int tlc5947_suspend(struct spi_device *spi, pm_message_t mesg)
{
	struct tlc5947_chip *pchip = dev_get_drvdata(&spi->dev);
	if(gSleep_Mode_Suspend) {
	}
	return 0;
}

int tlc5947_resume(struct spi_device *spi)
{
	struct tlc5947_chip *pchip = dev_get_drvdata(&spi->dev);
	if(gSleep_Mode_Suspend) {
		if(pchip) {
			tlc5947_chip_init(pchip);
		}
	}
	return 0;
}

static struct spi_driver tlc5947_spi_driver = {
	.driver = {
		   .name = TLC5947_NAME,
		   },
	.probe = tlc5947_probe,
	.remove = tlc5947_remove,
	.suspend = tlc5947_suspend,
	.resume = tlc5947_resume,
};

static int __init tlc5947_init(void)
{
	return spi_register_driver(&tlc5947_spi_driver);
}

static void __exit tlc5947_exit(void)
{
	spi_unregister_driver(&tlc5947_spi_driver);
}
module_init(tlc5947_init);
module_exit(tlc5947_exit);

MODULE_DESCRIPTION("Texas Instruments Backlight driver for TLC5947");
MODULE_LICENSE("GPL v2");
