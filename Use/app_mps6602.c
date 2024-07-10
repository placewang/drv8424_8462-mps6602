#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_gpio.h"
#include "bsp_spi.h"
#include "bsp_uart.h"
#include "app_mps6602.h"

/*
��drv8462�Ĵ���ֵ
addr:�Ĵ�����ַ
return:drv8462����ֵ
*/
unsigned short appMps6602ReadRegisterVal(unsigned char num,unsigned char addr)
{
    uint16_t senddata=0;
    senddata=(uint16_t)((addr<<8)|0x00);
    return bsp_spi0_readdata_16bits(num,senddata);
}
/*
дdrv8462�Ĵ���ֵ
num:1-NSS1(motor8)
    2-Nss2(motor9)
addr:�Ĵ�����ַ
data:Ҫд������
return:drv8462����ֵ
*/
unsigned short appMps6602WriteRegisterVal(unsigned char num,unsigned char addr,unsigned short data)
{
    uint16_t senddata=0;
    uint16_t sta=0;
    senddata=(uint16_t)((addr<<8)|data);
//    log_debug("spi0_write:0x%X \n",senddata);
    sta=bsp_spi0_writedata_16bits(num,senddata);
//    log_debug("spi0_write_Rev:0x%X \n",sta);
    return sta;
}


/*
���ߵ��ʹ��/ʹ������
num:0- all motor
    1- (motor8)
    2- (motor9)
Enb: 0/!0 
*/
int appPullMotorEnbleSet(unsigned char num,unsigned char Enb)
{
    uint8_t sta=0;
    sta=Enb==0?RESET:SET;
    if(num==0||num==1)
        gpio_bit_write(MT8EN_PORT,MT8EN_PIN,(bit_status)sta);
    if(num==0||num==2)
        gpio_bit_write(MT9EN_PORT,MT9EN_PIN,(bit_status)sta);    
    return 0;
}
/*
���ߵ����������
num:0- all motor
    1- (motor8)
    2- (motor9)
dir: 0/!0 
*/
int appPullMotorDirSet(unsigned char num,char dir)
{
  uint8_t sta=0;
  sta=dir==0?RESET:SET;
  if(num==0||num==1)
    gpio_bit_write(MT8DIR_PORT,MT8DIR_PIN,(bit_status)sta); 
  if(num==0||num==2)
    gpio_bit_write(MT9DIR_PORT,MT9DIR_PIN,(bit_status)sta);   
  return 0;
}
/*
���ߵ����λ
num:0- all motor
    1- (motor8)
    2- (motor9)
*/
int appPullMotorReseting(unsigned char num)
{   
  if(num==0||num==1)
  {
    gpio_bit_reset(MT8_NRST_PORT,MT8_NRST_PIN);
    delay_1ms(50);
    gpio_bit_set(MT8_NRST_PORT,MT8_NRST_PIN);
  }
  if(num==0||num==2)
  {
    gpio_bit_reset(MT9_NRST_PORT,MT9_NRST_PIN);
    delay_1ms(50);
    gpio_bit_set(MT9_NRST_PORT,MT9_NRST_PIN);    
  }      
  return 0;
}
/*
���ߵ�����ϼĴ���״̬��ȡ
num:1- (motor8)
    2- (motor9)
*/
unsigned char appGetPullMotorFaultRegisterSta(unsigned char num)
{
    uint16_t sta=0;
    if(num==1||num==2)
        sta=appMps6602ReadRegisterVal(num,SPI0_FAULT);
    return (uint8_t)(sta);
}
/*
���ߵ������״̬��ȡ(�͵�ƽ��Ч)
num:1- (motor8)
    2- (motor9)
*/
unsigned char appGetPullMotorFaultPinSta(unsigned char num)
{
    uint8_t sta=0;
    if(num==1)
        sta=gpio_input_bit_get(MT8NFAULT_PORT,MT8NFAULT_PIN);
    else if(num==2)
        sta=gpio_input_bit_get(MT9NFAULT_PORT,MT9NFAULT_PIN);
    return sta;
}


