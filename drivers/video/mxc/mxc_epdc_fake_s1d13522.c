
// this file should be included by epdc driver from manufacturer .

#include "fake_s1d13522.h"
#include "lk_tps65185.h"
#include "lk_sy7636.h"
#include "lk_fp9928.h"
#include <linux/completion.h>


#if defined(CONFIG_MACH_MX6SL_NTX)||(CONFIG_MACH_MX6DL_NTX) //[
	#define FAKE_S1D13522_PLATFORM_MX6	1
#endif //]CONFIG_SOC_IMX6SL
//#define LM75_ENABLED		1


#ifdef LM75_ENABLED//[
#include "lk_lm75.h"
#endif //]LM75_ENABLED


#define SYSFS_DBG		1
//#define DITHER_ENABLE		1
#define FW_IN_RAM	1


#define WF_INIT	0
#define WF_DU	1
#define WF_GC16	2
#define WF_GC4	3
//
static EPDFB_DC *gptDC;

// global mxc update data ....
static struct mxcfb_update_data g_mxc_upd_data;
#ifdef FAKE_S1D13522_PLATFORM_MX6//[
static struct mxcfb_update_marker_data g_mxc_upd_marker_data;
#endif //]FAKE_S1D13522_PLATFORM_MX6

extern int check_hardware_name(void);



#include "ntx_hwconfig.h"
extern volatile NTX_HWCONFIG *gptHWCFG;

static int giLastTemprature = DEFAULT_TEMP;
static volatile unsigned long gdwLastUpdateJiffies = 0;
static int giIsInited = 0;
DECLARE_COMPLETION(mxc_epdc_fake13522_inited);
#define EPD_PMIC_EXCEPTION_STATE_NONE							0
#define EPD_PMIC_EXCEPTION_STATE_ABORTING					-1
#define EPD_PMIC_EXCEPTION_STATE_REUPDATE_INIT		1
#define EPD_PMIC_EXCEPTION_STATE_REUPDATING				2		
static volatile int giEPD_PMIC_exception_state = EPD_PMIC_EXCEPTION_STATE_NONE;
static struct mxcfb_rect gtEPD_PMIC_exception_rect;
#define INVALID_TEMP	500
static int giCustomTemp=INVALID_TEMP;


static char gcFB_snapshot_pathA[512+2];
volatile static int giFB_snapshot_enable;
#ifdef OUTPUT_SNAPSHOT_IMGFILE//[
static int giFB_snapshot_total=OUTPUT_SNAPSHOT_IMGFILE;
#else //]OUTPUT_SNAPSHOT_IMGFILE
static int giFB_snapshot_total=3;
#endif//]OUTPUT_SNAPSHOT_IMGFILE
static int giFB_snapshot_repeat;
#ifdef DITHER_ENABLE//[
static int giDither_enable;
#endif //]DITHER_ENABLE



static void epdc_powerup(struct mxc_epdc_fb_data *fb_data);
static void epdc_powerdown(struct mxc_epdc_fb_data *fb_data);

static void _pmic_on(void);

//
// private help functions prototype ...
//


static ssize_t waveform_mode_ver_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t waveform_mode_ver_write(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count);

static ssize_t waveform_rev_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t waveform_rev_write(struct device *dev, struct device_attribute *attr,
    const char *buf, size_t count);


static ssize_t temperature_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t temperature_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count);

static ssize_t waveform_mode_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t waveform_mode_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count);

#ifdef SYSFS_DBG//[
static ssize_t dbg_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t dbg_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count);
#endif //]SYSFS_DBG
static ssize_t fbsnapshot_path_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t fbsnapshot_path_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count);
static ssize_t fbsnapshot_enable_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t fbsnapshot_enable_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count);

static ssize_t vcom_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t vcom_write(struct device *dev, struct device_attribute *attr,const char *buf, size_t count);

static ssize_t xwi_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t xwi_write(struct device *dev, struct device_attribute *attr,const char *buf, size_t count);
#ifdef DITHER_ENABLE//[
static ssize_t dither_enable_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t dither_enable_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
#endif //]DITHER_ENABLE
static ssize_t tce_state_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t tce_state_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);

static ssize_t power_state_read(struct device *dev, struct device_attribute *attr,char *buf);
static ssize_t power_state_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
static DEVICE_ATTR(waveform_mode_ver, 0666, waveform_mode_ver_read, waveform_mode_ver_write);
static DEVICE_ATTR(waveform_rev, 0666, waveform_rev_read, waveform_rev_write);
static DEVICE_ATTR(temperature, 0666, temperature_read, temperature_write);
static DEVICE_ATTR(waveform_mode_gc16, 0666, waveform_mode_read, waveform_mode_write);
static DEVICE_ATTR(waveform_mode_du, 0666, waveform_mode_read, waveform_mode_write);
static DEVICE_ATTR(waveform_mode_gl16, 0666, waveform_mode_read, waveform_mode_write);
static DEVICE_ATTR(waveform_mode_reagl, 0666, waveform_mode_read, waveform_mode_write);
static DEVICE_ATTR(waveform_mode_reagld, 0666, waveform_mode_read, waveform_mode_write);
static DEVICE_ATTR(waveform_mode_a2, 0666, waveform_mode_read, waveform_mode_write);
static DEVICE_ATTR(fbsnapshot_path, 0666, fbsnapshot_path_read, fbsnapshot_path_write);
static DEVICE_ATTR(fbsnapshot_enable, 0666, fbsnapshot_enable_read, fbsnapshot_enable_write);
static DEVICE_ATTR(vcom, 0666, vcom_read, vcom_write);
static DEVICE_ATTR(xwi, 0666, xwi_read, xwi_write);
#ifdef SYSFS_DBG//[
static DEVICE_ATTR(dbg, 0666, dbg_read, dbg_write);
#endif //]SYSFS_DBG
#ifdef DITHER_ENABLE//[
static DEVICE_ATTR(dither_enable, 0666, dither_enable_read, dither_enable_write);
#endif //]DITHER_ENABLE
static DEVICE_ATTR(tce_state, 0666, tce_state_read, tce_state_write);
static DEVICE_ATTR(power_state, 0666, power_state_read, power_state_write);


static ssize_t xwi_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	if(g_fb_data&&g_fb_data->waveform_xwi_string) 
	{
		sprintf(buf,"%s\n",g_fb_data->waveform_xwi_string);
		return strlen(buf);
	}
	else {
		return 0;
	}
}
static ssize_t xwi_write(struct device *dev, struct device_attribute *attr,
	const char *buf, size_t count)
{
	return 0;
}
static ssize_t vcom_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	int iVCOM_mV;
	int iChk;

	if(8==gptHWCFG->m_val.bDisplayCtrl) {
		iChk = fp9928_vcom_get_cached(&iVCOM_mV);
		if(iChk>=0) {
			sprintf (buf,"%dmV\n",iVCOM_mV);
		}
	}
	else if(19==gptHWCFG->m_val.bDisplayCtrl || 22==gptHWCFG->m_val.bDisplayCtrl) {
		iChk = sy7636_vcom_get_cached(&iVCOM_mV);
		if(iChk>=0) {
			sprintf (buf,"%dmV\n",iVCOM_mV);
		}
	}
	else if(6==gptHWCFG->m_val.bDisplayCtrl||7==gptHWCFG->m_val.bDisplayCtrl||17==gptHWCFG->m_val.bDisplayCtrl) {
		iChk = tps65185_vcom_get_cached(&iVCOM_mV);
		if(iChk>=0) {
			sprintf (buf,"%dmV\n",iVCOM_mV);
		}
	}
	else {
	}
	return strlen(buf);
}

