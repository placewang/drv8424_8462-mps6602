#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_uart.h"
#include "bsp_time.h"
#include "app_Motorstep.h"
#include "app_MotorConfig.h"

void speed_decision(uint8_t Mnum,MotorStep *srd);

MotorStep Mt1Step,Mt2Step,Mt3Step;
MotorStep Mt4Step,Mt5Step,Mt6Step;           
MotorStep Mt7Step,Mt8Step,Mt9Step; 

uint16_t STEPCOUNT=30;        //加减速步数


/*中断处理函数_Mt1*/
void TIM1_Interrupt_Mt1(void)
{
    gpio_bit_toggle(MT_STEP1_PORT,MT_STEP1_PIN);
    speed_decision(Motor1,&Mt1Step);
    timer_autoreload_value_config(TIMER1,0xffffffff&(Mt1Step.new_step_delay));    
    return;
}
/*中断处理函数_Mt2*/
void TIM2_Interrupt_Mt2(void)
{
    gpio_bit_toggle(MT_STEP2_PORT,MT_STEP2_PIN);
    speed_decision(Motor2,&Mt2Step);
    timer_autoreload_value_config(TIMER2,0xffff&(Mt2Step.new_step_delay));    
    return;
}
/*中断处理函数_Mt3*/
void TIM4_Interrupt_Mt3(void)
{
    gpio_bit_toggle(MT_STEP3_PORT,MT_STEP3_PIN);
    speed_decision(Motor3,&Mt3Step);
    timer_autoreload_value_config(TIMER4,0xffffffff&(Mt3Step.new_step_delay));    
    return;
}
/*中断处理函数_Mt4*/
void TIM5_Interrupt_Mt4(void)
{
    gpio_bit_toggle(MT_STEP4_PORT,MT_STEP4_PIN);
    speed_decision(Motor4,&Mt4Step);
    timer_autoreload_value_config(TIMER5,0xffff&(Mt4Step.new_step_delay));    
    return;
}
/*中断处理函数_Mt5*/
void TIM6_Interrupt_Mt5(void)
{
    gpio_bit_toggle(MT_STEP5_PORT,MT_STEP5_PIN);
    speed_decision(Motor5,&Mt5Step);
    timer_autoreload_value_config(TIMER6,0xffff&(Mt5Step.new_step_delay));    
    return;
}

/*中断处理函数_Mt6*/
void TIM9_Interrupt_Mt6(void)
{
    gpio_bit_toggle(MT_STEP6_PORT,MT_STEP6_PIN);
    speed_decision(Motor6,&Mt6Step);
    timer_autoreload_value_config(TIMER9,0xffff&(Mt6Step.new_step_delay));    
    return;
}
/*中断处理函数_Mt7*/
void TIM10_Interrupt_Mt7(void)
{
    gpio_bit_toggle(MT_STEP7_PORT,MT_STEP7_PIN);
    speed_decision(Motor7,&Mt7Step);
    timer_autoreload_value_config(TIMER10,0xffff&(Mt7Step.new_step_delay));    
    return;
}
/*中断处理函数_Mt8*/
void TIM11_Interrupt_Mt8(void)
{
    gpio_bit_toggle(MT_STEP8_PORT,MT_STEP8_PIN);
    speed_decision(Motor8,&Mt8Step);
    timer_autoreload_value_config(TIMER11,0xffff&(Mt8Step.new_step_delay));    
    return;
}
/*中断处理函数_Mt9*/
void TIM12_Interrupt_Mt9(void)
{
    gpio_bit_toggle(MT_STEP9_PORT,MT_STEP9_PIN);
    speed_decision(Motor9,&Mt9Step);
    timer_autoreload_value_config(TIMER12,0xffff&(Mt9Step.new_step_delay));    
    return;
}
/*
步进电机控制初始化
    -中断处理回调函数赋值
    -脉冲定时器初始化
    -9路电机上电默认参数
    -Drv8424初始化
    -Drv8462初始化
    -MPS6602初始化
*/
void appMotorStepInit(void)
{
    Step1_TIM1InterruptCallback=TIM1_Interrupt_Mt1;
    Step2_TIM2InterruptCallback=TIM2_Interrupt_Mt2;
    Step3_TIM4InterruptCallback=TIM4_Interrupt_Mt3;
    Step4_TIM5InterruptCallback=TIM5_Interrupt_Mt4;
    Step5_TIM6InterruptCallback=TIM6_Interrupt_Mt5;
    Step6_TIM9InterruptCallback=TIM9_Interrupt_Mt6;
    Step7_TIM10InterruptCallback=TIM10_Interrupt_Mt7;
    Step8_TIM11InterruptCallback=TIM11_Interrupt_Mt8;
    Step9_TIM12InterruptCallback=TIM12_Interrupt_Mt9;
    
    bsp_Time1Step_init();
    bsp_Time2Step_init();
    bsp_Time4Step_init();
    bsp_Time5Step_init();
    bsp_Time6Step_init(); 
    bsp_Time9Step_init();
    bsp_Time10Step_init();
    bsp_Time11Step_init();
    bsp_Time12Step_init();
    
    app_NineStepperMotorsDefaultParameter();
    appDrv8424Init();
    appDrv8462Init();
    appMps6602Init();
  
}


