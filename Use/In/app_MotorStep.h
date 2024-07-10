#ifndef _APPMOTORSTEP_H
#define _APPMOTORSTEP_H


//运行模式
#define MODE_S       0           //速度模式
#define MODE_P       1           //位置模式
//加减速计算参数
#define TIM1COUNTCYCLE    0.000001   //计数周期

/*电机速度决策中的四个状态*/
#define STOP              0 // 停止状态
#define ACCEL             1 // 加速状态
#define DECEL             2 // 减速状态
#define RUN               3 // 匀速状态
/*电机编号*/
enum MotorNum
{
    Motor1 =1,
    Motor2,
    Motor3,
    
    Motor4,
    Motor5,
    Motor6,
    
    Motor7,
    Motor8,
    Motor9
};

/*梯形加减速相关*/
typedef struct 
{
    //电机运动正方向 
    unsigned char  FwDir;         
    /*定时器使用翻转模式，需要进入两次中断才输出一个完整脉冲*/
	unsigned char i; 
    /*位置模式/速度模式*/
    unsigned char mode;               
	/*当前电机状态*/
	unsigned char run_state ; 
	/*旋转方向*/
	unsigned char dir ; 
    //锁定电流   
    unsigned short LockCurrent;  
    //运行电流
    unsigned short RunCurrent;   
	/* 保存新（下）一个延时周期*/
	unsigned short new_step_delay;
	/* 加速过程中最后一次延时（脉冲周期）*/
	unsigned short last_accel_delay;
    /*减速系数*/
    unsigned short accel_step;    
	/*脉冲间隔*/
	int  step_delay;  
	/*减速位置*/
	int  decel_start; 
	/*减速步数*/
	int  decel_val;   
	/*最小间隔*/
	int  min_delay;   
	/*加速步数*/
	int  accel_count; 
    /*余数补偿*/
	int  rest;
    /*软件编码器*/
    int  Encoder;    
	/* 总移动步数计数器*/
	unsigned int step_count;
    /*目标位置*/
    unsigned int TargetStepCont;
   
}MotorStep;

extern unsigned short STEPCOUNT;   //加减速步数


void appMotorStepInit(void);
MotorStep* GetMorotParameterPointer(unsigned char num);
int appMotorSpeedModeMove_T(unsigned char stepnum,int speed);
int appMotorStepModeMove_T(unsigned char stepnum,unsigned char mode,int step,unsigned int speed);

#endif











