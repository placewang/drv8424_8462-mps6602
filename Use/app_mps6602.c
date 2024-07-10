#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_gpio.h"
#include "bsp_spi.h"
#include "bsp_uart.h"
#include "app_mps6602.h"

/*
读drv8462寄存器值
addr:寄存器地址
return:drv8462返回值
*/
unsigned short appMps6602ReadRegisterVal(unsigned char num,unsigned char addr)
{
    uint16_t senddata=0;
    senddata=(uint16_t)((addr<<8)|0x00);
    return bsp_spi0_readdata_16bits(num,senddata);
}
/*
写drv8462寄存器值
num:1-NSS1(motor8)
    2-Nss2(motor9)
addr:寄存器地址
data:要写入数据
return:drv8462返回值
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
拉线电机使能/使能设置
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
拉线电机方向设置
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
拉线电机复位
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
拉线电机故障寄存器状态获取
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
拉线电机故障状态获取(低电平有效)
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


