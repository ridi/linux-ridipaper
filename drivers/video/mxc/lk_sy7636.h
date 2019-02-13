#ifndef __LK_SY7636_H //[
#define __LK_SY7636_H


#define SY7636_RET_SUCCESS							0
#define SY7636_RET_GPIOINITFAIL					(-1)
#define SY7636_RET_MEMNOTENOUGH					(-2)
#define SY7636_RET_NOTINITEDSTATE				(-3)
#define SY7636_RET_PWRDWNWORKPENDING		(-4)
#define SY7636_RET_I2CCHN_NOTFOUND			(-5)
#define SY7636_RET_I2CTRANS_ERR					(-6)


int sy7636_init(int iPort);
void sy7636_release(void);


int sy7636_suspend(void);
void sy7636_resume(void);
void sy7636_shutdown(void);


int sy7636_output_power(int iIsOutputPwr,int iIsChipPowerDown);
int sy7636_power_onoff(int iIsPowerOn,int iIsOutputPwr);

int sy7636_get_temperature(int *O_piTemperature);
int sy7636_vcom_set(int iVCOM_mV,int iIsWriteToFlash);
int sy7636_vcom_get(int *O_piVCOM_mV);
int sy7636_vcom_get_cached(int *O_piVCOM_mV);

int sy7636_ONOFF(int iIsON);

typedef void *(SY7636_INTEVT_CB)(int iEVENT);
int sy7636_int_callback_setup(SY7636_INTEVT_CB fnCB);

#endif //] __LK_SY7636_H

