

/*
 *
 * Purpose : SY7636 driver
 * Author : Gallen Lin
 * versions :
 *
 */ 

#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/semaphore.h>
#include <linux/wait.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/interrupt.h>


#include <mach/hardware.h>
#include <mach/gpio.h>

#if defined(CONFIG_MACH_MX6DL_NTX) //[
	#define SY7636_PLATFORM_MX6DL		1
	#define SY7636_PLATFORM_MX6		1
#elif defined(CONFIG_MACH_MX6SL_NTX)//[
	#define SY7636_PLATFORM_MX6SL		1
	#define SY7636_PLATFORM_MX6		1
#endif//]CONFIG_MACH_MX6SL_NTX

#if defined(SY7636_PLATFORM_MX6DL)//[
	#include <mach/iomux-mx6dl.h>
#elif defined(SY7636_PLATFORM_MX6SL)//[
	#include <mach/iomux-mx6sl.h>
#else 
	#error "Not support platform !"
#endif //] 

#include "ntx_hwconfig.h"
#include "fake_s1d13522.h"

#define GDEBUG	1
#include <linux/gallen_dbg.h>

#include "lk_sy7636.h"


#define DRIVER_NAME "SY7636"

#define INIT_POWER_STATE	0

#define USE_EPD_PWRSTAT		1



#if defined(SY7636_PLATFORM_MX6DL)
//
#define GPIO_SY7636_VIN_PADCFG		MX6DL_PAD_EIM_D29__GPIO_3_29
#define GPIO_SY7636_VIN					IMX_GPIO_NR(3,29) // PWRALL
#define GPIO_SY7636_EN_PADCFG			MX6DL_PAD_EIM_A19__GPIO_2_19	
#define GPIO_SY7636_EN					IMX_GPIO_NR(2,19) // EPDC_PWRCTRL1
#define GPIO_SY7636_VCOM_PADCFG			MX6DL_PAD_EIM_D17__GPIO_3_17	
#define GPIO_SY7636_VCOM				IMX_GPIO_NR(3,17) // EPDC_VCOM0

//#define GPIO_SY7636_EP_3V3_IN								
//#define GPIO_SY7636_EP_3V3_IN_PADCFG				

#define GPIO_SY7636_PWRGOOD							IMX_GPIO_NR(2,21) // EPDC_PWRSTAT
#define GPIO_SY7636_PWRGOOD_GPIO_PADCFG			MX6DL_PAD_EIM_A17__GPIO_2_21_FLOAT
#define GPIO_SY7636_PWRGOOD_INT_PADCFG			MX6DL_PAD_EIM_A17__GPIO_2_21_PUINT

#elif defined(SY7636_PLATFORM_MX6SL)
//
#define GPIO_SY7636_VIN_PADCFG		MX6SL_PAD_EPDC_PWRWAKEUP__GPIO_2_14
#define GPIO_SY7636_VIN					IMX_GPIO_NR(2,14)
#define GPIO_SY7636_EN_PADCFG			MX6SL_PAD_EPDC_PWRCTRL1__GPIO_2_8	
#define GPIO_SY7636_EN					IMX_GPIO_NR(2,8)
#define GPIO_SY7636_VCOM_PADCFG			MX6SL_PAD_EPDC_VCOM0__GPIO_2_3	
#define GPIO_SY7636_VCOM				IMX_GPIO_NR(2,3)
//#define GPIO_SY7636_EP_3V3_IN								IMX_GPIO_NR(4,3) // EPDC_PWRWAKEUP
#define GPIO_SY7636_EP_3V3_IN_PADCFG				MX6SL_PAD_KEY_ROW5__GPIO_4_3

#define GPIO_SY7636_PWRGOOD							IMX_GPIO_NR(2,13) // EPDC_PWRSTAT
#define GPIO_SY7636_PWRGOOD_GPIO_PADCFG			MX6SL_PAD_EPDC_PWRSTAT__GPIO_2_13_PUINT
//#define GPIO_SY7636_PWRGOOD_GPIO_PADCFG			MX6SL_PAD_EPDC_PWRSTAT__GPIO_2_13
//#define GPIO_SY7636_PWRGOOD_GPIO_PADCFG		MX6SL_PAD_EPDC_PWRSTAT__GPIO_2_13_FLOATINPUT

#else
// beta version .
#define GPIO_SY7636_EN_PADCFG			MX6SL_PAD_EPDC_VCOM0__GPIO_2_3	
#define GPIO_SY7636_EN					IMX_GPIO_NR(2,3)
#define GPIO_SY7636_VCOM_PADCFG			MX6SL_PAD_EPDC_PWRCTRL1__GPIO_2_8	
#define GPIO_SY7636_VCOM				IMX_GPIO_NR(2,8)
#endif

#define VIN_ON		1
#define VIN_OFF		0
#define EN_ON			1
#define EN_OFF		0
#define VCOM_ON		1
#define VCOM_OFF	0


//#define SY7636_EP3V3OFF_TICKS_MAX			350
#define SY7636_POWEROFF_ms_MAX			0 //
#define SY7636_PWROFFDELAYWORK_ms			500

#define SY7636_VCOM_EXTERNAL	1
#define SY7636_LIGHTNESS_MODE	1
#define SY7636_EN_OFF_WITH_RAILS	1



#define SY7636_VCOM_MV_MAX		(-0)
#define SY7636_VCOM_MV_MIN		(-5000)
//#define SY7636_VCOM_MV_STEP		(22)
#define SY7636_VCOM_UV_STEP		(21569)

#define SY7636_WAIT_TICKSTAMP(_TickEnd,_wait_item)	\
{\
	unsigned long dwTickNow=jiffies,dwTicks;\
	int iInInterrupt=in_interrupt();\
	if ( time_before(dwTickNow,_TickEnd) ) {\
		dwTicks = _TickEnd-dwTickNow;\
		DBG_MSG("%s() waiting to %ld ticks for %s ... ",__FUNCTION__,dwTicks,_wait_item);\
		if(iInInterrupt) {\
			mdelay(jiffies_to_msecs(dwTicks));\
			DBG_MSG("done(@INT)\n");\
		}\
		else {\
			msleep(jiffies_to_msecs(dwTicks));\
			DBG_MSG("done\n");\
		}\
	}\
}


typedef struct tagSY7636_PWRDWN_WORK_PARAM {
	struct delayed_work pwrdwn_work;
	int iIsTurnOffChipPwr;
} SY7636_PWRDWN_WORK_PARAM;



typedef struct tagSY7636_data {
	int iCurrent_temprature;
	unsigned short wTempratureData,wReserved;
	struct i2c_adapter *ptI2C_adapter; 
	struct i2c_client *ptI2C_client;
	struct mutex tI2CLock;
	struct mutex tPwrLock;
	int iIsPoweredON;
	int iIsOutputEnabled;
	int iIsOutputPowerDownCounting;
	int iIsVCOMNeedReInit;
	int iCurrent_VCOM_mV;
	int iIsRegsNeedReInit;
	unsigned long dwTickPowerOffEnd;
	unsigned long dwTickPowerOnEnd;
	unsigned long dwTickEP3V3OffEnd;
	SY7636_PWRDWN_WORK_PARAM tPwrdwn_work_param;
	int iIsEP3V3_SW_enabled;
	int iChipPwrWaitON_ms; // the times to wait SY7636 ON after turnning it ON .
	int iVEEStableWait_ms; // the times to wait VEE discharged .
#ifdef USE_EPD_PWRSTAT //[
	wait_queue_head_t tWQ_RailPower;
#else //][!USE_EPD_PWRSTAT
	int iRailPwrWaitON_ms; // the times to wait rail power stable after enabling EN pin .
	unsigned long dwTickRailPowerOnEnd;
#endif //] USE_EPD_PWRSTAT

} SY7636_data;