static ssize_t vcom_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	int iVCOM_mV;
	int iChk;

	sscanf(buf,"%dmV",&iVCOM_mV);
	//printk("%s():user input %dmV\n",__FUNCTION__,iVCOM_mV);

	if(iVCOM_mV<0) {
		if(8==gptHWCFG->m_val.bDisplayCtrl) {
			iChk = fp9928_vcom_set(iVCOM_mV,0);
			if(iChk<0) {
				printk(KERN_ERR"FP9928 VCOM %dmV write failed !\n",iVCOM_mV);
			}
		}
		else if(19==gptHWCFG->m_val.bDisplayCtrl || 22==gptHWCFG->m_val.bDisplayCtrl) {
			iChk = sy7636_vcom_set(iVCOM_mV,0);
			if(iChk<0) {
				printk(KERN_ERR"SY7636 VCOM %dmV write failed !\n",iVCOM_mV);
			}
		}
		else if(6==gptHWCFG->m_val.bDisplayCtrl||7==gptHWCFG->m_val.bDisplayCtrl||17==gptHWCFG->m_val.bDisplayCtrl) {
			iChk = tps65185_vcom_set(iVCOM_mV,0);
			if(iChk<0) {
				printk(KERN_ERR"TPS65185 VCOM %dmV write failed !\n",iVCOM_mV);
			}
		}
		else {
		}
	}
	return strlen(buf);
}

#ifdef SYSFS_DBG//[
static char gcDbgStringA[128];
static ssize_t dbg_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	//printk(KERN_ALERT"%s():%s\n",__FUNCTION__,gcDbgStringA);
	sprintf (buf,"%d\n",g_fb_data->verbose_lvl);
	return strlen(buf);
}

static void epdc_recovery(struct mxc_epdc_fb_data *fb_data);
static ssize_t dbg_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	//strcpy(gcFB_snapshot_pathA,buf);
	int iCnt=0;
	char *pc=buf;

	if(!pc) {
		dev_err(dev,"%s() : parameter error !!",__FUNCTION__);
		return 0;
	}

	while(*pc!='\0' && *pc!='\x0a' && *pc!='\x0d') 
	{
		if (*pc < '0' || *pc > '9') {
			// special command .
			//dev_info(dev,"invalid char=%c\n",*pc);
			dev_info(dev,"debug command mode : \"%s\"\n",buf);
			if(0==strcmp(buf,"epdc-reinit")) {
				epdc_recovery(g_fb_data);
			}
			return strlen(buf);
		}
		pc++;

		if(++iCnt>256) {
			dev_err(dev,"parameter length cannot > 256\n");
			return 256;
		}
	}

	sscanf(buf,"%d\n",&g_fb_data->verbose_lvl);
	return strlen(buf);
}
#endif //]SYSFS_DBG
static ssize_t fbsnapshot_path_read(struct device *dev, struct device_attribute *attr,char *buf)
{

	sprintf (buf,"%s\n",gcFB_snapshot_pathA);
	return strlen(buf);
}

static ssize_t fbsnapshot_path_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	sscanf(buf,"%s\n",gcFB_snapshot_pathA);
	//strcpy(gcFB_snapshot_pathA,buf);
	return strlen(buf);
}
static ssize_t fbsnapshot_enable_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	sprintf (buf,"%d %d %d\n",giFB_snapshot_enable,giFB_snapshot_total,giFB_snapshot_repeat);
	return strlen(buf);
}
static ssize_t fbsnapshot_enable_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	int iEnable=-1,iCapTotal=-1,iRepeat=-1;
	sscanf(buf,"%d %d %d\n",&iEnable,&iCapTotal,&iRepeat);
	switch(iEnable) {
	case 0:
	case 1:
	case 2:
		giFB_snapshot_enable=iEnable;
		if(-1!=iRepeat) {
			giFB_snapshot_repeat=iRepeat;
		}
		if(iCapTotal>0) {
			giFB_snapshot_total=iCapTotal;
		}
		break;
	default:
		break;
	}
	return strlen(buf);
}

#ifdef DITHER_ENABLE//[
static ssize_t dither_enable_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	sprintf (buf,"%d\n",giDither_enable);
	return strlen(buf);
}

static ssize_t dither_enable_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	int iEnable;
	sscanf(buf,"%d\n",&iEnable);
	switch(iEnable) {
	case 0:
	case 1:
	case 2:
	case 3:
		giDither_enable=iEnable;
		break;
	default:
		break;
	}
	return strlen(buf);
}

static int dither_enable_state(void)
{
	return giDither_enable;
}
#else //][!DITHER_ENABLE
static int dither_enable_state(void)
{
	return 0;
}
#endif //]DITHER_ENABLE



static ssize_t tce_state_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	switch (giTCE_State) {
	case TCE_STATE_NORMAL:
		sprintf (buf,"%s\n","normal");
		break;
	case TCE_STATE_CRITICAL:
		sprintf (buf,"%s\n","critical");
		break;
	default:
		sprintf (buf,"%s\n","unkown");
		break;
	}
	return strlen(buf);
}

static ssize_t tce_state_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	return strlen(buf);
}

static ssize_t power_state_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	if(POWER_STATE_ON == g_fb_data->power_state && !g_fb_data->powering_down) {
		sprintf(buf,"%s\n","on");
	}
	else {
		if(g_fb_data->powering_down) {
			sprintf(buf,"%s\n","powering down");
		}
		else {
			sprintf(buf,"%s\n","off");
		}
	}
	return strlen(buf);
}

static ssize_t power_state_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	int iDelay_ms = 0;
	int iOn;
	ssize_t len=strlen(buf) ;

	
	sscanf(buf,"%d,%d\n",&iOn,&iDelay_ms);
	//printk("state=>%d,delay_ms=>%d\n",iOn,iDelay_ms);
	if(1==iOn) {
		if ((g_fb_data->power_state == POWER_STATE_OFF)
			|| g_fb_data->powering_down) {
			cancel_delayed_work_sync(&g_fb_data->epdc_done_work);

			//g_fb_data->pwrdown_delay = FB_POWERDOWN_DISABLE;
			epdc_powerup(g_fb_data);
			//_pmic_on();
		}
	}
	else if(0==iOn) {
		if(iDelay_ms<=0) {
			g_fb_data->powering_down = true;
			epdc_powerdown(g_fb_data);
		}
		else {
			g_fb_data->powering_down = true;
			g_fb_data->pwrdown_delay = iDelay_ms;

			cancel_delayed_work_sync(&g_fb_data->epdc_done_work);
			schedule_delayed_work(&g_fb_data->epdc_done_work,
				msecs_to_jiffies(iDelay_ms));
		}
	}

	return len;
}



static ssize_t waveform_mode_ver_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	sprintf (buf,"0x%x\n",gbModeVersion);
	return strlen(buf);
}

static ssize_t waveform_mode_ver_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	DBG_MSG("%s()\n",__FUNCTION__);
	return count;
}

static ssize_t waveform_rev_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	sprintf (buf,"0x%x\n",gbWFM_REV);
	return strlen(buf);
}

static ssize_t waveform_rev_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	DBG_MSG("%s()\n",__FUNCTION__);
	return count;
}

