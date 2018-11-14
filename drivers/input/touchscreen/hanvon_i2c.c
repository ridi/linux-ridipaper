/*
 *
 * Electromagnetic Pen I2C Driver for Hanvon
 *
 * Copyright (C) 1999-2012  Hanvon Technology Inc.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * !!!!!!!!!!!!!! NOTICE !!!!!!!!!!!!!!!!
 * Nvidia tegra 2 ventana demo board.
 * OS: android 4.0.3
 * version: 0.4.0
 * Features:
 * 		1. firmware update function
 *		2. work with calibration App
 *		3. add side key function
 * Updated: 2014/12/11
 */
#include <linux/module.h>
#include <linux/delay.h>
//#include <linux/earlysuspend.h>
#include <linux/device.h>
#include <linux/hrtimer.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/async.h>
//#include <mach/iomux.h>
#include <linux/irq.h>
//#include <mach/board.h>
#include <linux/workqueue.h>
#include <linux/proc_fs.h>
#include <linux/input/mt.h>
#include <linux/gpio.h>
#include <linux/version.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/of_gpio.h>
//#include "flag.h"

#include "../../../arch/arm/mach-mx6/ntx_hwconfig.h"
//#include "../../../arch/arm/mach-mx6/board-mx6sl_ntx.h"

extern volatile NTX_HWCONFIG *gptHWCFG;

#define HW0868_CALIBRATE		1
static unsigned long gdwScreenMaxY=1080;
static unsigned long gdwScreenMaxX=1440;

#define CHIP_NAME						"Hanvon0868"
#define MAX_EVENTS						10
//#define SCR_X						1920//	1280
//#define SCR_Y						1200//	800
#define SCR_X						gdwScreenMaxX//	1280
#define SCR_Y						gdwScreenMaxY//	800
#define MAX_X						0x27de
#define MAX_Y						0x1cfe
#define MAX_PRESSURE					1024
#define MAX_PACKET_SIZE					7

/* if uncomment this definition, calibrate function is enabled. */

#define DEBUG_SHOW_RAW					0X00000001
#define DEBUG_SHOW_COORD				0X00000010

//#define UPDATE_SLAVE_ADDR				0x34
#define UPDATE_SLAVE_ADDR                             0x18



#define HW0868_CMD_RESET				0x08680000
#define HW0868_CMD_CONFIG_HIGH			0x08680001
#define HW0868_CMD_CONFIG_LOW			0x08680002
#define HW0868_CMD_UPDATE				0x08680003
#define HW0868_CMD_GET_VERSION			0x08680004
#define HW0868_CMD_CALIBRATE			0x08680005

/* define pen flags, 7-bytes protocal. */
#define PEN_POINTER_UP					0xa0
#define PEN_POINTER_DOWN				0xa1
#define PEN_BUTTON_UP					0xa2
#define PEN_BUTTON_DOWN					0xa3
#define PEN_RUBBER_UP					0xa4
#define PEN_RUBBER_DOWN					0xa5
#define PEN_ALL_LEAVE					0xe0

 int gpio_rst=0;
 int gpio_cfg=0;
 int gpio_power=0;
 int gpio_irq=0;

#define HW0868_GPIO_RESET				gpio_rst
#define HW0868_GPIO_CONFIG			    gpio_cfg
#define HW0868_GPIO_POWER				gpio_power

struct hanvon_pen_data
{
    u16 		x;
    u16 		y;
    u16 		pressure;
    u8 			flag;
};

struct hanvon_i2c_chip {
	unsigned char * chipname;
	struct workqueue_struct *ktouch_wq;
	struct work_struct work_irq;
	struct mutex mutex_wq;
	struct i2c_client *client;
	unsigned char work_state;
	struct input_dev *p_inputdev;
	 int em_power;
	 int em_cfg;
	 int irq_pin;
	 int em_rst;
	 int irq;
	
};


/* global I2C client. */
static struct i2c_client *g_client;