static SY7636_data *gptSY7636_data ;

// externals ...
extern volatile NTX_HWCONFIG *gptHWCFG;
extern volatile int gSleep_Mode_Suspend;


static struct i2c_board_info gtSY7636_BI = {
 .type = "SY7636",
 .addr = 0x62,
 .platform_data = NULL,
};

static const unsigned short gwSY7636_AddrA[] = {
	0x62,
	I2C_CLIENT_END
};


//
// SY7636 operation mode .
//
// 1:turn on all power rails . 
#define SY7636_REG_OPM_RAILS_ON_mask	0x1 //  
#define SY7636_REG_OPM_RAILS_ON_lsb		7 //  

// 1:controll the vcom by external VCOM_EN pin 
#define SY7636_REG_OPM_VCOM_EXT_mask	0x1 //  
#define SY7636_REG_OPM_VCOM_EXT_lsb		6 //  

// 1:lightness mode power down sequence enable . 
#define SY7636_REG_OPM_LIGHTNESS_mask		0x1 //  
#define SY7636_REG_OPM_LIGHTNESS_lsb		5 //  

// VDDH disable discharge .
#define SY7636_REG_OPM_VDDH_DISABLE_mask		0x1 //  
#define SY7636_REG_OPM_VDDH_DISABLE_lsb		4 //  

// VEE disable discharge . 
#define SY7636_REG_OPM_VEE_DISABLE_mask		0x1 //  
#define SY7636_REG_OPM_VEE_DISABLE_lsb		3 //  

// VPOS disable discharge . 
#define SY7636_REG_OPM_VPOS_DISABLE_mask		0x1 //  
#define SY7636_REG_OPM_VPOS_DISABLE_lsb		2 //  

// VNEG disable discharge .
#define SY7636_REG_OPM_VNEG_DISABLE_mask		0x1 //  
#define SY7636_REG_OPM_VNEG_DISABLE_lsb		1 //  

// VNEG disable discharge .
#define SY7636_REG_OPM_VCOM_DISABLE_mask		0x1 //  
#define SY7636_REG_OPM_VCOM_DISABLE_lsb		0 //  
static volatile unsigned char gbSY7636_REG_OPM_addr=0x00;
static volatile unsigned char gbSY7636_REG_OPM=0;


// 
// 
//
#define SY7636_REG_VCOM_ADJ_ALL_mask	0xff //  
#define SY7636_REG_VCOM_ADJ_ALL_lsb		0 //  
static volatile unsigned char gbSY7636_REG_VCOM_ADJ_addr=0x01;
static volatile unsigned char gbSY7636_REG_VCOM_ADJ=0x7d;

// lightness mode delay times .
#define SY7636_REG_VDDH_EXT_VCOM8_mask						0x01
#define SY7636_REG_VDDH_EXT_VCOM8_lsb							7

#define SY7636_REG_VDDH_EXT_VDDH_EXT_mask					0x0f
#define SY7636_REG_VDDH_EXT_VDDH_EXT_lsb					0
static volatile unsigned char gbSY7636_REG_VDDH_EXT_addr=0x02;
static volatile unsigned char gbSY7636_REG_VDDH_EXT=0x4;

#define SY7636_REG_VLDO_VPDD_ADJ_VLDO_mask						0xf
#define SY7636_REG_VLDO_VPDD_ADJ_VLDO_lsb							4
#define SY7636_REG_VLDO_VPDD_ADJ_VPDD_mask						0xf
#define SY7636_REG_VLDO_VPDD_ADJ_VPDD_lsb							0
static volatile unsigned char gbSY7636_REG_VLDO_VPDD_ADJ_addr=0x03;
static volatile unsigned char gbSY7636_REG_VLDO_VPDD_ADJ=0x66;


// lightness mode delay times .
#define SY7636_REG_VPDD_LEN_VPDD_LEN_mask							0x1f
#define SY7636_REG_VPDD_LEN_VPDD_LEN_lsb							0
static volatile unsigned char gbSY7636_REG_VPDD_LEN_addr=0x04;
static volatile unsigned char gbSY7636_REG_VPDD_LEN=0x7;

// lightness mode delay times .
#define SY7636_REG_VEE_VP_EXT_ALL_mask						0xff
#define SY7636_REG_VEE_VP_EXT_ALL_lsb							0
#define SY7636_REG_VEE_VP_EXT_VEE_mask						0x1f
#define SY7636_REG_VEE_VP_EXT_VEE_lsb							0
#define SY7636_REG_VEE_VP_EXT_VP_mask							0x3
#define SY7636_REG_VEE_VP_EXT_VP_lsb							5
static volatile unsigned char gbSY7636_REG_VEE_VP_EXT_addr=0x05;
static volatile unsigned char gbSY7636_REG_VEE_VP_EXT=0x26;



#define SY7636_REG_PWRON_DLY_DLY1_mask						0x3
#define SY7636_REG_PWRON_DLY_DLY1_lsb							0
#define SY7636_REG_PWRON_DLY_DLY2_mask						0x3
#define SY7636_REG_PWRON_DLY_DLY2_lsb							2
#define SY7636_REG_PWRON_DLY_DLY3_mask						0x3
#define SY7636_REG_PWRON_DLY_DLY3_lsb							4
#define SY7636_REG_PWRON_DLY_DLY4_mask						0x3
#define SY7636_REG_PWRON_DLY_DLY4_lsb							6
static volatile unsigned char gbSY7636_REG_PWRON_DLY_addr=0x06;
static volatile unsigned char gbSY7636_REG_PWRON_DLY=0xaa;


#define SY7636_REG_FAULTS_FAULTS_mask							0xf
#define SY7636_REG_FAULTS_FAULTS_lsb							1
#define SY7636_REG_FAULTS_PG_mask									0x1
#define SY7636_REG_FAULTS_PG_lsb									0
static volatile unsigned char gbSY7636_REG_FAULTS_addr=0x07;
static volatile unsigned char gbSY7636_REG_FAULTS=0;



#define SY7636_REG_TMST_ALL_mask								0xff
#define SY7636_REG_TMST_ALL_lsb									0
static volatile unsigned char gbSY7636_REG_TMST_addr=0x08;
static volatile unsigned char gbSY7636_REG_TMST=0;


static int _sy7636_EN(int iEN_ON);

static int _sy7636_set_reg(unsigned char bRegAddr,unsigned char bRegSetVal)
{
	int iRet=SY7636_RET_SUCCESS;
	int iChk;
	unsigned char bA[2] ;
	int iIn_Interrupt = in_interrupt();
	unsigned long dwTickNow = jiffies,dwTicks;

	ASSERT(gptSY7636_data);


	SY7636_WAIT_TICKSTAMP(gptSY7636_data->dwTickPowerOnEnd,"power on stable");

	if(EN_ON!=gpio_get_value(GPIO_SY7636_EN)) {
#ifndef SY7636_EN_OFF_WITH_RAILS //[
		ERR_MSG("%s(%d):turns on EN automatically .\n",__FUNCTION__,__LINE__);
#endif //]SY7636_EN_OFF_WITH_RAILS
		_sy7636_EN(1);
	}

	if(!iIn_Interrupt) {
		//DBG_MSG("%s(%d):I2C lock .\n",__FUNCTION__,__LINE__);
		mutex_lock(&gptSY7636_data->tI2CLock);
	}
	bA[0]=bRegAddr;
	bA[1]=bRegSetVal;
	iChk = i2c_master_send(gptSY7636_data->ptI2C_client, (const char *)bA, sizeof(bA));
	if (iChk < 0) {
		ERR_MSG("%s(%d):%d=%s(),regAddr=0x%x,regVal=0x%x fail !\n",__FILE__,__LINE__,\
			iChk,"i2c_master_send",bRegAddr,bRegSetVal);
		iRet=SY7636_RET_I2CTRANS_ERR;
	}
	
	if(!iIn_Interrupt) {
		//DBG_MSG("%s(%d):I2C unlock .\n",__FUNCTION__,__LINE__);
		mutex_unlock(&gptSY7636_data->tI2CLock);
	}

	return iRet;
}

