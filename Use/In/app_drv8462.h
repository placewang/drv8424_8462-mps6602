#ifndef _APPDRV8462_H
#define _APPDRV8462_H


// Bit Mask definitions for Registers
// Register 0x00: FAULT Register
#define FAULT_OL_MASK               (0x01)         // 该位为1b时表示存在开路负载故障情况
#define FAULT_OT_MASK               (0x02)         // 过热警告(OTW)和过热关断(OTSD)的逻辑或,该位为1b时表示出现过热故障
#define FAULT_STL_MASK              (0x04)         // 该位为1b时表示存在电机失速情况
#define FAULT_OCP_MASK              (0x08)         // 该位为1b时表示存在过流故障情况
#define FAULT_CPUV_MASK             (0x10)         // 该位为1b时表示存在电荷泵欠压故障情况
#define FAULT_UVLO_MASK             (0x20)         // 该位为1b时表示存在电源欠压锁定故障情况
#define FAULT_SPIERROR_MASK         (0x40)         /* SPI协议错误SCLK脉冲多于所需或缺少
                                                      nSCS为低电平SPI_ERROR会在出现故障时变为1bnFAULT引脚会被驱动为低电平
                                                      当协议错误消失时并且已通过CLR_FLT位或nSLEEP复位脉冲发出清除故障命令后,器件恢复正常运行
                                                   */
#define FAULT_MASK                  (0x80)         /* 器件出现任何故障情况时,FAULT位为1b,正常期间FAULT位为0b,
                                                      当 FAULT 位为1b时,nFAULT 引脚会被下拉,在正常工作期间,nFAULT引脚会被释放
                                                   */
