#include "gd32f4xx.h"
#include "bsp_adc.h"

/*
��Դ����ʼ��
*/
void appPowerDetectionInit(void)
{
    bsp_adc_dma_init();
}

/*
��ȡ����ѹֵ(0-3.3)δ�˲�
DC12V:12V��ѹֵ
DC24V:24V��ѹֵ
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
��ȡ���ʵ�ʵ�ѹֵ(0-12/24V)δ�˲�
DC12V:12V��ѹֵ
DC24V:24V��ѹֵ
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