static ssize_t temperature_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	sprintf (buf,"%d\n",giLastTemprature);
	return strlen(buf);
}

static ssize_t temperature_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	int iChk,iLastTemprature;

	iLastTemprature = simple_strtol(buf,NULL,0);
	if(iLastTemprature>=INVALID_TEMP) {
		giCustomTemp=INVALID_TEMP;
		gdwLastUpdateJiffies = jiffies;
	}
	else {
		iChk = mxc_epdc_fb_set_temperature(iLastTemprature,&g_fb_data->info);
		if(0==iChk) {
			DBG_MSG("%s(),temp <== %d\n",__FUNCTION__,iLastTemprature);
			giLastTemprature = iLastTemprature;
			gdwLastUpdateJiffies = jiffies+(60*HZ);
			giCustomTemp=iLastTemprature;
		}
		else {
			ERR_MSG("%s(),temp <== %d fail!\n",__FUNCTION__,iLastTemprature);
		}
	}

	return count;
}

static ssize_t waveform_mode_read(struct device *dev, struct device_attribute *attr,char *buf)
{
	int iWaveform_mode=-1,iWaveform_mode_eink=-1;

	if(attr==&dev_attr_waveform_mode_du.attr) {
		iWaveform_mode_eink = giNTX_waveform_modeA[NTX_WFM_MODE_DU];
		iWaveform_mode = NTX_WFM_MODE_DU;
	}
	else 
	if(attr==&dev_attr_waveform_mode_a2.attr) {
		iWaveform_mode_eink = giNTX_waveform_modeA[NTX_WFM_MODE_A2];
		iWaveform_mode = NTX_WFM_MODE_A2;
	}
	else 
	if(attr==&dev_attr_waveform_mode_gc16.attr) {
		iWaveform_mode_eink = giNTX_waveform_modeA[NTX_WFM_MODE_GC16];
		iWaveform_mode = NTX_WFM_MODE_GC16;
	}
	else 
	if(attr==&dev_attr_waveform_mode_gl16.attr) {
		iWaveform_mode_eink = giNTX_waveform_modeA[NTX_WFM_MODE_GL16];
		iWaveform_mode = NTX_WFM_MODE_GL16;
	}
	else 
	if(attr==&dev_attr_waveform_mode_reagl.attr) {
		iWaveform_mode_eink = giNTX_waveform_modeA[NTX_WFM_MODE_GLR16];
		iWaveform_mode = NTX_WFM_MODE_GLR16;
	}
	else 
	if(attr==&dev_attr_waveform_mode_reagld.attr) {
		iWaveform_mode_eink = giNTX_waveform_modeA[NTX_WFM_MODE_GLD16];
		iWaveform_mode = NTX_WFM_MODE_GLD16;
	}

	sprintf (buf,"%d:%d\n",iWaveform_mode,iWaveform_mode_eink);
	return strlen(buf);
}

static ssize_t waveform_mode_write(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	int iWaveform_mode=-1,iWaveform_mode_eink=-1;

	sscanf (buf,"%d:%d\n",&iWaveform_mode,&iWaveform_mode_eink);

	switch (iWaveform_mode) {
	case NTX_WFM_MODE_DU:
	case NTX_WFM_MODE_A2:
	case NTX_WFM_MODE_GC16:
	case NTX_WFM_MODE_GL16:
	case NTX_WFM_MODE_GLR16:
	case NTX_WFM_MODE_GLD16:
		giNTX_waveform_modeA[iWaveform_mode] = iWaveform_mode_eink;
		break;
	default:
		ERR_MSG("%s():parameter error !\n",__FUNCTION__);
		break;
	}

	return count;
}

static const struct attribute *sysfs_epdc_attrs[] = {
	&dev_attr_waveform_mode_ver.attr,
	&dev_attr_waveform_rev.attr,
	&dev_attr_temperature.attr,
	&dev_attr_waveform_mode_du.attr,
	&dev_attr_waveform_mode_a2.attr,
	&dev_attr_waveform_mode_gc16.attr,
	&dev_attr_waveform_mode_gl16.attr,
	&dev_attr_waveform_mode_reagl.attr,
	&dev_attr_waveform_mode_reagld.attr,
#ifdef OUTPUT_SNAPSHOT_IMGFILE//[
	&dev_attr_fbsnapshot_path.attr,
	&dev_attr_fbsnapshot_enable.attr,
#endif //]OUTPUT_SNAPSHOT_IMGFILE	
	&dev_attr_vcom.attr,
	&dev_attr_xwi.attr,
#ifdef SYSFS_DBG//[
	&dev_attr_dbg.attr,
#endif //]SYSFS_DBG
#ifdef DITHER_ENABLE//[
	&dev_attr_dither_enable.attr,
#endif //]DITHER_ENABLE
	&dev_attr_tce_state.attr,
	&dev_attr_power_state.attr,
	NULL,
};


//////////////////////////////////////////////////////
//
// driver extention helper functions ...
//
int mxc_epdc_fb_check_update_complete(u32 update_marker, struct fb_info *info)
{
	struct mxc_epdc_fb_data *fb_data = info ?
		(struct mxc_epdc_fb_data *)info:g_fb_data;
	struct update_marker_data *next_marker;
	struct update_marker_data *temp;
	unsigned long flags;
	bool marker_found = false;
	int ret = 0;
	
	//GALLEN_DBGLOCAL_BEGIN();

	/* 0 is an invalid update_marker value */
	if (update_marker == 0) {
		//GALLEN_DBGLOCAL_ESC();
		return -EINVAL;
	}

	/*
	 * Find completion associated with update_marker requested.
	 * Note: If update completed already, marker will have been
	 * cleared, it won't be found, and function will just return.
	 */

	/* Grab queue lock to protect access to marker list */
#ifdef FAKE_S1D13522_PLATFORM_MX6 //[
	mutex_lock(&fb_data->queue_mutex);
#else //][!FAKE_S1D13522_PLATFORM_MX6
	spin_lock_irqsave(&fb_data->queue_lock, flags);
#endif //] FAKE_S1D13522_PLATFORM_MX6

	list_for_each_entry_safe(next_marker, temp,
		&fb_data->full_marker_list, full_list) {
		//GALLEN_DBGLOCAL_RUNLOG(0);
		if (next_marker->update_marker == update_marker) {
			//GALLEN_DBGLOCAL_RUNLOG(1);
			dev_dbg(fb_data->dev, "Waiting for marker %d\n",
				update_marker);
			next_marker->waiting = true;
			marker_found = true;
			break;
		}
	}

#ifdef FAKE_S1D13522_PLATFORM_MX6 //[
	mutex_unlock(&fb_data->queue_mutex);
#else //][!FAKE_S1D13522_PLATFORM_MX6
	spin_unlock_irqrestore(&fb_data->queue_lock, flags);
#endif //] FAKE_S1D13522_PLATFORM_MX6

	/*
	 * If marker not found, it has either been signalled already
	 * or the update request failed.  In either case, just return.
	 */
	if (!marker_found) {
		//GALLEN_DBGLOCAL_ESC();
		return ret;
	}

	ret = completion_done(&next_marker->update_completion)?1:0;


	//GALLEN_DBGLOCAL_END();
	return ret;
}
//EXPORT_SYMBOL(mxc_epdc_fb_check_update_complete);



//////////////////////////////////////////////////////
//
// fake_s1d13522 HAL interface .
//


