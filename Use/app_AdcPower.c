#include "gd32f4xx.h"
#include "bsp_adc.h"

/*
电源检测初始化
*/
void appPowerDetectionInit(void)
{
    bsp_adc_dma_init();
}

/*
获取检测电压值(0-3.3)未滤波
DC12V:12V电压值
DC24V:24V电压值
*/
int appGetPowerVoltageValue(float* DC12V,float* DC24V)
{
    if(DC12V==NULL||DC24V==NULL)
    {
        return -1;
    }
    *DC12V=((float)adc_value[1]/4096.0f)*3.3f;
    *DC24V=((float)adc_value[0]/4096.0f)*3.3f;
    return 0;
}
/*
获取检测实际电压值(0-12/24V)未滤波
DC12V:12V电压值
DC24V:24V电压值
*/
int appGetPowerActualVoltageValue(float* DC12V,float* DC24V)
{
    float dc12VmaxVoltageVal=1328;
    float dc24VmaxVoltageVal=1397;
    
    if(DC12V==NULL||DC24V==NULL)
    {
        return -1;
    }
    *DC12V=((float)adc_value[1]/dc12VmaxVoltageVal)*12.0f;
    *DC24V=((float)adc_value[0]/dc24VmaxVoltageVal)*24.0f;
    
    return 0;
}






