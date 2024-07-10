#ifndef _APPMPS6602_H
#define _APPMPS6602_H


// mps6602 SPI Register Addresses
enum
{
  SPI0_CTRL        = 0x00,
  SPI0_CTRL2       = 0x20,
  SPI0_ISET        = 0x40,
  SPI0_STALL       = 0x60,
  SPI0_BEMF        = 0x80,
  SPI0_TSTP        = 0xA0,
  SPI0_OCP         = 0xC0,
  SPI0_FAULT       = 0xE0,
};


//电流参数
enum
{
    Current125mA    =0x00,
    Current250mA    =0x01,
    Current375mA    =0x02,
    Current500mA    =0x03,    
    Current625mA    =0x04,
    Current750mA    =0x05,
    Current875mA    =0x06,
    Current1000mA   =0x07, 
    Current1130mA   =0x08,
    Current1250mA   =0x09,
    Current1380mA   =0x0A,
    Current1500mA   =0x0B,    
    Current1630mA   =0x0C,
    Current1750mA   =0x0D,
    Current1880mA   =0x0E,
    Current2000mA   =0x0F,
    
    Current2130mA   =0x10,
    Current2250mA   =0x11,
    Current2380mA   =0x12,
    Current2500mA   =0x13,    
    Current2630mA   =0x14,
    Current2750mA   =0x15,
    Current2880mA   =0x16,
    Current3000mA   =0x17, 
    Current3120mA   =0x18,
    Current3250mA   =0x19,
    Current3380mA   =0x1A,
    Current3500mA   =0x1B,    
    Current3630mA   =0x1C,
    Current3750mA   =0x1D,
    Current3880mA   =0x1E,
    Current4000mA   =0x1F
};
//保持电流自动响应时间
enum
{
    HoldTime15_6ms    =0x01,
    HoldTime31_3ms    =0x02,
    HoldTime62_5ms    =0x03,
    HoldTime125ms     =0x04,
    HoldTime250ms     =0x05,
    HoldTime500ms     =0x06,
    HoldTime1000ms    =0x07,    
};
//细分配置参数
enum
{
  step_1   = 0x00,   // Full step (70%)
  step_2   = 0x01,   // Half-step
  step_4   = 0x02,   // Quarter-step
  step_8   = 0x03,   // Eighth-step
  step_16  = 0x04,   // 1/16-step
  step_32  = 0x05,   // 1/16-step
};

unsigned short appMps6602ReadRegisterVal(unsigned char num,unsigned char addr);
unsigned short appMps6602WriteRegisterVal(unsigned char num,unsigned char addr,unsigned short data);
unsigned char appGetPullMotorFaultRegisterSta(unsigned char num);
unsigned char appGetPullMotorFaultPinSta(unsigned char num);
int appPullMotorDirSet(unsigned char num,char dir);
int appPullMotorEnbleSet(unsigned char num,unsigned char Enb);
int appPullMotorReseting(unsigned char num);


#endif