/* when pen detected, this flag is set 1 */
//static volatile int isPenDetected = 0;
unsigned int isPenDetected = 0;
/* DEBUG micro, for user interface. */
static unsigned int debug = 0;

/* version number buffer */
static unsigned char ver_info[9] = {0};
static int ver_size = 9;

/* calibration parameter */
static bool isCalibrated = false;
static int a[7];
static int A = 65535, B = 0, C = 16, D = 0, E = 65535, F = 0, scale = 65536;

#define hw0868_dbg_raw(fmt, args...)        \
	    if(debug & DEBUG_SHOW_RAW) \
        printk(KERN_INFO "[HW0868 raw]: "fmt, ##args);
#define hw0868_dbg_coord(fmt, args...)    \
        printk(KERN_INFO "[HW0868 coord]: "fmt, ##args);

static struct i2c_device_id hanvon_i2c_idtable[] = {
	{ "hanvon_0868_i2c", 0 }, 
	{ } 
};

static void hw0868_reset(void)
{
	printk(KERN_INFO "Hanvon 0868 reset!\n");
	//tegra_gpio_enable(HW0868_GPIO_RESET);
	gpio_direction_output(HW0868_GPIO_RESET, 0);
	mdelay(50);
	gpio_direction_output(HW0868_GPIO_RESET, 1);
	mdelay(50);
}
/*
static void hw0868_set_power(int i)
{
	printk(KERN_INFO "Hanvon 0868 set power (%d)\n", i);
	if (i == 0)
		gpio_direction_output(HW0868_GPIO_POWER, 0);
	if (i == 1)
		gpio_direction_output(HW0868_GPIO_POWER, 1);
}
*/
static void hw0868_set_config_pin(int i)
{
	printk(KERN_INFO "Config pin status(%d)\n", i);
	//tegra_gpio_enable(HW0868_GPIO_CONFIG);
	if (i == 0)
		gpio_direction_output(HW0868_GPIO_CONFIG, 0);
	if (i == 1)
		gpio_direction_output(HW0868_GPIO_CONFIG, 1);
}

static int hw0868_get_version(struct i2c_client *client)
{
	int ret = -1;
	unsigned char ver_cmd[] = {0xcd, 0x5f};
	//hw0868_reset();
	ret = i2c_master_send(client, ver_cmd, 2);
	if (ret < 0)
	{
		printk(KERN_INFO "Get version ERROR!\n");
		return ret;
	}
	return ret;
}

static int read_calibrate_param(void)
{
	mm_segment_t old_fs;
	struct file *file = NULL;
	printk(KERN_INFO "kernel read calibrate param.\n");
	old_fs = get_fs();
	set_fs(get_ds());
	file = filp_open("/data/calibrate", O_RDONLY, 0);
	if (file == NULL)
		return -1;
	if (file->f_op->read == NULL)
		return -1;

	// TODO: read file
	if (file->f_op->read(file, (unsigned char*)a, sizeof(int)*7, &file->f_pos) == 28)
	{
		printk(KERN_INFO "calibrate param: %d, %d, %d, %d, %d, %d, %d\n", a[0], a[1], a[2], a[3], a[4], a[5], a[6]);
		A = a[1];
		B = a[2];
		C = a[0];
		D = a[4];
		E = a[5];
		F = a[3];
		scale = a[6];
		isCalibrated = true;
	}
	else
	{
		filp_close(file, NULL);
		set_fs(old_fs);
		return -1;
	}

	filp_close(file, NULL);
	set_fs(old_fs);
	return 0;
}

int fw_i2c_master_send(const struct i2c_client *client, const char *buf, int count)
{
	int ret;
	struct i2c_adapter *adap = client->adapter;
	struct i2c_msg msg;

	msg.addr = UPDATE_SLAVE_ADDR;
	msg.flags = client->flags & I2C_M_TEN;
	msg.len = count;
	msg.buf = (char *)buf;

	ret = i2c_transfer(adap, &msg, 1);
	printk(KERN_INFO "[hanvon 0868 update] fw_i2c_master_send  ret = %d\n", ret);
	/* 
	 * If everything went ok (i.e. 1 msg transmitted), return #bytes
	 * transmitted, else error code.
	 */
	return (ret == 1) ? count : ret;
}

int fw_i2c_master_recv(const struct i2c_client *client, char *buf, int count)
{
	struct i2c_adapter *adap = client->adapter;
	struct i2c_msg msg;
	int ret;

	msg.addr = UPDATE_SLAVE_ADDR;
	msg.flags = client->flags & I2C_M_TEN;
	msg.flags |= I2C_M_RD;
	msg.len = count;
	msg.buf = buf;

	ret = i2c_transfer(adap, &msg, 1);
	printk(KERN_INFO "[hanvon 0868 update] fw_i2c_master_recv  ret = %d\n", ret);
	/*
	 * If everything went ok (i.e. 1 msg received), return #bytes received,
	 * else error code.
	 */
	return (ret == 1) ? count : ret;
}


ssize_t hw0868_i2c_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count, i;
	unsigned char csw_packet[13] = {1};
	printk(KERN_INFO "Receive CSW package.\n");
	count = fw_i2c_master_recv(g_client, csw_packet, 13);
	if (count < 0)
	{
		return -1;
	}
	printk(KERN_INFO "[num 01] read %d bytes.\n", count);
	for(i = 0; i < count; i++)
	{
		printk(KERN_INFO "%.2x \n", csw_packet[i]);
	}
	return sprintf(buf, "%s", csw_packet);
}

ssize_t hw0868_i2c_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	int cmd = *((int *)buf);
	printk(KERN_INFO "%x\n", buf[3]);
	printk(KERN_INFO "%x\n", buf[2]);
	printk(KERN_INFO "%x\n", buf[1]);
	printk(KERN_INFO "%x\n", buf[0]);
	printk(KERN_INFO "%s is called, count=%d.\n", __func__, (int )count);
	if ((count == 31) && (buf[1] == 0x57) && (buf[0] == 0x48))
	{
		printk(KERN_INFO "Send CBW package.\n");
		ret = fw_i2c_master_send(g_client, buf, count);
		return ret;
	}

	/* transfer file */
	if (count == 32)
	{
		printk(KERN_INFO "Transfer file.\n");
		ret = fw_i2c_master_send(g_client, buf, count);
		return ret;
	}
	
	if ((cmd & 0x08680000) != 0x08680000)
	{
		printk(KERN_INFO "Invalid command (0x%08x).\n", cmd);
		return -1;
	}

	switch(cmd)
	{
		case HW0868_CMD_RESET:
			printk(KERN_INFO "Command: reset.\n");
			hw0868_reset();
			break;
		case HW0868_CMD_CONFIG_HIGH:
			printk(KERN_INFO "Command: set config pin high.\n");
			hw0868_set_config_pin(1);
			break;
		case HW0868_CMD_CONFIG_LOW:
			printk(KERN_INFO "Command: set config pin low.\n");
			hw0868_set_config_pin(0);
			break;
		case HW0868_CMD_GET_VERSION:
			printk(KERN_INFO "Command: get firmware version.\n");
			hw0868_get_version(g_client);
			break;
		case HW0868_CMD_CALIBRATE:
			printk(KERN_INFO "Command: Calibrate.\n");
			read_calibrate_param();
			break;
	}
	return count;
}

