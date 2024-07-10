#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_uart.h"
#include "bsp_gpio.h"
#include "bsp_time.h"

/*
剪刀夹子电机细分设置(电路默认4细分)
group: 1--左剪刀,右剪刀
       2-右夹1,右夹2,左夹1,左夹2
       0-全部 
microstep:  0-全步  0 0
            2-1/2步 1 0
            4-1/4步 0 1 
            8-1/8步 1 1
*/
int appScissorsClipMotorMicrostepSet(unsigned char group,unsigned char microstep)
{
    uint8_t M0=0;
    uint8_t M1=0;
    if(group!=0&&group!=1&&group!=2)
        return -1;
    switch(microstep)
    {
        case 0:
          M0=RESET;
          M1=RESET;
          break;
        case 2:
          M0=SET;
          M1=RESET;
          break;
        case 4:
          M0=RESET;
          M1=SET;
          break;
        case 8:
          M0=SET;
          M1=SET;
          break;
        default:
            return -1;
    }
    if(group==1||group==0)
    {
       gpio_bit_write(JD_M0_PORT,JD_M0_PIN,(bit_status)(!M0));
       gpio_bit_write(JD_M1_PORT,JD_M1_PIN,(bit_status)(!M1)); 
    }
    if(group==2||group==0)
    {
       gpio_bit_write(JZ_M0_PORT,JZ_M0_PIN,(bit_status)(!M0));
       gpio_bit_write(JZ_M1_PORT,JZ_M1_PIN,(bit_status)(!M1)); 
    }
    return 1;
}
/*
剪刀夹子电机方向设置
num: 1-6 
     0-全部 
dir: 0/!0 
*/
int appScissorsClipMotorDirSet(unsigned char num,unsigned char dir)
{
    uint8_t i=0;
    uint8_t sta=0;
    
    uint32_t prot[6]={  MT1DIR_PORT,MT2DIR_PORT,MT3DIR_PORT,
                        MT4DIR_PORT,MT5DIR_PORT,MT6DIR_PORT
                     };
    uint32_t pin[6]={ MT1DIR_PIN,MT2DIR_PIN,MT3DIR_PIN,
                      MT4DIR_PIN,MT5DIR_PIN,MT6DIR_PIN,
                    }; 
    if(num>6)
        return -1;
    sta=dir==0?RESET:SET;
    if(num!=0){
        gpio_bit_write(prot[num-1],pin[num-1],(bit_status)sta);
    }
    if(num==0)
    {
        for(i=0;i<6;i++)
        {
            gpio_bit_write(prot[i],pin[i],(bit_status)sta);
        }        
    }
    return 1;
}
/*
剪刀夹子电机使能/失能设置
num: 1-6 
     0-全部 
En: 0/!0 
*/
int appScissorsClipMotorEnbleSet(unsigned char num,unsigned char Enb)
{
    uint8_t i=0;
    
    uint8_t sta=0;

    uint32_t prot[6]={  MT1EN_PORT,MT2EN_PORT,MT3EN_PORT,
                        MT4EN_PORT,MT5EN_PORT,MT6EN_PORT
                     };
    uint32_t pin[6]={ MT1EN_PIN,MT2EN_PIN,MT3EN_PIN,
                      MT4EN_PIN,MT5EN_PIN,MT6EN_PIN,
                    }; 
    if(num>6)
        return -1;
    sta=Enb==0?RESET:SET;
    if(num!=0){
        gpio_bit_write(prot[num-1],pin[num-1],(bit_status)sta);
    }
    if(num==0)
    {
        for(i=0;i<6;i++)
        {
            gpio_bit_write(prot[i],pin[i],(bit_status)sta);
        }        
    }
    return 1;
}

/*
剪刀夹子电机故障状态获取(低电平有效)
num: 1-6 
     0-全部 
*/
int appGetScissorsClipGetMotorFault(unsigned char num)
{
    uint8_t i=0;
    
    uint8_t sta=0;

    uint32_t prot[6]={  MT1NFAULT_PORT,MT2NFAULT_PORT,MT3NFAULT_PORT,
                        MT4NFAULT_PORT,MT5NFAULT_PORT,MT6NFAULT_PORT
                     };
    uint32_t pin[6]={ MT1NFAULT_PIN,MT2NFAULT_PIN,MT3NFAULT_PIN,
                      MT4NFAULT_PIN,MT5NFAULT_PIN,MT6NFAULT_PIN,
                    }; 
    if(num>6)
        return -1;
    if(num!=0)
        sta=gpio_input_bit_get(prot[num-1],pin[num-1]);
    else if(num==0)
    {
        for(i=0;i<6;i++)
        {
            sta|=gpio_input_bit_get(prot[i],pin[i])<<i;
        }
    }
    return sta;
}

/*
剪刀夹子电机电流设
(IFS):IFS(A)=VREF(V)/KV(V/A)=VREF(V)/1.32(V/A)
num: 1-6 
     0-全部 
current:电流值(1-2500ma)
*/
int appScissorsClipMotorCurrentSet(unsigned char num,unsigned short current)
{
    char      i=0;
    float     VREF=0.0;
    uint16_t  CurrentVal=0;
    uint16_t  CHNum[4]={TIMER_CH_0,TIMER_CH_1,TIMER_CH_2,TIMER_CH_3};  
    
    if(num>6||current>2500)
    {
        return -1;
    }
    
    VREF=(float)current*1320.0f;
    CurrentVal=(uint32_t)(((float)PWM_MAXVAL*VREF/3300.0f)/1000.0f);

    if(num>0&&num<=4){ 
        timer_channel_output_pulse_value_config(TIMER3,CHNum[(num-1)],CurrentVal);
    }
    else if(num>4&&num<=6){
      timer_channel_output_pulse_value_config(TIMER8,CHNum[(num-5)],CurrentVal);  
    }
    else if(num==0)
    {
        for(i=0;i<6;i++)
        {
            if(i>3){
               timer_channel_output_pulse_value_config(TIMER8,CHNum[(i-4)],CurrentVal);  
            }
            else{
               timer_channel_output_pulse_value_config(TIMER3,CHNum[i],CurrentVal);
            }
        }
    }
    return 0;
}