static void k_fake_s1d13522_progress_start(void)
{
	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return ;
	}
	
	//fake_s1d13522_progress_start(gptDC);
}


static int k_fake_s1d13522_wait_inited(void)
{
	int iRet=0;

	if(giIsInited<=1) 
	{
		if(in_interrupt()) {
			printk("[%s]:skip before init (interrupt).",__FUNCTION__);
		}
		else {
			printk("[%s]:wait init .",__FUNCTION__);
			wait_for_completion(&mxc_epdc_fake13522_inited);
			printk("[%s]:wait init ok.",__FUNCTION__);
		}
	}
	return iRet;
}

static int32_t k_fake_s1d13522_ioctl(unsigned int cmd,unsigned long arg)
{
	//k_fake_s1d13522_wait_inited();
	return fake_s1d13522_ioctl(cmd,arg,gptDC);
}


static void k_vcom_enable(int iIsEnable)
{
	if(iIsEnable) {
		//vcom enable .
	}
	else {
		//vcom disable .
	}
}

static int k_get_wfbpp(void)
{
	int i_wf_bpp=4;
	
	if(*(gpbWF_vaddr+0x10) == 0x2) {
		i_wf_bpp=3;
	}
	
	return i_wf_bpp;
}

static int k_set_partial(int iIsSetPartial)
{
	u32 temp;
	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return -1;
	}
	
	if(iIsSetPartial) {
		g_mxc_upd_data.update_mode = UPDATE_MODE_PARTIAL;
	}
	else {
		g_mxc_upd_data.update_mode = UPDATE_MODE_FULL;
	}
	return 0;
}

static unsigned char *k_get_realfbEx(unsigned long *O_pdwFBSize)
{
	unsigned char *pbRet ;
	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return 0;
	}
	
	//pbRet = (unsigned char *)g_fb_data->working_buffer_virt;
	pbRet = (unsigned char *)g_fb_data->info.screen_base;
	if(O_pdwFBSize) {
		*O_pdwFBSize = g_fb_data->info.screen_size;
	}
	
	return pbRet;
}

static void k_display_start(int iIsStart)
{
	int iChk;
	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return ;
	}
	
	
	if(iIsStart) {
		#if 0
		printk("%s(%d):==============================>\n",__FUNCTION__,__LINE__) ;
		printk("\t%d bits/pixel\n",g_fb_data->info.var.bits_per_pixel) ;
		printk("\t grayscale=%d \n",g_fb_data->info.var.grayscale) ;
		printk("\t yoffset=%d \n",g_fb_data->info.var.yoffset) ;
		printk("\t rotate=%d \n",g_fb_data->info.var.rotate) ;
		printk("\t activate=%d \n",g_fb_data->info.var.activate) ;
		printk("<======================================\n") ;
		#endif

		g_mxc_upd_data.update_marker=g_mxc_upd_marker_data.update_marker;
		DBG_MSG("%s() (x,y)=(%u,%u),(w,h)(%u,%u),marker=%d\n",__FUNCTION__,
			g_mxc_upd_data.update_region.top,g_mxc_upd_data.update_region.left,
			g_mxc_upd_data.update_region.width,g_mxc_upd_data.update_region.height,
			g_mxc_upd_data.update_marker);

		
		iChk = mxc_epdc_fb_send_update(&g_mxc_upd_data,&g_fb_data->info);
		if(iChk<0) {
			printk(KERN_WARNING"%s(%d):mxc_epdc_fb_send_update fail !\n",
				__FUNCTION__,__LINE__);
		}

	}
	else {
	}
}


static int k_get_wfmode(void)
{
	int i_wf_mode;
	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return 0;
	}
	
	i_wf_mode = g_mxc_upd_data.waveform_mode;
	return i_wf_mode;
}

static void k_set_wfmode(int iWaveform)
{
	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return ;
	}
	
	g_mxc_upd_data.waveform_mode = iWaveform;
}


static int k_is_updating(void)
{
	int iRet;
	int iChk = 0;

	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return 0;
	}

	//if(epdc_is_working_buffer_busy()) 
	iChk = mxc_epdc_fb_check_update_complete(g_mxc_upd_data.update_marker,&g_fb_data->info);
	
	if(1==iChk)
	{
		// updating ...
		iRet = 1;
	}
	else {
		// update done 
		iRet = 0;
	}
	return iRet;
}

static int k_wait_update_complete(void) 
{
	int iRet;
	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return 0;
	}
	

	//if(1==g_mxc_upd_data.waveform_mode||4==g_mxc_upd_data.waveform_mode) {
		// skip wait update complete at DOC mode and A2 mode .
		//iRet = 0;
	//}
	//else if(k_is_updating())
	{
		unsigned long dwJiffiesStart,dwJiffiesEnd;
		dwJiffiesStart = jiffies ;
#ifdef FAKE_S1D13522_PLATFORM_MX6//[
		iRet = mxc_epdc_fb_wait_update_complete(&g_mxc_upd_marker_data,&g_fb_data->info);
		g_mxc_upd_marker_data.update_marker++;
#else //][! FAKE_S1D13522_PLATFORM_MX6
		iRet = mxc_epdc_fb_wait_update_complete(g_mxc_upd_data.update_marker++,&g_fb_data->info);
#endif //] FAKE_S1D13522_PLATFORM_MX6
		dwJiffiesEnd = jiffies;
		printk("[%s]waitupdate ret=%d,%u->%u\n",__FUNCTION__,iRet,\
			(unsigned int)dwJiffiesStart,(unsigned int)dwJiffiesEnd);
	}
	return iRet;
}



/////////////////////////////////////////////////////////////
// calling by real epdc driver .
static int k_set_temperature(struct fb_info *info)
{
	int iRet;
	int iChk;
	

	//printk("%s(),timeout_tick=%u,current_tick=%u\n",__FUNCTION__,
	//		gdwLastUpdateJiffies,jiffies);
	
	
	if(0==gdwLastUpdateJiffies||time_after(jiffies,gdwLastUpdateJiffies)) {
		
		if(giCustomTemp!=INVALID_TEMP) {
			printk(KERN_ERR"%s():use custom temperature %d\n",__FUNCTION__,giCustomTemp);
			return giLastTemprature;
		}

		gdwLastUpdateJiffies = jiffies+(60*HZ);

		ASSERT(gptHWCFG);
		
		if(8==gptHWCFG->m_val.bDisplayCtrl) {
			iChk = fp9928_get_temperature(&giLastTemprature);
		}
		else if(19==gptHWCFG->m_val.bDisplayCtrl || 22==gptHWCFG->m_val.bDisplayCtrl) {
			iChk = sy7636_get_temperature(&giLastTemprature);
		}
		else
		if(6==gptHWCFG->m_val.bDisplayCtrl||7==gptHWCFG->m_val.bDisplayCtrl||17==gptHWCFG->m_val.bDisplayCtrl) 
		{
			// imx508 + tps16585 .
			iChk = tps65185_get_temperature(&giLastTemprature);
		}

#ifdef LM75_ENABLED//[
		else {
			iChk = lm75_get_temperature(0,&giLastTemprature);
		}
#else
		else {
			iChk = -100;
		}
#endif //]LM75_ENABLED
		
		if(iChk>=0) {
			//printk("%s():mxc_epdc_fb_set_temperature...\n",__FUNCTION__);// DBG
			//iChk = mxc_epdc_fb_set_temperature(giLastTemprature,info);
			g_fb_data->temp_index = mxc_epdc_fb_get_temp_index(g_fb_data, giLastTemprature);
		}
		else {
			gdwLastUpdateJiffies = jiffies;
		}
	}
	return giLastTemprature;
}