DEVICE_ATTR(hw0868_entry, 0666, hw0868_i2c_show, hw0868_i2c_store);

/* get version */
ssize_t hw0868_version_show(struct device *dev, struct device_attribute *attr,char *buf)
{
	return sprintf(buf, "version number: %.2x %.2x %.2x %.2x %.2x %.2x\n", 
			ver_info[1], ver_info[2], ver_info[3],ver_info[4], ver_info[5], ver_info[6]);
}

ssize_t hw0868_version_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	return count;
}
DEVICE_ATTR(version, 0666, hw0868_version_show, hw0868_version_store);

MODULE_DEVICE_TABLE(i2c, hanvon_i2c_idtable);

static long hw0868_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}

static struct file_operations hanvon_cdev_fops = {
	.owner= THIS_MODULE,
	.unlocked_ioctl= hw0868_ioctl,
};

static struct miscdevice hanvon_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "hw0868",
	.fops = &hanvon_cdev_fops,
};

static struct input_dev * allocate_hanvon_input_dev(void)
{
	int ret;
	struct input_dev *p_inputdev=NULL;

	p_inputdev = input_allocate_device();
	if(p_inputdev == NULL)
	{
		return NULL;
	}

	p_inputdev->name = "Hanvon electromagnetic pen";
	p_inputdev->phys = "I2C";
	p_inputdev->id.bustype = BUS_I2C;
	