/*
根据电机编号赋值加减速度句柄指针
num:电机编号
return ：句柄指针
*/
MotorStep* GetMorotParameterPointer(unsigned char num)
{
   if(num==1) 
      return &Mt1Step;  
   else if(num==2)
      return &Mt2Step; 
   else if(num==3)
      return &Mt3Step;   
   else if(num==4)
      return &Mt4Step; 
   else if(num==5)
      return &Mt5Step; 
   else if(num==6)
      return &Mt6Step; 
   else if(num==7)
      return &Mt7Step;   
   else if(num==8)
      return &Mt8Step;  
   else if(num==9)
      return &Mt9Step; 
           
   return NULL;
}


/*
电机启动
Mstep;   电机操作句柄
startnum:编号(1-9)
*/
int Motor_Star_Set(MotorStep* Mstep,unsigned char startnum)
{
    uint32_t  handle[10]={0,TIMER1,TIMER2,TIMER4,\
                            TIMER5,TIMER6,TIMER9,\
                            TIMER10,TIMER11,TIMER12
                         };
    uint32_t source[10]={0,TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,\
                           TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,\
                           TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP
                        };
    if(Mstep==NULL)
        return -1;    
    if(startnum==0||startnum>9)
        return -1;

    timer_interrupt_enable(handle[startnum],source[startnum]);
    timer_enable(handle[startnum]);

    timer_counter_value_config(handle[startnum],0);  
    timer_autoreload_value_config(handle[startnum],Mstep->new_step_delay);  
    return 0;
}

/*
电机停止
Mstep;   电机操作句柄
startnum:编号(1-9)
*/
int Motor_Stop_Set(MotorStep* Mstep,unsigned char stopnum)
{
    uint32_t  handle[10]={0,TIMER1,TIMER2,TIMER4,\
                            TIMER5,TIMER6,TIMER9,\
                            TIMER10,TIMER11,TIMER12
                         };
    uint32_t source[10]={0,TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,\
                           TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP,\
                           TIMER_INT_UP,TIMER_INT_UP,TIMER_INT_UP
                        };
   
   if(Mstep==NULL)
        return -1;                           
   if(stopnum==0||stopnum>9)
        return -1;
   
   timer_autoreload_value_config(handle[stopnum],0);  
   timer_interrupt_disable(handle[stopnum],source[stopnum]);
   timer_interrupt_flag_clear(handle[stopnum],source[stopnum]);
  
   Mstep->run_state=0; 
   Mstep->rest=0;
   Mstep->step_count=0;        
   Mstep->accel_count=0;
   Mstep->decel_start=0;
   Mstep->decel_val=0;
   Mstep->last_accel_delay=0;
   Mstep->min_delay=0;
   Mstep->new_step_delay=0;
   Mstep->step_delay=0;
   return 0;
}
/*
加减速度计数换算
num:电机编号
adspeed:加减速
mode:1-加速度  0-减速度
*/
static uint32_t HzCountConversion(uint8_t mode,uint8_t num,int32_t adspeed)
{
   unsigned int tval=0;
// int tval2=0;   
    MotorStep* Mstep=NULL;
   
    Mstep=GetMorotParameterPointer(num);

    if(Mstep==NULL)
        return 0;
    if(mode==1)
    {
        Mstep->step_delay+=adspeed;
        tval=(((unsigned int)((1000*1000.0)/Mstep->step_delay))>>1);
//        Mstep->rest=(((unsigned int)(1000*1000.0))%Mstep->step_delay)/2;
//        Mstep->step_delay+=Mstep->rest;
//        tval2=(tval/(float)TIM1COUNTCYCLE)+1;  
    }
    else 
    {
        Mstep->step_delay-=adspeed;
        tval=((unsigned int)((1000*1000.0)/Mstep->step_delay))>>1;
//        Mstep->rest=(((unsigned int)(1000*1000.0))%Mstep->step_delay)/2;
//        Mstep->step_delay+=Mstep->rest;        
//        tval2=(tval/(float)TIM1COUNTCYCLE)-1;         
    }
    return tval;
}
/**
  * @brief  速度决策
  *	@note 	在中断中使用，每进一次中断，决策一次
  * @retval 无
  */