////////////////////////////////////////////////////////////

static int k_set_update_rect(unsigned short wX,unsigned short wY,
	unsigned short wW,unsigned short wH)
{
	int iRet = 0;
	if(0==giIsInited) {
		printk("[%s]:skip before init .",__FUNCTION__);
		return 0;
	}
	
	
	DBG_MSG("%s() x=%u,y=%u,w=%u,h=%u\n",__FUNCTION__,wX,wY,wW,wH);
	g_mxc_upd_data.update_region.top = wY;
	g_mxc_upd_data.update_region.left = wX;
	g_mxc_upd_data.update_region.height = wH;
	g_mxc_upd_data.update_region.width = wW;	

	
	return iRet;
}

static int k_set_vcom(int iVCOM_set_mV)
{
	int iRet=0;
	ASSERT(gptHWCFG);
	//printk("%s(%d):%s\n",__FILE__,__LINE__,__FUNCTION__);
	if(8==gptHWCFG->m_val.bDisplayCtrl) {
		iRet = fp9928_vcom_set(iVCOM_set_mV,0);
		if(iRet>=0) {
			int iVCOM_get_mV;
			if(fp9928_vcom_get(&iVCOM_get_mV)>=0) {
				vcom_nominal=iVCOM_get_mV*1000;/* save the vcom_nominal value in uV */
			}
		}
	}
	else if(19==gptHWCFG->m_val.bDisplayCtrl || 22==gptHWCFG->m_val.bDisplayCtrl) {
		iRet = sy7636_vcom_set(iVCOM_set_mV,0);
		if(iRet>=0) {
			int iVCOM_get_mV;
			if(sy7636_vcom_get(&iVCOM_get_mV)>=0) {
				vcom_nominal=iVCOM_get_mV*1000;/* save the vcom_nominal value in uV */
			}
		}
	}
	else
	if(6==gptHWCFG->m_val.bDisplayCtrl||7==gptHWCFG->m_val.bDisplayCtrl||17==gptHWCFG->m_val.bDisplayCtrl) {
		iRet = tps65185_vcom_set(iVCOM_set_mV,0);
		if(iRet>=0) {
			int iVCOM_get_mV;
			if(tps65185_vcom_get(&iVCOM_get_mV)>=0) {
				vcom_nominal=iVCOM_get_mV*1000;/* save the vcom_nominal value in uV */
			}
		}
	}
	else {
	}

	return iRet;
}
static int k_set_vcom_to_flash(int iVCOM_set_mV)
{
	int iRet=0;
	//printk("%s(%d):%s\n",__FILE__,__LINE__,__FUNCTION__);
	if(8==gptHWCFG->m_val.bDisplayCtrl) {
		iRet = fp9928_vcom_set(iVCOM_set_mV,1);
		if(iRet>=0) {
			int iVCOM_get_mV;
			if(fp9928_vcom_get(&iVCOM_get_mV)>=0) {
				vcom_nominal=iVCOM_get_mV*1000;/* save the vcom_nominal value in uV */
			}
		}
	}
	else if(19==gptHWCFG->m_val.bDisplayCtrl || 22==gptHWCFG->m_val.bDisplayCtrl) {
		iRet = sy7636_vcom_set(iVCOM_set_mV,1);
		if(iRet>=0) {
			int iVCOM_get_mV;
			if(sy7636_vcom_get(&iVCOM_get_mV)>=0) {
				vcom_nominal=iVCOM_get_mV*1000;/* save the vcom_nominal value in uV */
			}
		}
	}
	else
	if(gptHWCFG&&(6==gptHWCFG->m_val.bDisplayCtrl||7==gptHWCFG->m_val.bDisplayCtrl||17==gptHWCFG->m_val.bDisplayCtrl)) {
		iRet = tps65185_vcom_set(iVCOM_set_mV,1);
		if(iRet>=0) {
			int iVCOM_get_mV;
			if(tps65185_vcom_get(&iVCOM_get_mV)>=0) {
				vcom_nominal=iVCOM_get_mV*1000;/* save the vcom_nominal value in uV */
			}
		}
	}
	else {
	}
	return iRet;
}

static int k_get_vcom(int *O_piVCOM_get_mV)
{
	int iRet=0;
	//printk("%s(%d):%s\n",__FILE__,__LINE__,__FUNCTION__);
	if(8==gptHWCFG->m_val.bDisplayCtrl) {
#if 0
		if(vcom_nominal) {
			if(O_piVCOM_get_mV) {
				*O_piVCOM_get_mV = vcom_nominal/1000;
			}
		}
		else 
#endif
		{		
			iRet = fp9928_vcom_get(O_piVCOM_get_mV);
		}
	}
	else if(19==gptHWCFG->m_val.bDisplayCtrl || 22==gptHWCFG->m_val.bDisplayCtrl) {
#if 0
		if(vcom_nominal) {
			if(O_piVCOM_get_mV) {
				*O_piVCOM_get_mV = vcom_nominal/1000;
			}
		}
		else 
#endif
		{		
			iRet = sy7636_vcom_get(O_piVCOM_get_mV);
		}
	}
	else
	if(gptHWCFG&&(6==gptHWCFG->m_val.bDisplayCtrl||7==gptHWCFG->m_val.bDisplayCtrl||17==gptHWCFG->m_val.bDisplayCtrl)) {
#if 0
		if(vcom_nominal) {
			if(O_piVCOM_get_mV) {
				*O_piVCOM_get_mV = vcom_nominal/1000;
			}
		}
		else 
#endif
		{
			iRet = tps65185_vcom_get(O_piVCOM_get_mV);
		}
	}
	else {
	}

	return iRet;
}

static void k_create_sys_attr(void)
{
	int err;
	DBG_MSG("%s()\n",__FUNCTION__);
	ASSERT(g_fb_data);
	ASSERT(g_fb_data->dev);
	//ASSERT(g_fb_data->dev->kobj);
	err = sysfs_create_files(&g_fb_data->info.dev->kobj, sysfs_epdc_attrs);
	if (err) {
		pr_err("Can't create epdc attr sysfs !\n");
	}
}


#define PMIC_EXCEPTION_MARKER			99999
#define PMIC_EXCEPTION_SPLITX			3
#define PMIC_EXCEPTION_SPLITY			2
#if 1
static int ntx_epdc_pmic_wait_exception_rect_reupdate(struct fb_info *info)
{
	if(EPD_PMIC_EXCEPTION_STATE_REUPDATING==giEPD_PMIC_exception_state) {
		printk("waiting for pmic exception processing ...[begin]\n");
		while(EPD_PMIC_EXCEPTION_STATE_REUPDATING==giEPD_PMIC_exception_state) {
			msleep(100);
		}
		printk("waiting for pmic exception processing ...[end]\n");
	}
	return 0;
}
#else
static int ntx_epdc_pmic_wait_exception_rect_reupdate(struct fb_info *info)
{
	int iRet = 0;

	int i,j;
	const int iSplitXUpdCnt=PMIC_EXCEPTION_SPLITX,iSplitYUpdCnt=PMIC_EXCEPTION_SPLITY;
	struct mxcfb_update_marker_data l_mxc_upd_marker_data[iSplitXUpdCnt][iSplitYUpdCnt];

	for(i=0;i<iSplitXUpdCnt;i++)
	{

		for(j=0;j<iSplitYUpdCnt;j++)
		{
			l_mxc_upd_marker_data[i][j].collision_test = 0;
			l_mxc_upd_marker_data[i][j].update_marker = PMIC_EXCEPTION_MARKER+i+j;
			iRet = mxc_epdc_fb_wait_update_complete(&l_mxc_upd_marker_data[i][j],info);
		}
	}

	return iRet;
}