	set_bit(EV_ABS, p_inputdev->evbit);
	__set_bit(INPUT_PROP_DIRECT, p_inputdev->propbit);
	__set_bit(EV_ABS, p_inputdev->evbit);
	__set_bit(EV_KEY, p_inputdev->evbit);
	__set_bit(BTN_TOUCH, p_inputdev->keybit);
	__set_bit(BTN_STYLUS, p_inputdev->keybit);
	__set_bit(BTN_TOOL_PEN, p_inputdev->keybit);
	__set_bit(BTN_TOOL_RUBBER, p_inputdev->keybit);

#ifdef HW0868_CALIBRATE
	input_set_abs_params(p_inputdev, ABS_X, 0, SCR_X, 0, 0);
	input_set_abs_params(p_inputdev, ABS_Y, 0, SCR_Y, 0, 0);
#else
	input_set_abs_params(p_inputdev, ABS_X, 0, MAX_X, 0, 0);
	input_set_abs_params(p_inputdev, ABS_Y, 0, MAX_Y, 0, 0);
#endif
	
	input_set_abs_params(p_inputdev, ABS_PRESSURE, 0, MAX_PRESSURE, 0, 0);


#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
	input_set_events_per_packet(p_inputdev, MAX_EVENTS);
#endif

	ret = input_register_device(p_inputdev);
	if(ret) 
	{
		printk(KERN_INFO "Unable to register input device.\n");
		input_free_device(p_inputdev);
		p_inputdev = NULL;
	}
	
	return p_inputdev;
}

static struct hanvon_pen_data hanvon_get_packet(struct hanvon_i2c_chip *phic)
{
	struct hanvon_pen_data data = {0};
	struct i2c_client *client = phic->client;
	u8 x_buf[MAX_PACKET_SIZE];
	int count;
#ifdef HW0868_CALIBRATE //[
	int sum_x;
	int sum_y;
#endif //]HW0868_CALIBRATE
	do {
		//mdelay(2);
		count = i2c_master_recv(client, x_buf, MAX_PACKET_SIZE);
	}
	while(count == EAGAIN);
#if 0 //[
	printk(KERN_INFO "Reading data. %.2x %.2x %.2x %.2x %.2x %.2x %.2x, count=%d\n", 
				x_buf[0], x_buf[1], x_buf[2], x_buf[3], x_buf[4], 
				x_buf[5], x_buf[6], count);
#endif //]

	if (x_buf[0] == 0x80)
	{
		printk(KERN_INFO "Get version number ok!\n");
		memcpy(ver_info, x_buf, ver_size);
	}
	data.flag = x_buf[0];
	data.x |= ((x_buf[1]&0x7f) << 9) | (x_buf[2] << 2) | (x_buf[6] >> 5); // x
	data.y |= ((x_buf[3]&0x7f) << 9) | (x_buf[4] << 2) | ((x_buf[6] >> 3)&0x03); // y
	data.pressure |= ((x_buf[6]&0x07) << 7) | (x_buf[5]);  // pressure

#ifdef HW0868_CALIBRATE

