#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_gpio.h"
#include "bsp_spi.h"
#include "bsp_uart.h"
#include "app_drv8462.h"

/*
��drv8462�Ĵ���ֵ
addr:�Ĵ�����ַ
return:drv8462����ֵ
*/
unsigned short appDrv8462ReadRegisterVal(unsigned char addr)
{
    uint16_t senddata=0;
    
    senddata=(uint16_t)(addr<<8|0x00);
    return bsp_spi1_readdata_16bits(senddata);
}
/*
дdrv8462�Ĵ���ֵ
addr:�Ĵ�����ַ
data:Ҫд������
return:drv8462����ֵ
*/
unsigned short appDrv8462WriteRegisterVal(unsigned char addr,unsigned char data)
{
    uint16_t senddata=0;
    
    senddata=(uint16_t)(addr<<8|data);
//    log_debug("spi1writedata:0x%X \n",senddata);
    return bsp_spi1_writedata_16bits(senddata);
}

/*
��������������� 
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
�������ʹ��/ʹ������
*/
int appLiftingMotorEnbleSet(unsigned char Enb)
{
    uint8_t sta=0;
    sta=Enb==0?RESET:SET;
    gpio_bit_write(MT7EN_PORT,MT7EN_PIN,(bit_status)(!sta));  
    return 0;
}
/*
����������ϼĴ���״̬��ȡ
*/
unsigned char appGetLiftingMotorFaultRegisterSta(void)
{
    uint16_t sta=0;
    sta=appDrv8462ReadRegisterVal(SPI1_FAULT);
    return (uint8_t)(sta);
}
/*
�����������״̬��ȡ(�͵�ƽ��Ч)
*/
unsigned char appGetLiftingMotorFaultPinSta(void)
{
    uint8_t sta=0;
    sta=gpio_input_bit_get(MT7NFAULT_PORT,MT7NFAULT_PIN);
    return sta;
}















