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

uint16_t STEPCOUNT=30;        //�Ӽ��ٲ���


/*�жϴ�����_Mt1*/
void TIM1_Interrupt_Mt1(void)
{
    gpio_bit_toggle(MT_STEP1_PORT,MT_STEP1_PIN);
    speed_decision(Motor1,&Mt1Step);
    timer_autoreload_value_config(TIMER1,0xffffffff&(Mt1Step.new_step_delay));    
    return;
}
/*�жϴ�����_Mt2*/
void TIM2_Interrupt_Mt2(void)
{
    gpio_bit_toggle(MT_STEP2_PORT,MT_STEP2_PIN);
    speed_decision(Motor2,&Mt2Step);
    timer_autoreload_value_config(TIMER2,0xffff&(Mt2Step.new_step_delay));    
    return;
}
/*�жϴ�����_Mt3*/
void TIM4_Interrupt_Mt3(void)
{
    gpio_bit_toggle(MT_STEP3_PORT,MT_STEP3_PIN);
    speed_decision(Motor3,&Mt3Step);
    timer_autoreload_value_config(TIMER4,0xffffffff&(Mt3Step.new_step_delay));    
    return;
}
/*�жϴ�����_Mt4*/
void TIM5_Interrupt_Mt4(void)
{
    gpio_bit_toggle(MT_STEP4_PORT,MT_STEP4_PIN);
    speed_decision(Motor4,&Mt4Step);
    timer_autoreload_value_config(TIMER5,0xffff&(Mt4Step.new_step_delay));    
    return;
}
/*�жϴ�����_Mt5*/
void TIM6_Interrupt_Mt5(void)
{
    gpio_bit_toggle(MT_STEP5_PORT,MT_STEP5_PIN);
    speed_decision(Motor5,&Mt5Step);
    timer_autoreload_value_config(TIMER6,0xffff&(Mt5Step.new_step_delay));    
    return;
}

/*�жϴ�����_Mt6*/
void TIM9_Interrupt_Mt6(void)
{
    gpio_bit_toggle(MT_STEP6_PORT,MT_STEP6_PIN);
    speed_decision(Motor6,&Mt6Step);
    timer_autoreload_value_config(TIMER9,0xffff&(Mt6Step.new_step_delay));    
    return;
}
/*�жϴ�����_Mt7*/
void TIM10_Interrupt_Mt7(void)
{
    gpio_bit_toggle(MT_STEP7_PORT,MT_STEP7_PIN);
    speed_decision(Motor7,&Mt7Step);
    timer_autoreload_value_config(TIMER10,0xffff&(Mt7Step.new_step_delay));    
    return;
}
/*�жϴ�����_Mt8*/
void TIM11_Interrupt_Mt8(void)
{
    gpio_bit_toggle(MT_STEP8_PORT,MT_STEP8_PIN);
    speed_decision(Motor8,&Mt8Step);
    timer_autoreload_value_config(TIMER11,0xffff&(Mt8Step.new_step_delay));    
    return;
}
/*�жϴ�����_Mt9*/
void TIM12_Interrupt_Mt9(void)
{
    gpio_bit_toggle(MT_STEP9_PORT,MT_STEP9_PIN);
    speed_decision(Motor9,&Mt9Step);
    timer_autoreload_value_config(TIMER12,0xffff&(Mt9Step.new_step_delay));    
    return;
}
/*
����������Ƴ�ʼ��
    -�жϴ���ص�������ֵ
    -���嶨ʱ����ʼ��
    -9·����ϵ�Ĭ�ϲ���
    -Drv8424��ʼ��
    -Drv8462��ʼ��
    -MPS6602��ʼ��
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
���ݵ����Ÿ�ֵ�Ӽ��ٶȾ��ָ��
num:������
return �����ָ��
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
�������
Mstep;   ����������
startnum:���(1-9)
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
���ֹͣ
Mstep;   ����������
startnum:���(1-9)
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
�Ӽ��ٶȼ�������
num:������
adspeed:�Ӽ���
mode:1-���ٶ�  0-���ٶ�
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
  * @brief  �ٶȾ���
  *	@note 	���ж���ʹ�ã�ÿ��һ���жϣ�����һ��
  * @retval ��
  */
