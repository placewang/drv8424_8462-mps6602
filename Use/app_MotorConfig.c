#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_spi.h"
#include "bsp_uart.h"
#include "bsp_gpio.h"
#include "bsp_time.h"
#include "app_mps6602.h"
#include "app_drv8462.h"
#include "app_drv8424.h"
#include "app_Motorstep.h"

    
/*
9路电机上电默认参数赋值
    -运行电流
    -锁定电流
    -电机运动默认正方向
*/
void app_NineStepperMotorsDefaultParameter(void)
{
    uint8_t  i=0;
    uint16_t Rcur=2000,Lcur=800;
    MotorStep* Mstep=NULL;
    
    uint8_t  dir[9]={0,0,0,0,0,0,
                     0,            
                     0,0,
                    };
    uint16_t R_Cur[9]={Rcur,Rcur,Rcur,Rcur,Rcur,Rcur,
                       0x9D, 
                       Current4000mA,Current4000mA
                      };
    
    uint16_t L_Cur[9]={Lcur,Lcur,Lcur,Lcur,Lcur,Lcur,
                       HoldCurr_40,
                       Current1500mA,Current1500mA
                       };    
        
    for(i=0;i<9;i++)
    {
        Mstep=GetMorotParameterPointer(i+1);
        if(Mstep==NULL){
           return;      
        }            
        Mstep->FwDir=dir[i];
        Mstep->RunCurrent=R_Cur[i];
        Mstep->LockCurrent=L_Cur[i];           
    }
}


/*
Drv8424初始化
    -电流控制端口(PWM)
    -默认配置
*/
void appDrv8424Init(void)
{
    uint8_t i=0;
    MotorStep* Mstep=NULL;
    
    bsp_Timer3_PWM_Config();
    bsp_Timer8_PWM_Config();

    for(i=0;i<6;i++)
    {
        Mstep=GetMorotParameterPointer(i+1);
        if(Mstep==NULL){
           return;      
        }  
        appScissorsClipMotorCurrentSet(i+1,Mstep->LockCurrent);                    
    }       
    appScissorsClipMotorDirSet(0,0);
    appScissorsClipMotorEnbleSet(0,1);
    appScissorsClipMotorMicrostepSet(0,4);     
}
/*
MPS6602初始化
    -spi_init
    -电机配置
    -默认使能
    -默认方向
*/
void appMps6602Init(void)
{
    uint8_t i=0;
    MotorStep* Mstep=NULL;
    
    bsp_spi0_Init();
    //电机配置4细分，开启自动保持 运行电流，锁定电流
    for(i=1;i<=2;i++)
    {
        Mstep=GetMorotParameterPointer(i+7);
        if(Mstep==NULL){
           return;      
        }
        appMps6602WriteRegisterVal(i,SPI0_ISET,(Mstep->LockCurrent<<6)|Mstep->RunCurrent);
    }             
    appMps6602WriteRegisterVal(1,SPI0_CTRL,(HoldTime31_3ms<<9)|(0x04<<6)|(step_4<<3)|0x00);
    appMps6602WriteRegisterVal(2,SPI0_CTRL,(HoldTime31_3ms<<9)|(0x04<<6)|(step_4<<3)|0x00);
     /*默认方向与使能*/
    appPullMotorDirSet(0,0);
    appPullMotorEnbleSet(0,1);
}
/*
drv8462初始化
    -spi_init
    -电机配置
    -默认使能
    -默认方向
*/
void appDrv8462Init(void)
{
    MotorStep* Mstep=NULL;
    
    Mstep=GetMorotParameterPointer(7);
    if(Mstep==NULL){
       return;      
    }    
    /*spi_init*/
    bsp_spi1_Init();
    /*motor config*/
    appDrv8462WriteRegisterVal(SPI1_CTRL1, (uint8_t)(CTRL1|1<<7));            //所有输出均启用
    appDrv8462WriteRegisterVal(SPI1_CTRL2, (uint8_t)(MicroStep4));           //1/4 步进
    appDrv8462WriteRegisterVal(SPI1_CTRL9, (uint8_t)(CTRL9|1));              //启用自动微步进(1/256)
    appDrv8462WriteRegisterVal(SPI1_CTRL10,(uint8_t)Mstep->LockCurrent);     //保持电流
    appDrv8462WriteRegisterVal(SPI1_CTRL11,(uint8_t)Mstep->RunCurrent);      //运行电流
    appDrv8462WriteRegisterVal(SPI1_CTRL12,(uint8_t)(CTRL12|1<<7));          //启用静止省电模式 
    appDrv8462WriteRegisterVal(SPI1_CTRL13,(uint8_t)(CTRL13|1<<1));          //使用内部3.3V基准进行电流调节
    appDrv8462WriteRegisterVal(SPI1_SS_CTRL1,(uint8_t)(SS_CTRL1|1));         //启用静音步进衰减模式
    appDrv8462WriteRegisterVal(SPI1_SS_CTRL2,(uint8_t)(0X20));               //静音步进PI控制器的比例增益
    /*默认方向与使能*/
    appLiftingMotorEnbleSet(1);
    appLiftingMotorDirSet(0);
}