#endif
static void ntx_epdc_pmic_exception_state_set(int iState)
{
	giEPD_PMIC_exception_state = iState;
}

static void ntx_epdc_pmic_exception_state_clear(void)
{
	ntx_epdc_pmic_exception_state_set(EPD_PMIC_EXCEPTION_STATE_NONE);
}
static void ntx_epdc_pmic_exception_abort(void)
{
	ntx_epdc_pmic_exception_state_set(EPD_PMIC_EXCEPTION_STATE_ABORTING);
}

static int ntx_epdc_pmic_exception_rect_reupdate(struct mxc_epdc_fb_data *fb_data,struct fb_info *info)
{
	int iChk = 0;
	int i,j;
	const int iSplitXUpdCnt=PMIC_EXCEPTION_SPLITX,iSplitYUpdCnt=PMIC_EXCEPTION_SPLITY;
	struct mxcfb_update_data l_upd_data[iSplitXUpdCnt][iSplitYUpdCnt];
	struct mxcfb_update_marker_data l_mxc_upd_marker_data[iSplitXUpdCnt][iSplitYUpdCnt];
	__u32 dw_update_marker ;
	__u32 dwX,dwY,dwW,dwH;
	__u32 old_upd_scheme;

	//dw_update_marker = fb_data->cur_update->update_desc->upd_data.update_marker;
	dw_update_marker = PMIC_EXCEPTION_MARKER;
	ntx_epdc_pmic_exception_state_set(EPD_PMIC_EXCEPTION_STATE_REUPDATING);

	if(FB_ROTATE_UD==fb_data->epdc_fb_var.rotate || FB_ROTATE_UR==fb_data->epdc_fb_var.rotate) {
		dwX = gtEPD_PMIC_exception_rect.top;
		dwY = gtEPD_PMIC_exception_rect.left;
		dwW = gtEPD_PMIC_exception_rect.width;
		dwH = gtEPD_PMIC_exception_rect.height;
	}
	else {
		dwX = gtEPD_PMIC_exception_rect.top;
		dwY = gtEPD_PMIC_exception_rect.left;
		dwH = gtEPD_PMIC_exception_rect.width;
		dwW = gtEPD_PMIC_exception_rect.height;
	}


	printk(KERN_WARNING"volt dropped !!! update rect@ (%d,%d),w=%d,h=%d\n",
			(int)dwX ,(int)dwY ,(int)dwW ,(int)dwH );

	msleep(650);// wait epdc stable .

	old_upd_scheme = fb_data->upd_scheme;

	for(i=0;i<iSplitXUpdCnt;i++)
	{

		for(j=0;j<iSplitYUpdCnt;j++)
		{
			l_upd_data[i][j].update_mode = UPDATE_MODE_FULL;
			l_upd_data[i][j].waveform_mode = fb_data->wv_modes.mode_gc16;
			l_upd_data[i][j].temp = TEMP_USE_AMBIENT;
			l_upd_data[i][j].flags = 0;
			l_upd_data[i][j].update_marker = dw_update_marker+i+j;

			l_upd_data[i][j].update_region.width = dwW/iSplitXUpdCnt;
			l_upd_data[i][j].update_region.height = dwH/iSplitYUpdCnt;
			l_upd_data[i][j].update_region.left = i*(dwW/iSplitXUpdCnt);
			l_upd_data[i][j].update_region.top = j*(dwH/iSplitYUpdCnt);

			if(EPD_PMIC_EXCEPTION_STATE_REUPDATING!=giEPD_PMIC_exception_state) {
				printk("%s : [%d][%d] abort ,exception state=%d\n",
						__FUNCTION__,i,j,giEPD_PMIC_exception_state);
				break;
			}

			printk("split upd[%d][%d] rect@ (%d,%d),w=%d,h=%d\n",i,j,
					(int)l_upd_data[i][j].update_region.left ,
					(int)l_upd_data[i][j].update_region.top ,
					(int)l_upd_data[i][j].update_region.width ,
					(int)l_upd_data[i][j].update_region.height );

			mxc_epdc_fb_set_upd_scheme(UPDATE_SCHEME_SNAPSHOT,info);
			iChk = mxc_epdc_fb_send_update(&l_upd_data[i][j], info);
			mxc_epdc_fb_set_upd_scheme(old_upd_scheme,info);


			l_mxc_upd_marker_data[i][j].collision_test = 0;
			l_mxc_upd_marker_data[i][j].update_marker = dw_update_marker+i+j;
			iChk = mxc_epdc_fb_wait_update_complete(&l_mxc_upd_marker_data[i][j],info);
		}

		if(EPD_PMIC_EXCEPTION_STATE_REUPDATING!=giEPD_PMIC_exception_state) {
			break;
		}
	}
	ntx_epdc_pmic_exception_state_set(EPD_PMIC_EXCEPTION_STATE_NONE);

	return iChk;
}



static inline void ntx_epdc_set_update_coord(u32 x,u32 y)
{

#if 0
	printk("%s() ,exception state=%d,x=%d,y=%d\n",
			__FUNCTION__,giEPD_PMIC_exception_state,(int)x,(int)y);
#endif

	if(EPD_PMIC_EXCEPTION_STATE_NONE!=giEPD_PMIC_exception_state) {
		return ;
	}
		//gtEPD_PMIC_exception_rect.top = 0;
		//gtEPD_PMIC_exception_rect.left = 0;
		gtEPD_PMIC_exception_rect.left = x;
		gtEPD_PMIC_exception_rect.top = y;
}
static inline void ntx_epdc_set_update_dimensions(u32 width, u32 height)
{
#if 0
	printk("%s() ,exception state=%d,w=%d,h=%d\n",
			__FUNCTION__,giEPD_PMIC_exception_state,(int)width,(int)height);
#endif

	if(EPD_PMIC_EXCEPTION_STATE_NONE!=giEPD_PMIC_exception_state) {
		return ;
	}
		//gtEPD_PMIC_exception_rect.width = g_fb_data->native_width;
		//gtEPD_PMIC_exception_rect.height = g_fb_data->native_height;
		gtEPD_PMIC_exception_rect.width = width;
		gtEPD_PMIC_exception_rect.height = height;
}
static void ntx_epdc_pmic_exception(int iEvt)
{
	if(7==gptHWCFG->m_val.bDisplayCtrl||17==gptHWCFG->m_val.bDisplayCtrl) {
		// MX6SL + TPS65185 .
		printk(KERN_ERR"%s(%d),native_w=%d,native_h=%d\n",__FUNCTION__,iEvt,
				(int)g_fb_data->native_width,(int)g_fb_data->native_height);
		//if(tps65185_int_state_get()>=0) 
		{
			tps65185_int_state_clear();
		}

		//g_fb_data->powering_down = true;
		epdc_powerdown(g_fb_data);

#ifdef VDROP_PROC_IN_KERNEL //[
		ntx_epdc_pmic_exception_state_set(EPD_PMIC_EXCEPTION_STATE_REUPDATE_INIT);
		if(ntx_epdc_pmic_exception_rect_reupdate(g_fb_data,&g_fb_data->info)<0) {
			printk(KERN_WARNING"EPD PMIC exceptions occured : reupdated fail !\n");
		}
		else {
			printk(KERN_WARNING"EPD PMIC exceptions occured : reupdated ok .\n");
		}
#else //][!VDROP_PROC_IN_KERNEL
		ntx_epdc_pmic_exception_state_set(EPD_PMIC_EXCEPTION_STATE_REUPDATE_INIT);
		printk(KERN_WARNING"EPD PMIC exceptions occured !!!\n");
#endif

	}
}
static int ntx_epdc_pmic_get_exception_state(void)
{
	return giEPD_PMIC_exception_state;
}

