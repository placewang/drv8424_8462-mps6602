#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_gpio.h"
#include "bsp_spi.h"
#include "bsp_uart.h"
#include "app_drv8462.h"

/*
读drv8462寄存器值
addr:寄存器地址
return:drv8462返回值
*/
unsigned short appDrv8462ReadRegisterVal(unsigned char addr)
{
    uint16_t senddata=0;
    
    senddata=(uint16_t)(addr<<8|0x00);
    return bsp_spi1_readdata_16bits(senddata);
}
/*
写drv8462寄存器值
addr:寄存器地址
data:要写入数据
return:drv8462返回值
*/
unsigned short appDrv8462WriteRegisterVal(unsigned char addr,unsigned char data)
{
    uint16_t senddata=0;
    
    senddata=(uint16_t)(addr<<8|data);
//    log_debug("spi1writedata:0x%X \n",senddata);
    return bsp_spi1_writedata_16bits(senddata);
}

/*
升降电机方向设置 
dir: 0/!0 
*/
int appLiftingMotorDirSet(char dir)
{
  uint8_t sta=0;
  sta=dir==0?RESET:SET;
  gpio_bit_write(MT7DIR_PORT,MT7DIR_PIN,(bit_status)sta);  
  return 0;
}
/*
升降电机使能/使能设置
*/
int appLiftingMotorEnbleSet(unsigned char Enb)
{
    uint8_t sta=0;
    sta=Enb==0?RESET:SET;
    gpio_bit_write(MT7EN_PORT,MT7EN_PIN,(bit_status)(!sta));  
    return 0;
}
/*
升降电机故障寄存器状态获取
*/
unsigned char appGetLiftingMotorFaultRegisterSta(void)
{
    uint16_t sta=0;
    sta=appDrv8462ReadRegisterVal(SPI1_FAULT);
    return (uint8_t)(sta);
}
/*
升降电机故障状态获取(低电平有效)
*/
unsigned char appGetLiftingMotorFaultPinSta(void)
{
    uint8_t sta=0;
    sta=gpio_input_bit_get(MT7NFAULT_PORT,MT7NFAULT_PIN);
    return sta;
}