/*
9路电机方向设置
num: 1-9 
     0-全部 
dir: 0/!0 
*/
int appNineMotorDirSet(unsigned char num,unsigned char dir)
{
    if(num>9){
        return -1;
    }
    if(num<=6){
       appScissorsClipMotorDirSet(num,dir); 
    }
    if(num==7||num==0){
        appLiftingMotorDirSet(dir);
    }
    if((num>7&&num<=9)||num==0){
        appPullMotorDirSet(num==0?0:(num-7),dir);
    }
    
    return 0;   
}
/*
9路电机使能/失能设置
num: 1-9
     0-全部 
En: 0/!0 
*/
int appNineMotorEnbleSet(unsigned char num,unsigned char Enb)
{
    if(num>9){
        return -1;
    }
    if(num<=6){
        appScissorsClipMotorEnbleSet(num,Enb); 
    }
    if(num==7||num==0){
        appLiftingMotorEnbleSet(Enb);
    }
    if((num>7&&num<=9)||num==0){
        appPullMotorEnbleSet(num==0?0:(num-7),Enb);
    }    
    return 0;
}
/*
电机故障状态获取(低电平有效)
num: 1-9    bit0
     0-全部 bit0--bit8
*/
int appNineMotorGetFaultStatus(unsigned char num)
{
    uint8_t  sta_1=0,sta_2=0,sta_3=0,sta_4=0;
    uint32_t status=0;    
    if(num>9){
        return -1;
    }
    if(num<=6){
       sta_1=appGetScissorsClipGetMotorFault(num); 
       status=sta_1; 
    }
    if(num==7||num==0){
       sta_2=appGetLiftingMotorFaultPinSta();
       status=sta_2; 
    }
    if(num==8||num==0){
       sta_3=appGetPullMotorFaultPinSta(1);
       status=sta_3; 
    }           
    if(num==9||num==0){
       sta_4=appGetPullMotorFaultPinSta(2);
       status=sta_4;        
    }
    if(num==0){
        status=(uint32_t)((sta_4<<8)|(sta_3<<7)|(sta_2<<6)|sta_1);
    }
    return status;
}

/*
9路电机电流设设置并记录(因三款电机IC电流调节方式差别大故不支持群操作)
num: 1-9 
current:电流值
*/
int appNineMotorRunCurrentSet(unsigned char num,unsigned short current)
{
    MotorStep* Mstep=NULL;
    
    if(num==0||num>9){
        return -1;
    }
    Mstep=GetMorotParameterPointer(num);
    if(Mstep==NULL){
       return -1;      
    }
    Mstep->RunCurrent=current;   

    if(num<=6)
    {
        appScissorsClipMotorCurrentSet(num,current);
    }        
    else if(num==7){
        appDrv8462WriteRegisterVal(SPI1_CTRL11,(uint8_t)current);
    }
    else if(num==8){
        appMps6602WriteRegisterVal(1,SPI0_ISET,(Mstep->LockCurrent<<6)|Mstep->RunCurrent); 
    }
    else if(num==9){
        appMps6602WriteRegisterVal(2,SPI0_ISET,(Mstep->LockCurrent<<6)|Mstep->RunCurrent);  
    }   
    return 0;  
}


/*
9路电机锁定电流设设置并记录(因三款电机IC电流调节方式差别大故不支持群操作)
num: 1-9 
current:电流值
*/
int appNineMotorLockCurrentSet(unsigned char num,unsigned short current)
{
    MotorStep* Mstep=NULL;
    
    if(num==0||num>9){
        return -1;
    }
    Mstep=GetMorotParameterPointer(num);
    if(Mstep==NULL){
       return -1;      
    }
    Mstep->LockCurrent=current;

    if(num<=6){
        appScissorsClipMotorCurrentSet(num,current);
    }  
    else if(num==7){
        appDrv8462WriteRegisterVal(SPI1_CTRL10,(uint8_t)current);    //保持电流
    }    
    else if(num==8){
        appMps6602WriteRegisterVal(1,SPI0_ISET,(Mstep->LockCurrent<<6)|Mstep->RunCurrent); 
    }
    else if(num==9){
        appMps6602WriteRegisterVal(2,SPI0_ISET,(Mstep->LockCurrent<<6)|Mstep->RunCurrent); 
    } 
   return 0;
}

/*
9路电机细分设置(上电默认配置4细分)
(因三款电机IC细分调节方式差别大紧支持4种情况,特殊使用对应IC接口)
num: 1--左剪刀,右剪刀
     2-右夹1,右夹2,左夹1,左夹2
     7-升降电机
     8/9-拉线电机   
     0-全部 
microstep:  0-全步  
            2-1/2步 
            4-1/4步  
            8-1/8步
*/
int appNineMotorMicrostepSet(unsigned char num,unsigned char microstep)
{

    uint8_t microDrv8424=0,microDrv8462=0,microMps6602=0;
    
     switch(microstep)
    {
        case 0:
            microDrv8424=microstep;
            microDrv8462=MicroStep1;
            microMps6602=step_1;
            break;
        case 2:
            microDrv8424=microstep;
            microDrv8462=MicroStep2;
            microMps6602=step_2;  
            break;
        case 4:
            microDrv8424=microstep;
            microDrv8462=MicroStep4;
            microMps6602=step_4;    
            break;  
        case 8:
            microDrv8424=microstep;
            microDrv8462=MicroStep8;
            microMps6602=step_8;     
            break;   
    }
    if(num<=2){
        appScissorsClipMotorMicrostepSet(num,microDrv8424);
    }
    if(num==7||num==0){
        appDrv8462WriteRegisterVal(SPI1_CTRL2,(uint8_t)(microDrv8462)); 
    }
    if(num==8||num==0){
        appMps6602WriteRegisterVal(1,SPI0_CTRL,(HoldTime31_3ms<<9)|(0x04<<6)|(microMps6602<<3)|0x00);
    }           
    if(num==9||num==0){
        appMps6602WriteRegisterVal(2,SPI0_CTRL,(HoldTime31_3ms<<9)|(0x04<<6)|(microMps6602<<3)|0x00);       
    }      
    return 0;
}