static int k_mx5_send_epd_update(struct mxcfb_mx5_update_data *ptUPD_DATA)
{
	int ret = 0;

	if(EPD_PMIC_EXCEPTION_STATE_REUPDATING==ntx_epdc_pmic_get_exception_state()) {
		printk(KERN_ERR"%s(%d):sending update when pmic exception processing ! scr.w=%d,scr.h=%d,upd.w=%d,upd.h=%d\n",
			__FUNCTION__,__LINE__,g_fb_data->native_width,g_fb_data->native_height,
			ptUPD_DATA->update_region.width,ptUPD_DATA->update_region.height);
		if(g_fb_data->native_width==ptUPD_DATA->update_region.width && 
			 g_fb_data->native_height==ptUPD_DATA->update_region.height )
		{
			ntx_epdc_pmic_exception_abort();
		}
		else {
			ntx_epdc_pmic_wait_exception_rect_reupdate(&g_fb_data->info);
		}

	}
	ptUPD_DATA->flags |= 0x100; // EPDC_FLAG_USE_ALT_BUFFER
	ptUPD_DATA->alt_buffer_data.phys_addr = g_fb_data->info.fix.smem_start+g_fb_data->info.fix.smem_len;

#if 0
	printk("%s():smem@0x%p,sz=%ld,alt buf phy addr@%p\n",
			__FUNCTION__,
			g_fb_data->info.fix.smem_start,
			g_fb_data->map_size,
			ptUPD_DATA->alt_buffer_data.phys_addr);
#endif

	ptUPD_DATA->alt_buffer_data.width = g_fb_data->info.var.xres_virtual;
	ptUPD_DATA->alt_buffer_data.height = g_fb_data->info.var.yres;
	ptUPD_DATA->alt_buffer_data.alt_update_region.top = ptUPD_DATA->update_region.top;
	ptUPD_DATA->alt_buffer_data.alt_update_region.left = ptUPD_DATA->update_region.left;
	ptUPD_DATA->alt_buffer_data.alt_update_region.width = ptUPD_DATA->update_region.width;
	ptUPD_DATA->alt_buffer_data.alt_update_region.height = ptUPD_DATA->update_region.height;
	ret = mxc_epdc_fb_send_update(ptUPD_DATA, &g_fb_data->info);
	if(-EMEDIUMTYPE==ret) {
		printk(KERN_ERR"%s(%d):detected contents unable to update on screen !\n",
				__FUNCTION__,__LINE__);
		return -EMEDIUMTYPE;
	}

	return ret;
}