static int _sy7636_get_reg(unsigned char bRegAddr,unsigned char *O_pbRegVal)
{
	int iRet=SY7636_RET_SUCCESS;
	int iChk;
	unsigned char bA[1] ;
	int iIn_Interrupt = in_interrupt();
	unsigned long dwTickNow = jiffies,dwTicks;

	ASSERT(gptSY7636_data);


	SY7636_WAIT_TICKSTAMP(gptSY7636_data->dwTickPowerOnEnd,"power on stable");
	if(EN_ON!=gpio_get_value(GPIO_SY7636_EN)) {
#ifndef SY7636_EN_OFF_WITH_RAILS //[
		ERR_MSG("%s(%d):turns on EN automatically .\n",__FUNCTION__,__LINE__);
#endif //]SY7636_EN_OFF_WITH_RAILS
		_sy7636_EN(1);
	}

	if(!iIn_Interrupt) {
		//DBG_MSG("%s(%d):I2C lock .\n",__FUNCTION__,__LINE__);
		mutex_lock(&gptSY7636_data->tI2CLock);
	}

	bA[0]=bRegAddr;
	iChk = i2c_master_send(gptSY7636_data->ptI2C_client, (const char *)bA, 1);
	if (iChk < 0) {
		ERR_MSG("%s(%d):%s i2c_master_send fail !\n",__FILE__,__LINE__,__FUNCTION__);
		iRet = SY7636_RET_I2CTRANS_ERR;
	}
	

	iChk = i2c_master_recv(gptSY7636_data->ptI2C_client, bA, 1);
	if (iChk < 0) {
		ERR_MSG("%s(%d):%s i2c_master_recv fail !\n",__FILE__,__LINE__,__FUNCTION__);
		iRet = SY7636_RET_I2CTRANS_ERR;
	}


	if(iRet>=0) {
		*O_pbRegVal = bA[0];
	}

	
	//DBG_MSG("%s(0x%x,%p)==>0x%x\n",__FUNCTION__,bRegAddr,O_pbRegVal,bA[0]);

	if(!iIn_Interrupt) {
		//DBG_MSG("%s(%d):I2C unlock .\n",__FUNCTION__,__LINE__);
		mutex_unlock(&gptSY7636_data->tI2CLock);
	}

	return iRet;
}