	/* transform raw coordinate to srceen coord */
#if 1
	sum_x = ((data.x * SCR_X)/MAX_X);
	sum_y = ((data.y * SCR_Y)/MAX_Y);
	//printk("x,y mapping (%d,%d) => (%d,%d)\n",data.x,data.y,sum_x,sum_y);
	data.x = (unsigned short)(sum_x);
	data.y = (unsigned short)(sum_y);
#else
	data.x = data.x / MAX_X * SCR_X;
	data.y = data.y / MAX_Y * SCR_Y;
#endif

	/* perform calibrate */
	if (isCalibrated)
	{
		sum_x = data.x*A + data.y*B + C;
		if ((sum_x % scale) > 32768)
		{
			data.x = (sum_x >> 16) + 1;
		}
		else
		{
			data.x = sum_x >> 16;
		}
		
		sum_y = data.x*D + data.y*E + F;
		if ((sum_y % scale) > 32768)
		{
			data.y = (sum_y >> 16) + 1;
		}
		else
		{
			data.y = sum_y >> 16;
		}
	}

#endif 

	return data;
}

static int hanvon_report_event(struct hanvon_i2c_chip *phic)
{
	struct hanvon_pen_data data = {0};
	data = hanvon_get_packet(phic);
	if (data.flag == 0x80)
	{
		return 0;
	}
	//data.y = MAX_Y-data.y;
	//data.x = MAX_X-data.x;
#if 0
	hw0868_dbg_coord(KERN_INFO "x=%d\ty=%d\tpressure=%d\tflag=%d\n",data.x, data.y, data.pressure, data.flag);		
#endif
	//if(data.pressure>0)data.flag|=(0x01);
        //else data.flag &=~(0x01);
	

	switch(data.flag)
	{
		/* side key events */
		case PEN_BUTTON_DOWN:
		{
			input_report_abs(phic->p_inputdev, ABS_X, data.x);
			input_report_abs(phic->p_inputdev, ABS_Y, data.y);
			input_report_abs(phic->p_inputdev, ABS_PRESSURE, data.pressure);
			input_report_key(phic->p_inputdev, BTN_TOUCH, 1);
			input_report_key(phic->p_inputdev, BTN_TOOL_PEN, 1);
			input_report_key(phic->p_inputdev, BTN_STYLUS, 1);
			break;
		}
		case PEN_BUTTON_UP:
		{
			input_report_abs(phic->p_inputdev, ABS_X, data.x);
			input_report_abs(phic->p_inputdev, ABS_Y, data.y);
			input_report_abs(phic->p_inputdev, ABS_PRESSURE, data.pressure);
			input_report_key(phic->p_inputdev, BTN_TOUCH, 0);
			input_report_key(phic->p_inputdev, BTN_TOOL_PEN, 0);
			input_report_key(phic->p_inputdev, BTN_STYLUS, 0);
			break;
		}
		/* rubber events */
		case PEN_RUBBER_DOWN:
		{   
			input_report_abs(phic->p_inputdev, ABS_X, data.x);
			input_report_abs(phic->p_inputdev, ABS_Y, data.y);
			input_report_abs(phic->p_inputdev, ABS_PRESSURE, data.pressure);
			input_report_key(phic->p_inputdev, BTN_TOUCH, 1);
			input_report_key(phic->p_inputdev, BTN_TOOL_RUBBER, 1);
			break;
        	}
		case PEN_RUBBER_UP:
		{
			input_report_abs(phic->p_inputdev, ABS_X, data.x);
			input_report_abs(phic->p_inputdev, ABS_Y, data.y);
			input_report_abs(phic->p_inputdev, ABS_PRESSURE, data.pressure);
			input_report_key(phic->p_inputdev, BTN_TOUCH, 0);
			input_report_key(phic->p_inputdev, BTN_TOOL_RUBBER, 0);
			break;
		}
		/* pen pointer events */
		case PEN_POINTER_DOWN:
		{
			input_report_abs(phic->p_inputdev, ABS_X, data.x);
			input_report_abs(phic->p_inputdev, ABS_Y, data.y);
			input_report_abs(phic->p_inputdev, ABS_PRESSURE, data.pressure);
			input_report_key(phic->p_inputdev, BTN_TOUCH, 1);
			input_report_key(phic->p_inputdev, BTN_TOOL_PEN, 1);
			break;
		}
		case PEN_POINTER_UP:
		{
			input_report_abs(phic->p_inputdev, ABS_X, data.x);
			input_report_abs(phic->p_inputdev, ABS_Y, data.y);
			input_report_abs(phic->p_inputdev, ABS_PRESSURE, data.pressure);
			input_report_key(phic->p_inputdev, BTN_TOUCH, 0);
			if (isPenDetected == 0)
				input_report_key(phic->p_inputdev, BTN_TOOL_PEN, 1);
			isPenDetected = 1;
			break;
		}
		/* Leave the induction area. */
		case PEN_ALL_LEAVE:
		{
			input_report_abs(phic->p_inputdev, ABS_X, data.x);
			input_report_abs(phic->p_inputdev, ABS_Y, data.y);
			input_report_abs(phic->p_inputdev, ABS_PRESSURE, data.pressure);
			input_report_key(phic->p_inputdev, BTN_TOUCH, 0);
			input_report_key(phic->p_inputdev, BTN_TOOL_PEN, 0);
			input_report_key(phic->p_inputdev, BTN_STYLUS, 0);
			isPenDetected = 0;
			break;
		}
		default:
			printk(KERN_ERR "Hanvon stylus device[0868,I2C]: Invalid input event.\n");
	}
	input_sync(phic->p_inputdev);
	return 0;
}