void speed_decision(uint8_t Mnum,MotorStep *srd)
{
    srd->i++;
    //һ����������    
    if(srd->i==2)         
    {
        srd->i=0;    
        srd->step_count++;            
        switch(srd->run_state) 
        {
          /*�����������״̬*/
          case ACCEL: 
            srd->Encoder+=srd->dir==0?-1:1;
            srd->new_step_delay=HzCountConversion(1,Mnum,srd->accel_count);
                
            //����Ƿ񵽴�����������ٶ�
            if(srd->new_step_delay<= srd->min_delay)
            {
                srd->run_state = RUN;
                srd->new_step_delay=srd->min_delay;
            }
            //����ǹ�Ӧ�ÿ�ʼ����
            else if(srd->step_count==STEPCOUNT&&srd->mode==MODE_P){    
                srd->run_state = RUN;              
            }
             //����Ƿ���Ҫ��ʼ����
            if(srd->step_count>=srd->decel_start&&srd->mode==MODE_P) 
                srd->run_state = DECEL;            
            break;
           /*�����������ٶ�����״̬*/
          case RUN:
            srd->Encoder+=srd->dir==0?-1:1;              
             //����Ƿ���Ҫ��ʼ����
            if(srd->step_count>=srd->decel_start&&srd->mode==MODE_P) 
                srd->run_state = DECEL;
            break;
           /*�����������״̬*/
          case DECEL:
            srd->Encoder+=srd->dir==0?-1:1;              
            if(srd->new_step_delay <=1000)
                srd->new_step_delay=HzCountConversion(0,Mnum,srd->accel_count);
            //����Ƿ�Ϊ���һ��
            if(srd->TargetStepCont<=srd->step_count) 
            {              
               Motor_Stop_Set(srd,Mnum); 
               //��·MPS6602��1·DRV8462���úú�ͣ���Զ��л����������� 
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
����λ��ָ���ص��˶�����(����)
tye��1:��ֹ��ǰ�˶�����ͣ��,����ʱ��STEPCOUNT����������
        (�������һ��λ��ָ��)
    !1:�ȴ���ǰ�˶�����,����ʱ��ʣ��N��δ������������
        (�ص�λ��ָ�������λ�ã�    
mtn:������

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

/*! \brief �Ը����Ĳ����ƶ��������
 *  \param mode   1:����� 0:�߾��� 
 *  \param step   �ƶ��Ĳ���(����Ϊ˳ʱ�룬����Ϊ��ʱ��).
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
    //�Ӽ��ٲ���
    if(stepnum>6&&speed>4999){
       STEPCOUNT=800;
    } 
    else{
      STEPCOUNT=30;  
    }
    //�����ٶ�����
    if(speed>10*10*100)
       speed=10*1000; 
    else if(speed<10)  
       speed=10;
    
    //����λ��ָ���ص��˶�����
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
    //�����ٶ�hz
    Mstep->step_delay=1000; 
    //���ڼ���ֵ
    Mstep->new_step_delay=Mstep->step_delay/2;
    //Ŀ���ٶ�����ֵHZ
    Mstep->min_delay= ((unsigned int)tval2)-1;
    if(speed<=1000)
    {
        Mstep->new_step_delay=Mstep->min_delay;
        Mstep->run_state=RUN;
    }
    //Ŀ��λ��      
    Mstep->TargetStepCont=AbsoluteVal;   
    Mstep->accel_count=AbsSpeed;
    Mstep->decel_val=  AbsSpeed; 
    Mstep->decel_start=(AbsoluteVal-STEPCOUNT)+1;  
    if(AbsoluteVal<STEPCOUNT)
         Mstep->run_state=DECEL; 
    appNineMotorDirSet(stepnum,dir); 
    //��·MPS6602��1·DRV8462���úú��Զ��л������е���
    if(stepnum<=6)
      appNineMotorRunCurrentSet(stepnum,Mstep->RunCurrent);
    Motor_Star_Set(Mstep,stepnum);       
    return 0;
}
/*! \brief �Ը������ٶ��ƶ��������
*   \param  stepnum:������ 1-9
*   \param speed(Hz):>0��ת��<0��ת  ==0����ֹͣ
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
    //�Ӽ��ٲ���
    if(stepnum>6&&abs(speed)>4999){
       STEPCOUNT=800;
    }
    else{
        STEPCOUNT=30;
    }        
    //����ͣ��
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
     //�����ж�
    lastDir=Mstep->dir;    
    dir=speed<0?Mstep->FwDir:!Mstep->FwDir;    
    Mstep->dir=dir^Mstep->FwDir;     
    //������
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
    //����ٶ�����    
    if(AbsSpeed>10*10*100)
       AbsSpeed=10*1000;
    //��С�ٶ�����    
    else if(AbsSpeed<10)  
       AbsSpeed=10;    
    //�Ӽ��ټ���    
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
    //�����ٶ�hz
    Mstep->step_delay=1000; 
    //���ڼ���ֵ
    Mstep->new_step_delay=Mstep->step_delay/2;
    //Ŀ���ٶ�����ֵHZ
    Mstep->min_delay= ((unsigned int)tval2)-1;

    Mstep->accel_count=AbsSpeed;
    Mstep->decel_val=  AbsSpeed;  
    appNineMotorDirSet(stepnum,dir);  
    //��·MPS6602��1·DRV8462���úú��Զ��л������е���    
    if(stepnum<=6)
      appNineMotorRunCurrentSet(stepnum,Mstep->RunCurrent);    
    Motor_Star_Set(Mstep,stepnum);       
    return 0;
}