static int k_fake_s1d13522_init(unsigned char *pbInitDCbuf)
{

	int iChk;
	int vcom_mV;


	//printk("\n%s() DisplayCtrl=%d\n\n",__FUNCTION__,(int)gptHWCFG->m_val.bDisplayCtrl);

	gptDC = fake_s1d13522_initEx3(default_bpp,g_fb_data->info.screen_base,\
			g_fb_data->info.var.xres,g_fb_data->info.var.yres, \
			g_fb_data->info.var.xres_virtual,g_fb_data->info.var.yres_virtual);
				
	if(gptDC) {
		gptDC->pfnGetWaveformBpp = k_get_wfbpp;
		gptDC->pfnVcomEnable = k_vcom_enable;
		gptDC->pfnSetPartialUpdate = k_set_partial;
		//gptDC->pfnGetRealFrameBuf = k_get_realfb;
		gptDC->pfnGetRealFrameBufEx = k_get_realfbEx;
		gptDC->pfnDispStart = k_display_start;
		gptDC->pfnGetWaveformMode = k_get_wfmode;
		gptDC->pfnSetWaveformMode = k_set_wfmode;
		gptDC->pfnIsUpdating = k_is_updating;
		gptDC->pfnWaitUpdateComplete = k_wait_update_complete;
		gptDC->pfnSetUpdateRect = k_set_update_rect;
		gptDC->pfnSetVCOM = k_set_vcom;
		gptDC->pfnGetVCOM = k_get_vcom;
		gptDC->pfnSetVCOMToFlash = k_set_vcom_to_flash;
		gptDC->pfnSendEPDUpd = k_mx5_send_epd_update;
		
		//gptDC->dwFlags |= EPDFB_DC_FLAG_OFB_RGB565;
		gptDC->dwFlags |= EPDFB_DC_FLAG_FLASHDIRTY;
		
		// 
		g_mxc_upd_data.update_region.top = 0;
		g_mxc_upd_data.update_region.left = 0;
		g_mxc_upd_data.update_region.height = g_fb_data->info.var.yres;
		g_mxc_upd_data.update_region.width = g_fb_data->info.var.xres;
		
		//g_mxc_upd_data.waveform_mode = g_fb_data->wv_modes.mode_gc16;
		g_mxc_upd_data.waveform_mode = WF_GC16;
		
		g_mxc_upd_data.update_mode = UPDATE_MODE_FULL;
		g_mxc_upd_data.update_marker = 0;
		g_mxc_upd_data.temp = TEMP_USE_AMBIENT;
		g_mxc_upd_data.flags = 0;
		//g_mxc_upd_data.alt_buffer_data = ;
		//mxc_epdc_fb_set_upd_scheme(UPDATE_SCHEME_SNAPSHOT,&g_fb_data->info);

		// printk("%s(%d):%s,Display=%s\n",__FILE__,__LINE__,__FUNCTION__,
		//	NtxHwCfg_GetCfgFldStrVal(gptHWCFG,HWCFG_FLDIDX_DisplayCtrl));
		
		if(7==gptHWCFG->m_val.bDisplayCtrl||17==gptHWCFG->m_val.bDisplayCtrl) {
			// MX6SL+TPS65185 || MX6DL+TPS65185 .
			tps65185_int_callback_setup(ntx_epdc_pmic_exception);
		}

#ifdef LM75_ENABLED//[
		if(gptHWCFG&&\
				(6==gptHWCFG->m_val.bDisplayCtrl||\
				 7==gptHWCFG->m_val.bDisplayCtrl||\
				 8==gptHWCFG->m_val.bDisplayCtrl)) 
		{
#endif //]LM75_ENABLED
			int iPortA[2]={-1,-1} ;
			int i;
			// imx508 + tps16585 .


#ifdef FAKE_S1D13522_PLATFORM_MX6 //[
#ifdef CONFIG_MACH_MX6DL_NTX //[
			iPortA[0] = 3;
#else //][!CONFIG_MACH_MX6DL_NTX
			iPortA[0] = 2;
#endif //] CONFIG_MACH_MX6DL_NTX
#else//][!FAKE_S1D13522_PLATFORM_MX6

			if(28==gptHWCFG->m_val.bPCB) {
				// E606C2B3 PMIC in Channel 3. before E606C2B3 in Channel 2.

				#if 0 //[
				// <E606C2B3
				iPortA[0] = 2;
				iPortA[1] = -1;
				#else //][
				// >=E606C2B3 .
				iPortA[0] = 1;
				iPortA[1] = 2;
				#endif//]

			}
			else 
			{
				iPortA[0] = 2;
			}
#endif //]FAKE_S1D13522_PLATFORM_MX6
			
			for(i=0;i<2;i++) {
				if(iPortA[i]>0) {
					//printk("%s(),init TPS65185 @ i2c%d\n",__FUNCTION__,iPortA[i]);
					if(8==gptHWCFG->m_val.bDisplayCtrl) {
						iChk = fp9928_init(iPortA[i]);
						if(iChk>=0){
							if(0!=glVCOM_uV) {
								if(fp9928_vcom_set((int)(glVCOM_uV/1000),0)<0) {
									WARNING_MSG("%s(),FP9928 vcom set fail !\n",__FUNCTION__);
								}
							}
							fp9928_vcom_get(&vcom_mV);
						}
					}
					else if(19==gptHWCFG->m_val.bDisplayCtrl || 22==gptHWCFG->m_val.bDisplayCtrl) {
						iChk = sy7636_init(iPortA[i]);
						if(iChk>=0){
							if(0!=glVCOM_uV) {
								if(sy7636_vcom_set((int)(glVCOM_uV/1000),0)<0) {
									WARNING_MSG("%s(),SY7636 vcom set fail !\n",__FUNCTION__);
								}
							}
							sy7636_vcom_get(&vcom_mV);
						}
					}
					else {
						iChk = tps65185_init(iPortA[i],EPDTIMING_V110);
						if(iChk>=0) {
							if(0!=glVCOM_uV) {
								if(tps65185_vcom_set((int)(glVCOM_uV/1000),0)<0) {
									WARNING_MSG("%s(),tps65185 vcom set fail !\n",__FUNCTION__);
								}
							}
							tps65185_vcom_get(&vcom_mV);
						}
					}
					if(iChk>=0) {
						break;
					}
					else {
						WARNING_MSG("%s(),init @ i2c%d fail !\n",__FUNCTION__,iPortA[i]);
					}
				}
			}
#ifdef LM75_ENABLED//[
		}
		else {
			if ((4 == check_hardware_name()) || (3 == check_hardware_name())) {
				lm75_init (3);
			}
			else {
				lm75_init (2);
			}
		}
#endif //]LM75_ENABLED//

		vcom_nominal=vcom_mV*1000;/* save the vcom_nominal value in uV */

		DBG_MSG("%s():PMIC VCOM=%d mV,vcom_nominal=%d\n",
			__FUNCTION__,vcom_mV,vcom_nominal);

		//if(!fake_s1d13522_is_logo_bypss()) 
		{
			g_fb_data->wfm = 0; /* initial waveform mode should be INIT */
			//printk("draw mode0\n");
			epdc_powerup(g_fb_data);
			draw_mode0(g_fb_data);
			//printk("draw mode0 end\n");

			g_fb_data->powering_down = true;
			schedule_delayed_work(&g_fb_data->epdc_done_work,
				msecs_to_jiffies(g_fb_data->pwrdown_delay));
		}
		//epdc_powerdown(g_fb_data);

		giIsInited=1;
		
		//while(k_is_updating()) {
			//DBG0_MSG("%s(%d):wait for update done .\n");
			//schedule();
		//}
		if(fake_s1d13522_is_logo_bypss()) {
			printk("%s() bypass logo\n",__FUNCTION__);
		}
		else {
			if(pbInitDCbuf) {
				int ilogo_width ,ilogo_height;
				
				#if 1
				if(k_get_wfbpp() == 4) 
				{
					k_set_wfmode(WF_GC16); // fill LUT with default waveform, for 4bit, use mode 2
				}
				else {
					k_set_wfmode(WF_GC4); // fill LUT with default waveform, for 3bit, use mode 3 (GC)
				}	
				#endif	
				
				if(gptHWCFG) {
					if(1==gptHWCFG->m_val.bDisplayResolution) {
						ilogo_width = 1024 ;
						ilogo_height = 758 ;
					}
					else if(2==gptHWCFG->m_val.bDisplayResolution) {
						ilogo_width = 1024 ;
						ilogo_height = 768 ;
					}
					else if(3==gptHWCFG->m_val.bDisplayResolution) {
						ilogo_width = 1440 ;
						ilogo_height = 1080 ;
					}
					else if(5==gptHWCFG->m_val.bDisplayResolution) {
						ilogo_width = 1448 ;
						ilogo_height = 1072 ;
					}
					else if(6==gptHWCFG->m_val.bDisplayResolution) {
						ilogo_width = 1600 ;
						ilogo_height = 1200 ;
					}
					else if(8==gptHWCFG->m_val.bDisplayResolution) {
						ilogo_width = 1872 ;
						ilogo_height = 1404 ;
					}
					else {
						ilogo_width = 800 ;
						ilogo_height = 600 ;
					}
				}
				else {
					ilogo_width = 800 ;
					ilogo_height = 600 ;
				}
				
				if( gdwLOGO_size>=((ilogo_width*ilogo_height)>>1) ) {
					u32 old_upd_scheme=g_fb_data->upd_scheme;
					u32 old_auto_mode=g_fb_data->auto_mode;
					u32 old_rotate=g_fb_data->info.var.rotate;


					DBG0_MSG("drawing logo begin ...\n");
					g_fb_data->epdc_fb_var.rotate = FB_ROTATE_UR;
					mxc_epdc_fb_check_var(&g_fb_data->info.var,&g_fb_data->info);

					mxc_epdc_fb_set_auto_update(AUTO_UPDATE_MODE_REGION_MODE,&g_fb_data->info);
					mxc_epdc_fb_set_upd_scheme(UPDATE_SCHEME_SNAPSHOT,&g_fb_data->info);

					fake_s1d13522_display_img(0,0,ilogo_width,ilogo_height,pbInitDCbuf,gptDC,4,0);
					k_wait_update_complete();

					mxc_epdc_fb_set_upd_scheme(old_upd_scheme,&g_fb_data->info);
					mxc_epdc_fb_set_auto_update(old_auto_mode,&g_fb_data->info);

					g_fb_data->info.var.rotate = old_rotate;
					mxc_epdc_fb_check_var(&g_fb_data->info.var,&g_fb_data->info);

					DBG_MSG("drawing logo end ...\n");
				}
				else {
					printk("logo skip : logosize %u < %u !! \n ",(unsigned int)gdwLOGO_size,
						((ilogo_width*ilogo_height)>>1));
				}
			}
		}
		fake_s1d13522_progress_start(gptDC);
		giIsInited=2;
		k_create_sys_attr();
		complete_all(&mxc_epdc_fake13522_inited);
			
		return 0;
	}
	else {
		printk("%s(%d): init fail !!\n",__FUNCTION__,__LINE__);
		return -1;
	}
}


static int k_fake_s1d13522_pan_display(unsigned long xoffset,unsigned long yoffset)
{
	epdfbdc_set_fbxyoffset(gptDC,xoffset,yoffset);
	return 0;
}

