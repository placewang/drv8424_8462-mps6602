#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_gpio.h"


/*
gpio��ؼ��ϳ�ʼ��
    -ledָʾ��
    -5·�����
    -24·���������
    -���ϸ��
    -���ʹ��/����/���ϼ��
*/
void appGpioSetsInit(void)
{
    bsp_led_init();
    bsp_Out24V_init();
    bsp_Sensor_iniit();
    bsp_Dipswitch_init();
    bsp_StepperMotorMicrostep_init();
    bsp_StepperMotorEN_DiR_FUAL_NRST_init();
}

/*
ָʾ��״̬��ת
time:���ʱ��
*/
uint32_t LedTimeCount=0; 
void app_System_Led(uint16_t time)
{
    if(LedTimeCount>=time)
    {
        gpio_bit_toggle(LEDPRO,LEDPIN);
        LedTimeCount=0;
    }
}
/*
��ȡ�����

return bit-ID0
       bit-ID1
*/
unsigned char appGetDipSwitchNum(void)
{

    uint8_t num=0;
    
    num|= gpio_input_bit_get(DIPSWITCH0_PORT,DIPSWITCH0_PIN)<<0;
    num|= gpio_input_bit_get(DIPSWITCH1_PORT,DIPSWITCH1_PIN)<<1;
    
    return num;
}

/*
4·���DRV8803��λ
*/
void appDrv88033_RST(void)
{   
    gpio_bit_write(OUT_RST_PORT,OUT_RST_PIN,SET);
    delay_1ms(10);
    gpio_bit_write(OUT_RST_PORT,OUT_RST_PIN,RESET);
}
/*
��ȡDrv8803����״̬
    ����Ч
*/
unsigned char appGetDrv88033FaultStatus(void)
{
    return gpio_input_bit_get(OUT_NFAULT_PORT,OUT_NFAULT_PIN);
}

/*
5·�������
    1-4·��DRV8803 - ����Ч
    5·  ����©���- ����Ч 
num   : 1-5·  0-ȫ��
status: 1-��
        0-��
return: -1-�����������
         1-ִ�����
         0-δִ��   
*/
int app5wayOutputEnWrite(unsigned char num,unsigned char status)
{   
    char sta=0;
   
    if(num>5){
        return -1;
    }
    
    sta=status==0?RESET:SET;
  
    switch (num)
    {
        case 1:
           gpio_bit_write(OUT1_EN_PORT,OUT1_EN_PIN,(bit_status)sta);
           return 1;
        case 2:
           gpio_bit_write(OUT2_EN_PORT,OUT2_EN_PIN,(bit_status)sta);
           return 1;
        case 3:
           gpio_bit_write(OUT3_EN_PORT,OUT3_EN_PIN,(bit_status)sta);
           return 1;
        case 4:
           gpio_bit_write(OUT4_EN_PORT,OUT4_EN_PIN,(bit_status)sta);
           return 1;
        case 5:
           gpio_bit_write(OUT5_EN_PORT,OUT5_EN_PIN,(bit_status)sta); 
           return 1;  
        case 0:
           gpio_bit_write(OUT1_EN_PORT,OUT1_EN_PIN,(bit_status)sta); 
           gpio_bit_write(OUT2_EN_PORT,OUT2_EN_PIN,(bit_status)sta);
           gpio_bit_write(OUT3_EN_PORT,OUT3_EN_PIN,(bit_status)sta); 
           gpio_bit_write(OUT4_EN_PORT,OUT4_EN_PIN,(bit_status)sta);
           gpio_bit_write(OUT5_EN_PORT,OUT5_EN_PIN,(bit_status)sta); 
           return 1;         
    }
    return 0; 
}

/*
��5·����ܽ�״̬
num   : 1-5· 
        0-ȫ��: bit0-out1,
                bit1-out2, 
                bit2-out3,
                bit3-out4,
                bit4-out5
return: -1-�����������
         1-ִ�����
         0-δִ��   
*/
int appRead5wayOutputPinStatus(unsigned char num)
{   
    int sta=0;
   
    if(num>5){
        return -1;
    }
  
    switch (num)
    {
        case 1:
           return gpio_input_bit_get(OUT1_EN_PORT,OUT1_EN_PIN);
        case 2:
           return gpio_input_bit_get(OUT2_EN_PORT,OUT2_EN_PIN);
        case 3:
           return gpio_input_bit_get(OUT3_EN_PORT,OUT3_EN_PIN);
        case 4:
           return gpio_input_bit_get(OUT4_EN_PORT,OUT4_EN_PIN);
        case 5:
           return gpio_input_bit_get(OUT4_EN_PORT,OUT4_EN_PIN); 
        case 0:
          sta|= gpio_input_bit_get(OUT1_EN_PORT,OUT1_EN_PIN)<<0; 
          sta|= gpio_input_bit_get(OUT2_EN_PORT,OUT2_EN_PIN)<<1;
          sta|= gpio_input_bit_get(OUT3_EN_PORT,OUT3_EN_PIN)<<2; 
          sta|= gpio_input_bit_get(OUT4_EN_PORT,OUT4_EN_PIN)<<3;
          sta|= gpio_input_bit_get(OUT5_EN_PORT,OUT5_EN_PIN)<<4; 
          return sta;         
    }
    return 0; 
}

/*
��ȡ������״̬
num   : 1-24· 
        0-ȫ��: bit0-IN0...bit23-IN27
return: -1-�����������  
*/

int appGetSensorStatus(unsigned char num)
{
    char i=0;
    int sta=0;
    uint32_t prot[24]={IN0_PORT,IN1_PORT,IN2_PORT,IN3_PORT,IN4_PORT,IN5_PORT,
                   IN6_PORT,IN7_PORT,IN8_PORT,IN9_PORT,IN10_PORT,IN11_PORT,
                   IN12_PORT,IN13_PORT,IN14_PORT,IN15_PORT,IN16_PORT,IN17_PORT, 
                   IN22_PORT,IN23_PORT,IN24_PORT,IN25_PORT,IN26_PORT,IN27_PORT 
                   };
    uint32_t pin[24]={ IN0_PIN,IN1_PIN,IN2_PIN,IN3_PIN,IN4_PIN,IN5_PIN,
                   IN6_PIN,IN7_PIN,IN8_PIN,IN9_PIN,IN10_PIN,IN11_PIN,
                   IN12_PIN,IN13_PIN,IN14_PIN,IN15_PIN,IN16_PIN,IN17_PIN, 
                   IN22_PIN,IN23_PIN,IN24_PIN,IN25_PIN,IN26_PIN,IN27_PIN 
                  };    
    if(num>24)
        return -1;
    
    if(num!=0)
        sta=gpio_input_bit_get(prot[num-1],pin[num-1]);
    else if(num==0)
    {
        for(i=0;i<24;i++)
        {
            sta|=gpio_input_bit_get(prot[i],pin[i])<<i;
        }
    }
    return sta;
}