void speed_decision(uint8_t Mnum,MotorStep *srd)
{
    srd->i++;
    //一个完整脉冲    
    if(srd->i==2)         
    {
        srd->i=0;    
        srd->step_count++;            
        switch(srd->run_state) 
        {
          /*步进电机加速状态*/
          case ACCEL: 
            srd->Encoder+=srd->dir==0?-1:1;
            srd->new_step_delay=HzCountConversion(1,Mnum,srd->accel_count);
                
            //检查是否到达期望的最大速度
            if(srd->new_step_delay<= srd->min_delay)
            {
                srd->run_state = RUN;
                srd->new_step_delay=srd->min_delay;
            }
            //检查是够应该开始匀速
            else if(srd->step_count==STEPCOUNT&&srd->mode==MODE_P){    
                srd->run_state = RUN;              
            }
             //检查是否需要开始减速
            if(srd->step_count>=srd->decel_start&&srd->mode==MODE_P) 
                srd->run_state = DECEL;            
            break;
           /*步进电机最大速度运行状态*/
          case RUN:
            srd->Encoder+=srd->dir==0?-1:1;              
             //检查是否需要开始减速
            if(srd->step_count>=srd->decel_start&&srd->mode==MODE_P) 
                srd->run_state = DECEL;
            break;
           /*步进电机减速状态*/
          case DECEL:
            srd->Encoder+=srd->dir==0?-1:1;              
            if(srd->new_step_delay <=1000)
                srd->new_step_delay=HzCountConversion(0,Mnum,srd->accel_count);
            //检查是否为最后一步
            if(srd->TargetStepCont<=srd->step_count) 
            {              
               Motor_Stop_Set(srd,Mnum); 
               //两路MPS6602与1路DRV8462配置好后停机自动切换到锁定电流 
               if(Mnum<=6)
                   appNineMotorLockCurrentSet(Mnum,srd->LockCurrent);  
               log_info("%d \n",srd->Encoder);
               srd->run_state = STOP;
            }
            break;
        }
	}
}


/*
多条位置指令重叠运动处理(阻塞)
tye：1:终止当前运动减速停机,阻塞时间STEPCOUNT个脉冲周期
        (保障最后一条位置指令)
    !1:等待当前运动结束,阻塞时间剩余N个未走完脉冲周期
        (重叠位置指令都能走完位置）    
mtn:电机编号

*/
static int appScissorsClipOverlappingMotion(MotorStep* Mstep, uint8_t mtn,uint8_t tye)
{
    uint16_t surpluspos=0;
   
    if(Mstep==NULL)
        return -1;
    if(mtn==0||mtn>6)
        return -1;          
    if(tye==1)
    {
       surpluspos=Mstep->TargetStepCont-Mstep->step_count;
       Mstep->run_state=DECEL;   
       if(surpluspos>STEPCOUNT)
         Mstep->step_count=Mstep->TargetStepCont-STEPCOUNT;
       else
       {
         Mstep->step_delay=1000;
         Mstep->step_count=Mstep->TargetStepCont;
       }
    }
    while(Mstep->run_state!=STOP){;}    
    return 1;
}

/*! \brief 以给定的步数移动步进电机
 *  \param mode   1:走相对 0:走绝对 
 *  \param step   移动的步数(正数为顺时针，负数为逆时针).
 *  \param speed  Hz
 */