#define SY7636_REG_WRITE_EX(_regName,_bRegVal)		\
({\
	int __iRet=SY7636_RET_SUCCESS;\
	int __iChk;\
	volatile unsigned char _bRegOld = gbSY7636_REG_##_regName;\
	__iChk = _sy7636_set_reg(gbSY7636_REG_##_regName##_##addr,_bRegVal);\
	if(__iChk<0) {\
		__iRet = __iChk;\
	}\
	else {\
		DBG_MSG("%s() : SY7636 write reg%s(%02Xh) 0x%02x->0x%02x\n",__FUNCTION__,\
		#_regName,gbSY7636_REG_##_regName##_##addr,_bRegOld,_bRegVal);\
		gbSY7636_REG_##_regName = _bRegVal;\
	}\
	__iRet;\
})

#define SY7636_REG_WRITE(_regName)		\
	SY7636_REG_WRITE_EX(_regName,gbSY7636_REG_##_regName)


/*
 *  
 * 
 */ 
#define SY7636_REG_FLD_SET(_regName,_bFieldName,_bSetVal)		\
({\
	int _iRet=SY7636_RET_SUCCESS;\
	unsigned char _bNewReg,_bFieldMask;\
	\
	_bFieldMask=(unsigned char)(SY7636_REG_##_regName##_##_bFieldName##_mask<<SY7636_REG_##_regName##_##_bFieldName##_lsb);\
	_bNewReg=gbSY7636_REG_##_regName & ~_bFieldMask;\
	_bNewReg |= (_bSetVal<<SY7636_REG_##_regName##_##_bFieldName##_lsb)&_bFieldMask;\
	gbSY7636_REG_##_regName = _bNewReg;\
	DBG_MSG("%s() : SY7636 set reg%s(%02Xh) val=0x%02x\n",__FUNCTION__,\
		#_regName,gbSY7636_REG_##_regName##_##addr,_bNewReg);\
	_iRet;\
})


#define SY7636_REG_READ_EX(_regName,_into_cache)	\
({\
	int _iChk;\
	unsigned short _wRet;\
	unsigned char bReadReg=0;\
	\
	_iChk = _sy7636_get_reg(gbSY7636_REG_##_regName##_##addr,&bReadReg);\
	if(_iChk<0) {\
		_wRet = (unsigned short)-1;\
	}\
	else {\
		if(_into_cache) {\
			gbSY7636_REG_##_regName = bReadReg;\
		}\
		_wRet = (unsigned short)bReadReg;\
		DBG_MSG("%s() : SY7636 read reg%s(%02Xh)=0x%02x\n",__FUNCTION__,\
			#_regName,gbSY7636_REG_##_regName##_##addr,bReadReg);\
	}\
	_wRet;\
})

#define SY7636_REG_READ(_regName)	\
	SY7636_REG_READ_EX(_regName,0)	


#define SY7636_REG_FLD_GET(_regName,_bFieldName)		\
({\
	int _iChk;\
	unsigned char _bRet=0;\
	unsigned char _bFieldMask;\
	\
	_bFieldMask=(unsigned char)(SY7636_REG_##_regName##_##_bFieldName##_mask<<SY7636_REG_##_regName##_##_bFieldName##_lsb);\
	_bRet = (unsigned short)((gbSY7636_REG_##_regName&_bFieldMask)>>SY7636_REG_##_regName##_##_bFieldName##_lsb);\
	DBG_MSG("%s() : SY7636 get fld %s of reg%s(%02Xh)=0x%02x\n",__FUNCTION__,\
	#_bFieldName,#_regName,gbSY7636_REG_##_regName##_##addr,_bRet);\
	_bRet;\
})

#define SY7636_REG(_regName)	gbSY7636_REG_##_regName

#define SY7636_SET_VCOM_MV(iVCOMmV)	\
	{\
		unsigned short wVCOM_val;\
		wVCOM_val = (unsigned short)((-iVCOMmV)/10);\
		gbSY7636_REG_VCOM_ADJ1 = (unsigned char)(wVCOM_val&0xff);\
		if(wVCOM_val&0x100) {\
			gbSY7636_REG_VDDH_EXT |= 0x80;\
		}\
		else {\
			gbSY7636_REG_VDDH_EXT &= ~0x80;\
		}\
	}



static int _sy7636_gpio_init(void)
{
	int iRet = SY7636_RET_SUCCESS;
	int iVINState;

	GALLEN_DBGLOCAL_BEGIN();

#ifdef USE_EPD_PWRSTAT //[
	mxc_iomux_v3_setup_pad(GPIO_SY7636_PWRGOOD_GPIO_PADCFG);
	gpio_request(GPIO_SY7636_PWRGOOD, "SY7636_PWRGOOD");
	gpio_direction_input(GPIO_SY7636_PWRGOOD);
#endif //] USE_EPD_PWRSTAT

	mxc_iomux_v3_setup_pad(GPIO_SY7636_VIN_PADCFG);
	if(0!=gpio_request(GPIO_SY7636_VIN, "sy7636_VIN")) {
		WARNING_MSG("%s(),request gpio sy7636_VIN fail !!\n",__FUNCTION__);
		//gpio_direction_input(GPIO_SY7636_VIN);
	}

	iVINState = gpio_get_value(GPIO_SY7636_VIN);
	//printk("%s():SY7636 VIN=%d\n",__FUNCTION__,iVINState);
	gptSY7636_data->iIsPoweredON=(VIN_ON==iVINState)?1:0;

	mxc_iomux_v3_setup_pad(GPIO_SY7636_EN_PADCFG);
	if(0!=gpio_request(GPIO_SY7636_EN, "sy7636_EN")) {
		WARNING_MSG("%s(),request gpio sy7636_EN fail !!\n",__FUNCTION__);
		//gpio_direction_input(GPIO_SY7636_EN);
	}
	gpio_direction_output(GPIO_SY7636_EN,EN_ON);
	mdelay(2);
	

	mxc_iomux_v3_setup_pad(GPIO_SY7636_VCOM_PADCFG);
	gpio_request(GPIO_SY7636_VCOM, "sy7636_VCOM");
	if(0!=gpio_request(GPIO_SY7636_VCOM, "sy7636_VCOM")) {
		WARNING_MSG("%s(),request gpio sy7636_VCOM fail !!\n",__FUNCTION__);
		//gpio_direction_input(GPIO_SY7636_VCOM);
	}
	gpio_direction_output(GPIO_SY7636_VCOM,VCOM_OFF);

#if defined(GPIO_SY7636_EP_3V3_IN) && (GPIO_SY7636_EP_3V3_IN!=GPIO_SY7636_VIN) //[
	if(gptSY7636_data->iIsEP3V3_SW_enabled) {
		// E60Q3X revA .
		mxc_iomux_v3_setup_pad(GPIO_SY7636_EP_3V3_IN_PADCFG);
		gpio_request(GPIO_SY7636_EP_3V3_IN, "sy7636_EP_3V3");
		if(0!=gpio_request(GPIO_SY7636_EP_3V3_IN, "sy7636_EP_3V3")) {
			WARNING_MSG("%s(),request gpio sy7636_EP_3V3_IN fail !!\n",__FUNCTION__);
		}
		gpio_direction_output(GPIO_SY7636_EP_3V3_IN,0);
	}
#endif //]GPIO_SY7636_EP_3V3_IN_PADCFG

	GALLEN_DBGLOCAL_END();

	return iRet;
}

static void _sy7636_gpio_release(void)
{
	GALLEN_DBGLOCAL_BEGIN();
	if(!gptSY7636_data) {
		WARNING_MSG("%s(%d) : %s cannot work before init !\n",__FILE__,__LINE__,__FUNCTION__);
		GALLEN_DBGLOCAL_ESC();
		return ;
	}
	gpio_free(GPIO_SY7636_VCOM);
	gpio_free(GPIO_SY7636_EN);
	gpio_free(GPIO_SY7636_VIN);

#if defined(GPIO_SY7636_EP_3V3_IN) && (GPIO_SY7636_EP_3V3_IN!=GPIO_SY7636_VIN) //[
	if(gptSY7636_data->iIsEP3V3_SW_enabled) {
		gpio_free(GPIO_SY7636_EP_3V3_IN);
	}
#endif //]GPIO_SY7636_EP_3V3_IN_PADCFG
	GALLEN_DBGLOCAL_END();
}

static void _sy7636_reinit_vcom(void)
{
	ASSERT(gptSY7636_data);
	if(gptSY7636_data->iIsVCOMNeedReInit) {
		int iRetryCnt;
		int iChk = 0;
		
		for(iRetryCnt=0;iRetryCnt<10;iRetryCnt++)
		{
			iChk |= SY7636_REG_WRITE(VDDH_EXT);
			iChk |= SY7636_REG_WRITE(VCOM_ADJ);
			if(iChk>=0) {
				gptSY7636_data->iIsVCOMNeedReInit = 0;
				break;
			}
			else {
				ERR_MSG("%s():re-write VCOM_ADJ to 0x%02X failed (%d)!!\n",__FUNCTION__,SY7636_REG(VCOM_ADJ),iRetryCnt);
			}
		}
	}
}


static int _sy7636_reg_init(void)
{
	if(!gptSY7636_data->ptI2C_client) {
		WARNING_MSG("%s() registers setup skip ! since i2c not probed \n",__FUNCTION__);
		return -1;
	}

	SY7636_REG_WRITE(OPM);

	_sy7636_reinit_vcom();

#ifdef SY7636_LIGHTNESS_MODE //[
	// re-power on failed patch from silergy 20180620.
	SY7636_REG_WRITE(VDDH_EXT);
	SY7636_REG_WRITE(VPDD_LEN);
	SY7636_REG_WRITE(VEE_VP_EXT);
#endif //] SY7636_LIGHTNESS_MODE

	gptSY7636_data->iIsRegsNeedReInit = 0;
	return 0;
}


static int _sy7636_EN(int iEN_ON)
{
	if(iEN_ON) {
		gpio_direction_output(GPIO_SY7636_EN,EN_ON);
		msleep(3);
		if(gptSY7636_data->iIsRegsNeedReInit) { 
			_sy7636_reg_init();
		}
	}
	else {
		gpio_direction_output(GPIO_SY7636_EN,EN_OFF);
		gptSY7636_data->iIsVCOMNeedReInit = 1;
		gptSY7636_data->iIsRegsNeedReInit = 1;
		msleep(2);
	}
}


static int _sy7636_wait_power_good(int iWaitON,int iTimeout_ms)
{

	unsigned long dwTickWaitStart=jiffies,dwTickTimesout,dwTickWaitStop;
	int iPG,iPG_cur = gpio_get_value(GPIO_SY7636_PWRGOOD);
	unsigned long dwTestCnt=0;
	unsigned char bFaults ;
	int iRet=-1;


	dwTickTimesout = dwTickWaitStart + msecs_to_jiffies(iTimeout_ms);

	do 
	{
		dwTestCnt++;

		SY7636_REG_READ_EX(FAULTS,1);
		bFaults = SY7636_REG_FLD_GET(FAULTS,FAULTS);
		iPG = SY7636_REG_FLD_GET(FAULTS,PG);

		if(iWaitON) {
			if(bFaults) {
				// fault occurs .
				printk("SY7636 Rails ON fault (%xh)\n ",bFaults);
				iRet = -2;
				break;
			}
			if(1==iPG) {
				iRet = 1;
				break;
			}
		}
		else {
			if(0==iPG) {
				iRet = 0;
				break;
			}
		}


		if(jiffies>=dwTickTimesout) {
			printk(KERN_WARNING"%s(@INT) : turn %s the rail power failed (%dms timeout),faults=0x%x\n",__FILE__,iWaitON?"ON":"OFF",iTimeout_ms,bFaults);
			iRet = -3;
			break;
		}

		msleep(2);

	} while(1);

	dwTickWaitStop = jiffies;
	DBG_MSG("%s(@INT):%d ticks(%d times) taken for rail power %s,PG %d->%d\n",\
			__FUNCTION__,dwTickWaitStop-dwTickWaitStart,dwTestCnt,iWaitON?"ON":"OFF",
			iPG_cur,gpio_get_value(GPIO_SY7636_PWRGOOD));

	return iRet;

}

static int _sy7636_output_en(int iIsEnable)
{
	int iRet = SY7636_RET_SUCCESS;
	int iChk;

	DBG_MSG("%s(%d)\n",__FUNCTION__,iIsEnable);

	if(!gptSY7636_data) {
		WARNING_MSG("%s(%d) : %s cannot work before init !\n",__FILE__,__LINE__,__FUNCTION__);
		return SY7636_RET_NOTINITEDSTATE;
	}

	if(gptSY7636_data->iIsOutputEnabled == iIsEnable) {
		// nothing have to do when state not change .
		if(iIsEnable) {
			DBG_MSG("%s() : output power already enabled\n",__FUNCTION__);
			if(1==SY7636_REG_FLD_GET(OPM,VCOM_EXT)) 
			{
				gpio_direction_output(GPIO_SY7636_VCOM,VCOM_ON);
			}
		}
	}
	else {

		if(iIsEnable) {
			int iRailsON_RetryCnt=3;

			do {
#ifdef SY7636_EN_OFF_WITH_RAILS //[
				if(EN_ON!=gpio_get_value(GPIO_SY7636_EN)) {
					_sy7636_EN(1);
				}
#endif //]SY7636_EN_OFF_WITH_RAILS
				SY7636_REG_FLD_SET(OPM,RAILS_ON,1);
				if(SY7636_REG_WRITE(OPM)>=0) {

#ifdef USE_EPD_PWRSTAT //[
#else //][!USE_EPD_PWRSTAT
				gptSY7636_data->dwTickRailPowerOnEnd = jiffies + msecs_to_jiffies(gptSY7636_data->iRailPwrWaitON_ms) ;
#endif //] USE_EPD_PWRSTAT
				
				}
				else {
					WARNING_MSG("%s():set rails on failed !!\n",__FUNCTION__);
				}

				//msleep(10);
				_sy7636_reinit_vcom();
				//msleep(13);
#ifdef USE_EPD_PWRSTAT //[

				iChk = _sy7636_wait_power_good(1,200);
				if(1==iChk) {
					// wait power good ok . 
					gptSY7636_data->iIsOutputEnabled = 1;
				}
				else if(iChk<0) {
					// wait power good times out .
					if(--iRailsON_RetryCnt>0) {
						WARNING_MSG("%s():wait powergood timeout !! retry %d\n",
							__FUNCTION__,iRailsON_RetryCnt);
						_sy7636_EN(0);
						_sy7636_EN(1);
						continue;
					}
				}

#else //][!USE_EPD_PWRSTAT
				SY7636_WAIT_TICKSTAMP(gptSY7636_data->dwTickRailPowerOnEnd,"rail power on stable");
#endif //] USE_EPD_PWRSTAT


				if(1==SY7636_REG_FLD_GET(OPM,VCOM_EXT)) {
					msleep(2);
					gpio_direction_output(GPIO_SY7636_VCOM,VCOM_ON);
					msleep(2);
				}

			} while (0) ;
		}
		else {

			SY7636_REG_FLD_SET(OPM,RAILS_ON,0);
			if(SY7636_REG_WRITE(OPM)>=0) {
				gptSY7636_data->dwTickPowerOffEnd = jiffies + msecs_to_jiffies(SY7636_POWEROFF_ms_MAX);
			}

			iChk = _sy7636_wait_power_good(0,200);
			if(0==iChk) {
				// 
				gptSY7636_data->iIsOutputEnabled = 0;
			}
			else if(iChk<0) {
				// wait power good = 0 timeout or error. 
			}

#ifdef SY7636_EN_OFF_WITH_RAILS //[
			if(EN_ON==gpio_get_value(GPIO_SY7636_EN)) {
				_sy7636_EN(0);
			}
#endif //]SY7636_EN_OFF_WITH_RAILS
		}
	}

	return iRet ;
}




static int _sy7636_vin_onoff_ex(int iIsON,int iIsRegInit)
{
	int iRet = SY7636_RET_SUCCESS;

	ASSERT(gptSY7636_data);

	DBG_MSG("%s(%d,%d)\n",__FUNCTION__,iIsON,iIsRegInit);
	
	if(iIsON==gptSY7636_data->iIsPoweredON) {
	}
	else {
		if(iIsON) {
			gpio_direction_output(GPIO_SY7636_VIN,VIN_ON);
			gptSY7636_data->iIsPoweredON = 1;
			//msleep(10);
			gptSY7636_data->dwTickPowerOnEnd = jiffies + msecs_to_jiffies(gptSY7636_data->iChipPwrWaitON_ms) ;
			if(iIsRegInit) {
				_sy7636_reg_init();
			}
		}
		else {
			_sy7636_output_en(0);
			SY7636_WAIT_TICKSTAMP(gptSY7636_data->dwTickPowerOffEnd,"pwroff stable");
			gpio_direction_output(GPIO_SY7636_VIN,VIN_OFF);
			gptSY7636_data->iIsPoweredON = 0;
			gptSY7636_data->iIsVCOMNeedReInit = 1;
			gptSY7636_data->iIsRegsNeedReInit = 1;
			if(3==gptHWCFG->m_val.bUIConfig) {
				// MP/RD mode .
				gptSY7636_data->dwTickEP3V3OffEnd = jiffies + 0;
			}
			else {
				//gptSY7636_data->dwTickEP3V3OffEnd = jiffies + SY7636_EP3V3OFF_TICKS_MAX;
				gptSY7636_data->dwTickEP3V3OffEnd = jiffies + msecs_to_jiffies(gptSY7636_data->iVEEStableWait_ms);
			}
		}
	}

	return iRet;
}

static int _sy7636_vin_onoff(int iIsON)
{
	return _sy7636_vin_onoff_ex(iIsON,0);
}


static void _sy7636_pwrdwn_work_func(struct work_struct *work)
{
	GALLEN_DBGLOCAL_BEGIN();

	mutex_lock(&gptSY7636_data->tPwrLock);

	if(!gptSY7636_data->iIsOutputPowerDownCounting) {
		WARNING_MSG("[WARNING]%s(%d): race condition occured !\n",__FILE__,__LINE__);
		return ;
	}

	_sy7636_output_en(0);
	gptSY7636_data->iIsOutputPowerDownCounting = 0;

	if(gptSY7636_data->tPwrdwn_work_param.iIsTurnOffChipPwr) {
		_sy7636_vin_onoff(0);
	}

	mutex_unlock(&gptSY7636_data->tPwrLock);

	GALLEN_DBGLOCAL_END();
}


/**********************************************************************
 *
 * public functions .
 *
***********************************************************************/

int sy7636_power_onoff(int iIsPowerOn,int iIsOutputPwr)
{
	int iRet = SY7636_RET_SUCCESS;

	GALLEN_DBGLOCAL_BEGIN();
	if(!gptSY7636_data) {
		WARNING_MSG("%s(%d) : %s cannot work before init !\n",__FILE__,__LINE__,__FUNCTION__);
		GALLEN_DBGLOCAL_ESC();
		return SY7636_RET_NOTINITEDSTATE;
	}

		

	mutex_lock(&gptSY7636_data->tPwrLock);
	if (iIsPowerOn) {
		_sy7636_vin_onoff(1);

		if(iIsOutputPwr==1) {
			gptSY7636_data->iIsOutputPowerDownCounting = 0;
			cancel_delayed_work_sync(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work);
			_sy7636_output_en(1);
		}
	}
	else {
		gptSY7636_data->tPwrdwn_work_param.iIsTurnOffChipPwr = 0;
		if(!gptSY7636_data->iIsOutputPowerDownCounting) 
		{
			gptSY7636_data->iIsOutputPowerDownCounting = 1;
			cancel_delayed_work_sync(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work);
			schedule_delayed_work(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work, \
					msecs_to_jiffies(SY7636_PWROFFDELAYWORK_ms));
		}
	}
	mutex_unlock(&gptSY7636_data->tPwrLock);	

	GALLEN_DBGLOCAL_END();
	return iRet;
}

int sy7636_output_power(int iIsOutputPwr,int iIsChipPowerDown)
{
	int iRet=SY7636_RET_SUCCESS;

	GALLEN_DBGLOCAL_BEGIN();

	if(!gptSY7636_data) {
		WARNING_MSG("%s(%d) : %s cannot work before init !\n",__FILE__,__LINE__,__FUNCTION__);
		GALLEN_DBGLOCAL_ESC();
		return SY7636_RET_NOTINITEDSTATE;
	}


	mutex_lock(&gptSY7636_data->tPwrLock);
	if(iIsOutputPwr) {
		GALLEN_DBGLOCAL_RUNLOG(0);
		gptSY7636_data->iIsOutputPowerDownCounting = 0;
		cancel_delayed_work_sync(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work);

		if(!gptSY7636_data->iIsPoweredON) {
			GALLEN_DBGLOCAL_RUNLOG(1);
			// auto power on chip .
			_sy7636_vin_onoff(1);
		}

		iRet = _sy7636_output_en(1);
	}
	else {
		GALLEN_DBGLOCAL_RUNLOG(2);
		if(!gptSY7636_data->iIsOutputPowerDownCounting) {
			GALLEN_DBGLOCAL_RUNLOG(3);

			if(1==SY7636_REG_FLD_GET(OPM,VCOM_EXT)) { 
				udelay(100);gpio_direction_output(GPIO_SY7636_VCOM,VCOM_OFF);
			}

			gptSY7636_data->tPwrdwn_work_param.iIsTurnOffChipPwr = iIsChipPowerDown;
			gptSY7636_data->iIsOutputPowerDownCounting = 1;
			cancel_delayed_work_sync(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work);
			schedule_delayed_work(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work, \
					msecs_to_jiffies(SY7636_PWROFFDELAYWORK_ms));
		}
		else {
			GALLEN_DBGLOCAL_RUNLOG(4);
			DBG_MSG("%s(%d),power down work already exist \n",__FUNCTION__,__LINE__);
		}
	}
	mutex_unlock(&gptSY7636_data->tPwrLock);

	GALLEN_DBGLOCAL_END();
	return iRet;
}

#define SY7636_SUSPEND_ENABLED	1

int sy7636_suspend(void)
{
#ifdef SY7636_SUSPEND_ENABLED //[
	int iRet = SY7636_RET_SUCCESS;
	//int iChk;

	if(!gptSY7636_data) {
		WARNING_MSG("%s(%d) : %s cannot work before init !\n",
				__FILE__,__LINE__,__FUNCTION__);
		return SY7636_RET_NOTINITEDSTATE;
	}

	if(gptSY7636_data->iIsOutputEnabled) {
		WARNING_MSG("%s() : skip suspend when PMIC output enabled !! (%d)\n",__FUNCTION__,
				delayed_work_pending(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work));
		return SY7636_RET_PWRDWNWORKPENDING;
	}

	if(gSleep_Mode_Suspend) {
		mutex_lock(&gptSY7636_data->tPwrLock);
		_sy7636_vin_onoff(0);
		mutex_unlock(&gptSY7636_data->tPwrLock);

#if 0
		//SY7636_WAIT_TICKSTAMP(gptSY7636_data->dwTickEP3V3OffEnd,"pwroff->EP3V3 off stable");
#else
		if(time_before(jiffies,gptSY7636_data->dwTickEP3V3OffEnd)) {
			WARNING_MSG("%s():waiting for VEE stable ,please retry suspend later !!!\n",__FUNCTION__);
			return SY7636_RET_PWRDWNWORKPENDING;
		}
		else {
			#if defined(GPIO_SY7636_EP_3V3_IN) && (GPIO_SY7636_EP_3V3_IN!=GPIO_SY7636_VIN) //[
			if(gptSY7636_data->iIsEP3V3_SW_enabled) {
				gpio_direction_output(GPIO_SY7636_EP_3V3_IN,0);
			}
			#endif //] defined(GPIO_SY7636_EP_3V3_IN) && (GPIO_SY7636_EP_3V3_IN!=GPIO_SY7636_VIN)
		}
#endif
	}

	return iRet;
#else //][! SY7636_SUSPEND_ENABLED
	printk("%s() skipped !\n",__FUNCTION__);
	return 0;
#endif //] SY7636_SUSPEND_ENABLED
}

#define AVOID_ANIMATION_LOOP

void sy7636_shutdown(void)
{
	if(!gptSY7636_data) {
		WARNING_MSG("%s(%d) : %s cannot work before init !\n",
				__FILE__,__LINE__,__FUNCTION__);
		return ;
	}
	if(delayed_work_pending(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work)) {
#ifdef AVOID_ANIMATION_LOOP //[
		cancel_delayed_work_sync(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work);
#else //][!AVOID_ANIMATION_LOOP
		sy7636_power_onoff(0,0);
#endif //] AVOID_ANIMATION_LOOP
	}
#ifdef AVOID_ANIMATION_LOOP //[
	//DBG0_ENTRY_TAG();
	mutex_lock(&gptSY7636_data->tPwrLock);
	
	msleep(SY7636_PWROFFDELAYWORK_ms);
	//DBG0_ENTRY_TAG();
	_sy7636_output_en(0);
	//DBG0_ENTRY_TAG();
	_sy7636_vin_onoff(0);
	//DBG0_ENTRY_TAG();

#else //][!AVOID_ANIMATION_LOOP 

	while (1) {
		if(gptSY7636_data->iIsOutputEnabled) {
			DBG0_MSG("%s() : waiting for PMIC output disabled !! (%d)\n",__FUNCTION__,
				delayed_work_pending(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work));
			msleep(100);
		}
		else {
			break;
		}
	}// while end .

#endif //] AVOID_ANIMATION_LOOP 

	while (1) {
		if(time_before(jiffies,gptSY7636_data->dwTickEP3V3OffEnd)) {
			DBG0_MSG("%s() : waiting for VEE stable to power off the EP3V3 ...\n",__FUNCTION__);
			msleep(100);
		}
		else {
			#if defined(GPIO_SY7636_EP_3V3_IN) && (GPIO_SY7636_EP_3V3_IN!=GPIO_SY7636_VIN) //[
			if(gptSY7636_data->iIsEP3V3_SW_enabled) {
				gpio_direction_output(GPIO_SY7636_EP_3V3_IN,0);
			}
			#endif //] defined(GPIO_SY7636_EP_3V3_IN) && (GPIO_SY7636_EP_3V3_IN!=GPIO_SY7636_VIN)
			break;
		}
	}// while end .

#ifdef AVOID_ANIMATION_LOOP//[
	mutex_unlock(&gptSY7636_data->tPwrLock);
#endif //]AVOID_ANIMATION_LOOP

}

void sy7636_resume(void)
{
	printk("%s() enter\n",__FUNCTION__);
#ifdef SY7636_SUSPEND_ENABLED//[
	if(!gptSY7636_data) {
		WARNING_MSG("%s(%d) : %s cannot work before init !\n",__FILE__,__LINE__,__FUNCTION__);
		return ;
	}

	if(gSleep_Mode_Suspend) {
		mutex_lock(&gptSY7636_data->tPwrLock);	
		_sy7636_vin_onoff_ex(1,1);
		mutex_unlock(&gptSY7636_data->tPwrLock);

	}
#else
	printk("%s() skipped !\n",__FUNCTION__);
#endif //] SY7636_SUSPEND_ENABLED
	printk("%s() exit\n",__FUNCTION__);
	
}

int sy7636_ONOFF(int iIsON)
{
	int iRet=SY7636_RET_SUCCESS;

	if(! ((19==gptHWCFG->m_val.bDisplayCtrl)||(22==gptHWCFG->m_val.bDisplayCtrl))) {
		WARNING_MSG("%s() display controller (%d) not match !\n",
				__FUNCTION__,(int)gptHWCFG->m_val.bDisplayCtrl);
		return 1;
	}
	


	mutex_lock(&gptSY7636_data->tPwrLock);	
	if(iIsON) {
#if defined(GPIO_SY7636_EP_3V3_IN) && (GPIO_SY7636_EP_3V3_IN!=GPIO_SY7636_VIN) //[
		if(gptSY7636_data->iIsEP3V3_SW_enabled) {
			DBG_MSG("%s() : Trun ON EP_3V3\n",__FUNCTION__);
			gpio_direction_output(GPIO_SY7636_EP_3V3_IN,1);
		}
#endif //] 

		_sy7636_vin_onoff_ex(1,0);
	}
	else {
		_sy7636_vin_onoff_ex(0,0);

#if defined(GPIO_SY7636_EP_3V3_IN) && (GPIO_SY7636_EP_3V3_IN!=GPIO_SY7636_VIN) //[
		/*
		if(gptSY7636_data->iIsEP3V3_SW_enabled) 
		{
			DBG_MSG("%s() : Trun OFF EP_3V3\n",__FUNCTION__);
			SY7636_WAIT_TICKSTAMP(gptSY7636_data->dwTickEP3V3OffEnd,
					"pwroff->EP3V3 off stable");
			gpio_direction_output(GPIO_SY7636_EP_3V3_IN,0);
		}
		*/
#endif //] 
	}
	mutex_unlock(&gptSY7636_data->tPwrLock);

	return iRet;
}


int sy7636_get_temperature(int *O_piTemperature)
{
	unsigned short wReg;
	int iRet=SY7636_RET_SUCCESS;

	int iTemp;
	unsigned char bReg,bTemp;
	int iOldPowerState;

	//return SY7636_RET_SUCCESS;

	if(!gptSY7636_data) {
		WARNING_MSG("%s() cannot work if driver is not initialed \n",__FUNCTION__);
		return SY7636_RET_NOTINITEDSTATE;
	}

	iOldPowerState = gptSY7636_data->iIsPoweredON;
	sy7636_output_power(1,0);
	
	wReg = SY7636_REG_READ(TMST);

	sy7636_ONOFF(iOldPowerState);

	if(((unsigned short)(-1))==wReg) {
		ERR_MSG("%s(%d):%s regTMST read fail !\n",__FILE__,__LINE__,__FUNCTION__);
		return SY7636_RET_I2CTRANS_ERR;
	}

	bReg = (unsigned char)wReg;
	gptSY7636_data->wTempratureData = wReg;
	if(bReg&0x80) {
		// negative .
		bTemp=(~bReg)+1;
		iTemp = bTemp;
		iTemp = (~iTemp)+1;
	}
	else {
		// positive .
		iTemp = (int)(bReg);
	}
	gptSY7636_data->iCurrent_temprature = iTemp;
	printk("%s temprature data = 0x%x,%d\n",DRIVER_NAME,wReg,gptSY7636_data->iCurrent_temprature);

	if(O_piTemperature) {
		*O_piTemperature = gptSY7636_data->iCurrent_temprature;
	}

	return iRet;
}





int sy7636_vcom_set(int iVCOM_mV,int iIsWriteToFlash)
{

	const int iVCOM_mV_max=SY7636_VCOM_MV_MAX,iVCOM_mV_min=SY7636_VCOM_MV_MIN;
	int iRet=SY7636_RET_SUCCESS;

	if(!gptSY7636_data) {
		WARNING_MSG("%s() cannot work if driver is not initialed \n",__FUNCTION__);
		return SY7636_RET_NOTINITEDSTATE;
	}
	
	if(iVCOM_mV<iVCOM_mV_min) {
		ERR_MSG("%s(%d),VCOM %d cannot < %d mV\n",
				__FUNCTION__,__LINE__,iVCOM_mV,iVCOM_mV_min);
	}
	else if(iVCOM_mV>iVCOM_mV_max) {
		ERR_MSG("%s(%d),VCOM %d cannot > %d\n",
				__FUNCTION__,__LINE__,iVCOM_mV,iVCOM_mV_max);
	}
	else {
		unsigned short wVCOM_val;

		int iOldPowerState ;


		if(iVCOM_mV>0) {
			iVCOM_mV = 0;
			wVCOM_val = 0;
		}
		else {
			wVCOM_val = (unsigned short)((-iVCOM_mV)/10);
		}

		iOldPowerState = gptSY7636_data->iIsPoweredON;
		sy7636_ONOFF(1);

		if(wVCOM_val&0x100) {
			SY7636_REG_FLD_SET(VDDH_EXT,VCOM8,1);
		}
		else {
			SY7636_REG_FLD_SET(VDDH_EXT,VCOM8,0);
		}
		iRet |= SY7636_REG_WRITE(VDDH_EXT);
		SY7636_REG_FLD_SET(VCOM_ADJ,ALL,(unsigned char)wVCOM_val);
		iRet |= SY7636_REG_WRITE(VCOM_ADJ);
	
#if 0
		DBG_MSG("%s():set VCOM %dmV,VCOM=0x%02X%02X\n",\
				__FUNCTION__,iVCOM_mV,SY7636_REG_FLD_GET(VDDH_EXT,VCOM8),
				SY7636_REG_FLD_GET(VCOM_ADJ,ALL));
#endif
		if(iRet>=0) {
			gptSY7636_data->iCurrent_VCOM_mV=iVCOM_mV;
		}
		sy7636_ONOFF(iOldPowerState);

	}

	return iRet;
}


int sy7636_vcom_get(int *O_piVCOM_mV)
{
	int iVCOM_mV;
	int iOldPowerState;
	int iRet = SY7636_RET_SUCCESS;
	unsigned char bRegVCOM1,bRegVCOM2;
	unsigned short wTemp;

	if(!gptSY7636_data) {
		WARNING_MSG("%s() cannot work if driver is not initialed \n",__FUNCTION__);
		return SY7636_RET_NOTINITEDSTATE;
	}

	iOldPowerState = gptSY7636_data->iIsPoweredON;
	sy7636_ONOFF(1);

	_sy7636_reinit_vcom();

	bRegVCOM2 = (unsigned char)SY7636_REG_READ_EX(VDDH_EXT,1);
	bRegVCOM1 = (unsigned char)SY7636_REG_READ_EX(VCOM_ADJ,1);
	wTemp = bRegVCOM1;
	if(bRegVCOM2&0x80) {
		wTemp |= 0x100;
	}
	else {
		wTemp &= ~0x100;
	}
	iVCOM_mV = -(wTemp*10);


	DBG_MSG("%s(%d):iVCOM_mV=%d\n",__FUNCTION__,__LINE__,iVCOM_mV);

	if(O_piVCOM_mV) {
		*O_piVCOM_mV = iVCOM_mV;
		gptSY7636_data->iCurrent_VCOM_mV=iVCOM_mV;
	}

	sy7636_ONOFF(iOldPowerState);

	return iRet;
}

int sy7636_vcom_get_cached(int *O_piVCOM_mV)
{
	if(!gptSY7636_data) {
		WARNING_MSG("%s() cannot work if driver is not initialed \n",__FUNCTION__);
		return SY7636_RET_NOTINITEDSTATE;
	}

	if(O_piVCOM_mV) {
		*O_piVCOM_mV = gptSY7636_data->iCurrent_VCOM_mV;
	}

	return SY7636_RET_SUCCESS;
}


void sy7636_release(void)
{
	if(!gptSY7636_data) {
		WARNING_MSG("%s() cannot work if driver is not initialed \n",__FUNCTION__);
		return ;
	}


	mutex_lock(&gptSY7636_data->tPwrLock);	
	_sy7636_vin_onoff(0);
	mutex_unlock(&gptSY7636_data->tPwrLock);	

	gptSY7636_data->ptI2C_adapter = 0;
	i2c_unregister_device(gptSY7636_data->ptI2C_client);
	gptSY7636_data->ptI2C_client = 0;
	
	_sy7636_gpio_release();

	kfree(gptSY7636_data);gptSY7636_data = 0;

}

int sy7636_init(int iPort)
{

	int iRet = SY7636_RET_SUCCESS;
	int iChk;

	unsigned long dwSize;
	const int iProbeRetryMax=30;
	int iProbeRetryCnt;

	GALLEN_DBGLOCAL_BEGIN();

	if(gptSY7636_data) {
		WARNING_MSG("skipped %s() calling over twice !!\n",__FUNCTION__);
		return 0;
	}

	dwSize=sizeof(SY7636_data);

	gptSY7636_data = kmalloc(dwSize,GFP_KERNEL);
	if(!gptSY7636_data) {
		iRet = SY7636_RET_MEMNOTENOUGH;
		ERR_MSG("%s(%d) : memory not enough !!\n",__FILE__,__LINE__);
		GALLEN_DBGLOCAL_RUNLOG(0);
		goto MEM_MALLOC_FAIL;
	}

	memset(gptSY7636_data,0,sizeof(SY7636_data));
	
	if(36==gptHWCFG->m_val.bPCB || 40==gptHWCFG->m_val.bPCB) {
		// E60Q3X/E60Q5X
		if((0==gptHWCFG->m_val.bPCB_LVL&&gptHWCFG->m_val.bPCB_REV>=0x10) || 40==gptHWCFG->m_val.bPCB) {
			// >= E60Q30A10 ,E60Q5X
			printk("%s(): EP3V3 switch enabled",__FUNCTION__);
			gptSY7636_data->iIsEP3V3_SW_enabled = 1;
		}
		else {
			gptSY7636_data->iIsEP3V3_SW_enabled = 0;
		}
#ifdef USE_EPD_PWRSTAT //[
#else //][!USE_EPD_PWRSTAT
		gptSY7636_data->iRailPwrWaitON_ms = 10;
#endif //] USE_EPD_PWRSTAT
		
		gptSY7636_data->iChipPwrWaitON_ms = 10;
		gptSY7636_data->iVEEStableWait_ms = 3500;
	}
	else {
#ifdef USE_EPD_PWRSTAT //[
#else //][!USE_EPD_PWRSTAT
		gptSY7636_data->iRailPwrWaitON_ms = 60;
#endif //] USE_EPD_PWRSTAT
		
		gptSY7636_data->iIsEP3V3_SW_enabled = 0;
		gptSY7636_data->iChipPwrWaitON_ms = 10;
		if( 1 == gptHWCFG->m_val.bDisplayResolution) {
			// 1024x758 .
			gptSY7636_data->iVEEStableWait_ms = 6500;
		}
		else {
			gptSY7636_data->iVEEStableWait_ms = 3500;
		}
	}

	gptSY7636_data->dwTickPowerOffEnd = jiffies;
	gptSY7636_data->dwTickPowerOnEnd = jiffies;

#ifdef USE_EPD_PWRSTAT //[
	init_waitqueue_head(&gptSY7636_data->tWQ_RailPower);
#else //][!USE_EPD_PWRSTAT
	gptSY7636_data->dwTickRailPowerOnEnd = jiffies;
#endif //] USE_EPD_PWRSTAT
	
	gptSY7636_data->dwTickEP3V3OffEnd = jiffies;

	iChk = _sy7636_gpio_init();
	if(iChk<0) {
		iRet = SY7636_RET_GPIOINITFAIL;
		ERR_MSG("%s(%d) : gpio init fail !!\n",__FILE__,__LINE__);
		GALLEN_DBGLOCAL_RUNLOG(1);
		goto GPIO_INIT_FAIL;
	}


	_sy7636_vin_onoff_ex(1,0);


	gptSY7636_data->ptI2C_adapter = i2c_get_adapter(iPort-1);//
	if( NULL == gptSY7636_data->ptI2C_adapter) {
		ERR_MSG ("[Error] %s : SY7636_RET_I2CCHN_NOTFOUND,chn=%d\n",__FUNCTION__,iPort);
		GALLEN_DBGLOCAL_RUNLOG(2);
		iRet=SY7636_RET_I2CCHN_NOTFOUND;
		goto I2CCHN_GET_FAIL;
	}


	for (iProbeRetryCnt=1;iProbeRetryCnt<=iProbeRetryMax;iProbeRetryCnt++)
	{

		gptSY7636_data->ptI2C_client = i2c_new_probed_device(gptSY7636_data->ptI2C_adapter, &gtSY7636_BI,gwSY7636_AddrA,0);

		if(gptSY7636_data->ptI2C_client) {
			DBG_MSG("SY7636 addr=0x%x ready !\n",gwSY7636_AddrA[0]);
			break;
		}
		else {
			ERR_MSG("[Error] %s : SY7636 probe failed ! retry #%d/%d \n",
					__FUNCTION__,iProbeRetryCnt,iProbeRetryMax);
			msleep(10);
			continue;
		}
	}

	if( NULL == gptSY7636_data->ptI2C_client ) {
		GALLEN_DBGLOCAL_RUNLOG(3);
		ERR_MSG("[Error] %s : SY7636 probe fail \n",__FUNCTION__);
		goto I2CPROBE_DEVICE_FAIL;
	}



	// kernel objects initialize ...
	mutex_init(&gptSY7636_data->tPwrLock);
	mutex_init(&gptSY7636_data->tI2CLock);

	INIT_DELAYED_WORK(&gptSY7636_data->tPwrdwn_work_param.pwrdwn_work,_sy7636_pwrdwn_work_func);

#ifdef SY7636_VCOM_EXTERNAL //[
	if(SY7636_REG_FLD_SET(OPM,VCOM_EXT,1)<0) {
		ERR_MSG("%s():set vcom external failed !\n",__FUNCTION__);
	}
#endif //]SY7636_VCOM_EXTERNAL


#ifdef SY7636_LIGHTNESS_MODE //[
	// re-power on failed patch from silergy 20180620.
	SY7636_REG_FLD_SET(OPM,LIGHTNESS,1);
	SY7636_REG_FLD_SET(VDDH_EXT,VDDH_EXT,0);
	SY7636_REG_FLD_SET(VPDD_LEN,VPDD_LEN,0);
	SY7636_REG_FLD_SET(VEE_VP_EXT,VEE,0);
	SY7636_REG_FLD_SET(VEE_VP_EXT,VP,0x1);
#endif //] SY7636_LIGHTNESS_MODE


	_sy7636_reg_init();
	sy7636_ONOFF(INIT_POWER_STATE);

	sy7636_vcom_get(&gptSY7636_data->iCurrent_VCOM_mV);

	GALLEN_DBGLOCAL_ESC();
	return SY7636_RET_SUCCESS;


	i2c_unregister_device(gptSY7636_data->ptI2C_client);
	gptSY7636_data->ptI2C_client = 0;
I2CPROBE_DEVICE_FAIL:
	gptSY7636_data->ptI2C_adapter = 0;
I2CCHN_GET_FAIL:
	_sy7636_gpio_release();
GPIO_INIT_FAIL:
	kfree(gptSY7636_data);gptSY7636_data = 0;
MEM_MALLOC_FAIL:
	
	GALLEN_DBGLOCAL_END();
	return iRet;
}