// DRV8xx2 SPI Register Addresses
enum
{
  SPI1_FAULT             = 0x00,
  SPI1_DIAG1             = 0x01,
  SPI1_DIAG2             = 0x02,
  SPI1_DIAG3             = 0x03,
  SPI1_CTRL1             = 0x04,
  SPI1_CTRL2             = 0x05,
  SPI1_CTRL3             = 0x06,
  SPI1_CTRL4             = 0x07,
  SPI1_CTRL5             = 0x08,
  SPI1_CTRL6             = 0x09,
  SPI1_CTRL7             = 0x0A,
  SPI1_CTRL8             = 0x0B,
  SPI1_CTRL9             = 0x0C,
  SPI1_CTRL10            = 0x0D,
  SPI1_CTRL11            = 0x0E,
  SPI1_CTRL12            = 0x0F,
  SPI1_CTRL13            = 0x10,
  SPI1_INDEX1            = 0x11,
  SPI1_INDEX2            = 0x12,
  SPI1_INDEX3            = 0x13,
  SPI1_INDEX4            = 0x14,
  SPI1_INDEX5            = 0x15,
  SPI1_CUSTOM_CTRL1      = 0x16,
  SPI1_CUSTOM_CTRL2      = 0x17,
  SPI1_CUSTOM_CTRL3      = 0x18,
  SPI1_CUSTOM_CTRL4      = 0x19,
  SPI1_CUSTOM_CTRL5      = 0x1A,
  SPI1_CUSTOM_CTRL6      = 0x1B,
  SPI1_CUSTOM_CTRL7      = 0x1C,
  SPI1_CUSTOM_CTRL8      = 0x1D,
  SPI1_CUSTOM_CTRL9      = 0x1E,
  SPI1_ATQ_CTRL1         = 0x1F,
  SPI1_ATQ_CTRL2         = 0x20,
  SPI1_ATQ_CTRL3         = 0x21,
  SPI1_ATQ_CTRL4         = 0x22,
  SPI1_ATQ_CTRL5         = 0x23,
  SPI1_ATQ_CTRL6         = 0x24,
  SPI1_ATQ_CTRL7         = 0x25,
  SPI1_ATQ_CTRL8         = 0x26,
  SPI1_ATQ_CTRL9         = 0x27,
  SPI1_ATQ_CTRL10        = 0x28,
  SPI1_ATQ_CTRL11        = 0x29,
  SPI1_ATQ_CTRL12        = 0x2A,
  SPI1_ATQ_CTRL13        = 0x2B,
  SPI1_ATQ_CTRL14        = 0x2C,
  SPI1_ATQ_CTRL15        = 0x2D,
  SPI1_ATQ_CTRL16        = 0x2E,
  SPI1_ATQ_CTRL17        = 0x2F,
  SPI1_ATQ_CTRL18        = 0x30,
  SPI1_SS_CTRL1          = 0x31,
  SPI1_SS_CTRL2          = 0x32,
  SPI1_SS_CTRL3          = 0x33,
  SPI1_SS_CTRL4          = 0x34,
  SPI1_SS_CTRL5          = 0x35,
  SPI1_CTRL14            = 0x3C,
};
//寄存器默认值
enum
{
  CTRL1             = 0x0F,
  CTRL2             = 0x06,
  CTRL3             = 0x38,
  CTRL4             = 0x49,
  CTRL5             = 0x03,
  CTRL6             = 0x20,
  CTRL9             = 0x10,
  CTRL10            = 0x80,
  CTRL11            = 0xFF,
  CTRL12            = 0x20,
  CTRL13            = 0x10,
//  CUSTOM_CTRL1      = 0x16,
//  CUSTOM_CTRL2      = 0x17,
//  CUSTOM_CTRL3      = 0x18,
//  CUSTOM_CTRL4      = 0x19,
//  CUSTOM_CTRL5      = 0x1A,
//  CUSTOM_CTRL6      = 0x1B,
//  CUSTOM_CTRL7      = 0x1C,
//  CUSTOM_CTRL8      = 0x1D,
//  CUSTOM_CTRL9      = 0x1E,
//  ATQ_CTRL2         = 0x20,
//  ATQ_CTRL3         = 0x21,
//  ATQ_CTRL4         = 0x22,
//  ATQ_CTRL5         = 0x23,
//  ATQ_CTRL6         = 0x24,
//  ATQ_CTRL7         = 0x25,
//  ATQ_CTRL8         = 0x26,
//  ATQ_CTRL9         = 0x27,
//  ATQ_CTRL10        = 0x28,
//  ATQ_CTRL11        = 0x29,
//  ATQ_CTRL12        = 0x2A,
//  ATQ_CTRL13        = 0x2B,
//  ATQ_CTRL14        = 0x2C,
//  ATQ_CTRL15        = 0x2D,
//  ATQ_CTRL17        = 0x2F,
//  ATQ_CTRL18        = 0x30,
    SS_CTRL1  = 0x00,
//  SILENTSTEP_CTRL2  = 0x32,
//  SILENTSTEP_CTRL3  = 0x33,
//  SILENTSTEP_CTRL4  = 0x34,
//  SILENTSTEP_CTRL5  = 0x35,
//  CTRL14            = 0x3C,
};
//细分配置参数
enum
{
  MicroStep1_100 = 0x00,  // 0000b Full step with 100% current
  MicroStep1     = 0x01,  // 0001b Full step with 71% current
  MicroStep2_NC  = 0x02,  // 0010b Non-circular 1/2 step
  MicroStep2     = 0x03,  // 0011b Circular 1/2 step
  MicroStep4     = 0x04,  // 0100b 1/4   step
  MicroStep8     = 0x05,  // 0101b 1/8   step
  MicroStep16    = 0x06,  // 0110b 1/16  step
  MicroStep32    = 0x07,  // 0111b 1/32  step
  MicroStep64    = 0x08,  // 1000b 1/64  step
  MicroStep128   = 0x09,  // 1001b 1/128 step
  MicroStep256   = 0x0A,  // 1010b 1/256 step
};

//衰减模式
enum
{
  SlowDecay    = 0x00,           //慢速衰减
  Mixed30Decay = 0x04,           //混合30%衰减
  Mixed60Decay = 0x05,           //混合60%衰减
  SmartTuneDynamicDecay  = 0x06, //智能调优动态衰减
  SmartTuneRippleControl = 0x07, //智能调优纹波控制 
};
//锁定电流比例(满量程电流6A)
enum
{
  HoldCurr_10    = 0x19,      //10%(0.1*6A=0.6A)
  HoldCurr_20    = 0x33,      //20%
  HoldCurr_40    = 0x66,      //40%
  HoldCurr_50    = 0x80,      //50%
  HoldCurr_60    = 0x99,      //60%
  HoldCurr_70    = 0xB3,      //70%    
};

unsigned short appDrv8462ReadRegisterVal(unsigned char addr);
unsigned short appDrv8462WriteRegisterVal(unsigned char addr,unsigned char data);
unsigned char  appGetLiftingMotorFaultRegisterSta(void);
unsigned char  appGetLiftingMotorFaultPinSta(void);
int appLiftingMotorDirSet(char dir);
int appLiftingMotorEnbleSet(unsigned char Enb);
unsigned char appGetLiftingMotorFaultRegisterSta(void);
unsigned char appGetLiftingMotorFaultPinSta(void);

#endif