static void hanvon_i2c_wq(struct work_struct *work)
{
	struct hanvon_i2c_chip *phid = container_of(work, struct hanvon_i2c_chip, work_irq);
	//struct i2c_client *client = phid->client;
	mutex_lock(&phid->mutex_wq);
	//msleep(20);
	hanvon_report_event(phid);
	schedule();
	mutex_unlock(&phid->mutex_wq);
	enable_irq(phid->irq); 
}
static irqreturn_t hanvon_i2c_interrupt(int irq, void *dev_id)
{
	struct hanvon_i2c_chip *phid = (struct hanvon_i2c_chip *)dev_id;
	//printk("============enter_interrupt=======\n");
	disable_irq_nosync(irq);
	queue_work(phid->ktouch_wq, &phid->work_irq);
	//printk(KERN_INFO "%s:Interrupt handled.\n", __func__);

	return IRQ_HANDLED;
}

static int hanvon_i2c_probe(struct i2c_client * client, const struct i2c_device_id * idp)
{
	int result = -1,rc;
	unsigned int en_flags,irq_flags;
	unsigned int  wake_flags,config_flags;
	struct hanvon_i2c_chip *hidp = NULL;
	struct device_node *np = client->dev.of_node;
	g_client = client;

	printk("======enter %s probe=======\n",__func__);

	switch(gptHWCFG->m_val.bDisplayResolution) {
	case 1: // 1024x758
		gdwScreenMaxY=758;
		gdwScreenMaxX=1024;
		break;
	case 2: // 1024x768
		gdwScreenMaxY=768;
		gdwScreenMaxX=1024;
		break;
	case 3: // 1440x1080
		gdwScreenMaxY=1080;
		gdwScreenMaxX=1440;
		break;
	case 4: // 1366x768
		gdwScreenMaxY=768;
		gdwScreenMaxX=1366;
		break;
	case 5: // 1448x1072
		gdwScreenMaxY=1072;
		gdwScreenMaxX=1448;
		break;
	case 6: // 1600x1200
		gdwScreenMaxY=1200;
		gdwScreenMaxX=1600;
		break;
	case 8: // 1872x1404
		gdwScreenMaxY=1404;
		gdwScreenMaxX=1872;
		break;
	default:
		gdwScreenMaxY=600;
		gdwScreenMaxX=800;
		break;
	}


	printk("i2c address = 0x%0x (%dx%d) \n",client->addr,(int)gdwScreenMaxX,(int)gdwScreenMaxY);
	hidp = (struct hanvon_i2c_chip*)kzalloc(sizeof(struct hanvon_i2c_chip), GFP_KERNEL);
	if(!hidp)
	{
		printk(KERN_INFO "request memory failed.\n");
		result = -ENOMEM;
		goto fail1;
	}


	
	/* setup input device. */
	hidp->p_inputdev = allocate_hanvon_input_dev();
	
	/* setup work queue. */
	hidp->client = client;
	hidp->ktouch_wq = create_singlethread_workqueue("hanvon0868");
	mutex_init(&hidp->mutex_wq);
	INIT_WORK(&hidp->work_irq, hanvon_i2c_wq);
	i2c_set_clientdata(client, hidp);
	//hidp->device_id = hidp->driver_data;
#ifdef CONFIG_OF //[
	hidp->em_power = of_get_named_gpio_flags(np, "em-power", 0, (enum of_gpio_flags *)&en_flags);
	hidp->irq_pin = of_get_named_gpio_flags(np, "em-gpio", 0, (enum of_gpio_flags *)&irq_flags);
	hidp->em_rst = of_get_named_gpio_flags(np, "reset-gpio", 0,(enum of_gpio_flags *) &wake_flags);
	hidp->em_cfg = of_get_named_gpio_flags(np, "em-config", 0,(enum of_gpio_flags *) &config_flags);
	if (gpio_is_valid(hidp->em_power)) {
		rc = devm_gpio_request_one(&client->dev, hidp->em_power, (en_flags & OF_GPIO_ACTIVE_LOW) ? GPIOF_OUT_INIT_LOW : GPIOF_OUT_INIT_HIGH, "em_0868 en pin");
		if (rc != 0) {
			dev_err(&client->dev, "em_0868 en pin error\n");
			result = -EIO;goto fail1;
		}
	} else {
		dev_info(&client->dev, "irq pin invalid\n");
	}
	if (gpio_is_valid(hidp->irq_pin)) {
		rc = devm_gpio_request_one(&client->dev, hidp->irq_pin, (irq_flags & OF_GPIO_ACTIVE_LOW) ? GPIOF_OUT_INIT_LOW : GPIOF_OUT_INIT_HIGH, "em_0868 irq pin");
		if (rc != 0) {
			dev_err(&client->dev, "em_0868 irq pin error\n");
			result = -EIO;goto fail1;
		}
	} else {
		dev_info(&client->dev, "irq pin invalid\n");
	}
    
	if (gpio_is_valid(hidp->em_rst)) {
		rc = devm_gpio_request_one(&client->dev, hidp->em_rst, (wake_flags & OF_GPIO_ACTIVE_LOW) ? GPIOF_OUT_INIT_LOW : GPIOF_OUT_INIT_HIGH, "em_0868 wake pin");
		if (rc != 0) {
			dev_err(&client->dev, "em_0868 wake pin error\n");
			result = -EIO;goto fail1;
		}
	} else {
		dev_info(&client->dev, "irq pin invalid\n");
	}

	if (gpio_is_valid(hidp->em_cfg)) {
		rc = devm_gpio_request_one(&client->dev, hidp->em_cfg, (config_flags & OF_GPIO_ACTIVE_LOW) ? GPIOF_OUT_INIT_LOW : GPIOF_OUT_INIT_HIGH, "em_0868 config_flags pin");
		gpio_direction_input(hidp->em_cfg);
		gpio_direction_output(hidp->em_cfg,0);
		if (rc != 0) {
			dev_err(&client->dev, "em_0868 config_flags pin error\n");
			result =  -EIO;goto fail1;

		}
	} else {
		dev_info(&client->dev, "irq pin invalid\n");
	}
#else //][!CONFIG_OF
	hidp->irq_pin = irq_to_gpio(client->irq);
	hidp->em_rst = client->dev.platform_data;

	printk("gpio irq=%d,rst=%d\n",hidp->irq_pin,hidp->em_rst);

#endif //] CONFIG_OF

	gpio_power = hidp->em_power;
	gpio_rst = hidp->em_rst;
	gpio_cfg = hidp->em_cfg; 
	gpio_irq = hidp->irq_pin;	
	hidp->irq=gpio_to_irq(hidp->irq_pin);
	

	// gallen add [
	hw0868_reset();
	// Check functionality
	if(!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_WORD_DATA)) {
		result = -EIO;goto fail1;
	}
	//] gallen add .



	/* request irq. */
	result = request_irq(hidp->irq, hanvon_i2c_interrupt, IRQF_DISABLED | IRQF_TRIGGER_LOW/* |IRQF_TRIGGER_FALLING*/ , client->name, hidp);
	if(result)
	{
		printk(KERN_INFO " Request irq(%d) failed\n", hidp->irq_pin);
		goto fail1;
	}
	/*  define a entry for update use.
	 *  register misc device  */
	result = misc_register(&hanvon_misc_dev);
	device_create_file(hanvon_misc_dev.this_device, &dev_attr_hw0868_entry);
	device_create_file(hanvon_misc_dev.this_device, &dev_attr_version);
	printk(KERN_INFO "%s done.\n", __func__);
	printk(KERN_INFO "Name of device: %s.\n", client->dev.kobj.name);

	
	/*//Try to get firmware version here!
	hw0868_get_version(client);
	*/
	
	return 0;
	