int appMotorStepModeMove_T(unsigned char stepnum,unsigned char mode,int step,unsigned int speed)
{  
    uint8_t dir=0;  
    int32_t AbsoluteVal=0;
    int32_t Encoder=0; 
    int32_t AbsSpeed=(speed-1000); 
    MotorStep* Mstep=NULL;
    float tval=0.0,tval2=0.0;      

    if(stepnum==0||stepnum>9)
        return -1;        
    Mstep=GetMorotParameterPointer(stepnum);
    if(Mstep==NULL)
        return -1; 
    //加减速步数
    if(stepnum>6&&speed>4999){
       STEPCOUNT=800;
    } 
    else{
      STEPCOUNT=30;  
    }
    //极限速度限制
    if(speed>10*10*100)
       speed=10*1000; 
    else if(speed<10)  
       speed=10;
    
    //多条位置指令重叠运动处理
    appScissorsClipOverlappingMotion(Mstep,stepnum,0);
    
    AbsoluteVal=step<0?-(step):step;
    AbsSpeed=AbsSpeed>0?AbsSpeed:-AbsSpeed;
    AbsSpeed=AbsSpeed/STEPCOUNT;
    if(AbsSpeed>300){
        AbsSpeed=300;
    }
    AbsSpeed++;
    
    tval=(1/(float)speed)/2;
    tval2=tval/(float)TIM1COUNTCYCLE;
          
    if(mode!=0)
    {
        dir=step<0?Mstep->FwDir:!Mstep->FwDir;    
        Mstep->dir=dir^Mstep->FwDir; 
    }   
    else
    {
        Encoder=step-(Mstep->Encoder); 
        AbsoluteVal=Encoder<0?-Encoder:Encoder;
        dir=Mstep->Encoder>step?Mstep->FwDir:!Mstep->FwDir;
        Mstep->dir=dir^Mstep->FwDir; 
    }
    if(AbsoluteVal==0)
      return 0;
    
    Mstep->mode=MODE_P;
    Mstep->run_state=ACCEL; 
       
    Mstep->step_count=0;
    //启动速度hz
    Mstep->step_delay=1000; 
    //周期计数值
    Mstep->new_step_delay=Mstep->step_delay/2;
    //目标速度周期值HZ
    Mstep->min_delay= ((unsigned int)tval2)-1;
    if(speed<=1000)
    {
        Mstep->new_step_delay=Mstep->min_delay;
        Mstep->run_state=RUN;
    }
    //目标位置      
    Mstep->TargetStepCont=AbsoluteVal;   
    Mstep->accel_count=AbsSpeed;
    Mstep->decel_val=  AbsSpeed; 
    Mstep->decel_start=(AbsoluteVal-STEPCOUNT)+1;  
    if(AbsoluteVal<STEPCOUNT)
         Mstep->run_state=DECEL; 
    appNineMotorDirSet(stepnum,dir); 
    //两路MPS6602与1路DRV8462配置好后自动切换到运行电流
    if(stepnum<=6)
      appNineMotorRunCurrentSet(stepnum,Mstep->RunCurrent);
    Motor_Star_Set(Mstep,stepnum);       
    return 0;
}
/*! \brief 以给定的速度移动步进电机
*   \param  stepnum:电机编号 1-9
*   \param speed(Hz):>0正转，<0反转  ==0减速停止
*/
int appMotorSpeedModeMove_T(unsigned char stepnum,int speed)
{  
    uint8_t dir=0;  
    uint8_t lastDir=0;
    static uint8_t flag[9]={0};
    int32_t AbsSpeed; 
    MotorStep* Mstep=NULL;
    float tval=0.0,tval2=0.0;      

    if(stepnum==0||stepnum>9)
        return -1;        
    Mstep=GetMorotParameterPointer(stepnum);
    if(Mstep==NULL)
        return -1; 
    //加减速步数
    if(stepnum>6&&abs(speed)>4999){
       STEPCOUNT=800;
    }
    else{
        STEPCOUNT=30;
    }        
    //减速停机
    if(speed==0)
    {
        if(Mstep->run_state==STOP)
           return 0; 
        Mstep->step_count=0;
        Mstep->TargetStepCont=STEPCOUNT;
        Mstep->run_state=DECEL; 
        return 0;
    }
    AbsSpeed=speed>0?speed:-speed;
     //方向判断
    lastDir=Mstep->dir;    
    dir=speed<0?Mstep->FwDir:!Mstep->FwDir;    
    Mstep->dir=dir^Mstep->FwDir;     
    //换向处理
    if(lastDir!=Mstep->dir&&flag[stepnum])
    {
        Mstep->step_count=0;
        Mstep->TargetStepCont=STEPCOUNT;
        Mstep->run_state=DECEL;
        while(Mstep->run_state!=STOP)
        {//delay_1ms(1);
        }            
    }   
    flag[stepnum]=1;    
    //最大速度限制    
    if(AbsSpeed>10*10*100)
       AbsSpeed=10*1000;
    //最小速度限制    
    else if(AbsSpeed<10)  
       AbsSpeed=10;    
    //加减速计算    
    tval=(1/(float)AbsSpeed)/2;
    tval2=tval/(float)TIM1COUNTCYCLE;

    if(AbsSpeed<=1000)
    {
        Mstep->new_step_delay=Mstep->min_delay;
        Mstep->run_state=RUN;
    }       
    AbsSpeed=AbsSpeed/STEPCOUNT;
    if(AbsSpeed>300)
    {
        AbsSpeed=300;
    }
    AbsSpeed++;    
    
    Mstep->mode=MODE_S;
    Mstep->run_state=ACCEL; 
       
    Mstep->step_count=0;
    //启动速度hz
    Mstep->step_delay=1000; 
    //周期计数值
    Mstep->new_step_delay=Mstep->step_delay/2;
    //目标速度周期值HZ
    Mstep->min_delay= ((unsigned int)tval2)-1;

    Mstep->accel_count=AbsSpeed;
    Mstep->decel_val=  AbsSpeed;  
    appNineMotorDirSet(stepnum,dir);  
    //两路MPS6602与1路DRV8462配置好后自动切换到运行电流    
    if(stepnum<=6)
      appNineMotorRunCurrentSet(stepnum,Mstep->RunCurrent);    
    Motor_Star_Set(Mstep,stepnum);       
    return 0;
}