/*fail2:
	i2c_set_clientdata(client, NULL);
	destroy_workqueue(hidp->ktouch_wq);
	free_irq(client->irq, hidp);
	input_unregister_device(hidp->p_inputdev);
	hidp->p_inputdev = NULL;*/
fail1:
	if(hidp) {
		kfree(hidp);
		hidp = NULL;
	}
	return result;
}

static int hanvon_i2c_remove(struct i2c_client * client)
{
	return 0;
}

/*static int hanvon_i2c_suspend(struct i2c_client *client, pm_message_t mesg)
{
	reset hw0868 chip 
	hw0868_reset();
	return 0;
}
*/
/*static int hanvon_i2c_resume(struct i2c_client *client)
{
	 reset hw0868 chip 
	hw0868_reset();
	return 0;
}*/
#ifdef CONFIG_OF //[
static struct of_device_id em_of_match[] = {
	{ .compatible = "hanvon_0868_i2c" },
	{ }
};
#endif //]CONFIG_OF
static struct i2c_driver hanvon_i2c_driver = {
	.driver = {
		.name 	= "hanvon_0868_i2c",
		.owner          = THIS_MODULE,

#ifdef CONFIG_OF //[
		.of_match_table = of_match_ptr(em_of_match),
#endif //] CONFIG_OF

	},
	.probe		= hanvon_i2c_probe,
	.remove		= hanvon_i2c_remove,
	.id_table       = hanvon_i2c_idtable,
};

static int hw0868_i2c_init(void)
{
	printk(KERN_INFO "hw0868 chip initializing ....\n");
	return i2c_add_driver(&hanvon_i2c_driver);
}

static void hw0868_i2c_exit(void)
{
	printk(KERN_INFO "hw0868 driver exit.\n");
	i2c_del_driver(&hanvon_i2c_driver);
}

module_init(hw0868_i2c_init);
module_exit(hw0868_i2c_exit);

module_param(debug, uint, S_IRUGO | S_IWUSR);

MODULE_AUTHOR("Zhang Nian");
MODULE_DESCRIPTION("Hanvon Electromagnetic Pen");
MODULE_LICENSE("GPL");
