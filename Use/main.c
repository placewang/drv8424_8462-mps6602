#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_uart.h"
#include "app_AdcPower.h"
#include "app_Motorstep.h"
#include "app_CanMessage.h"
#include "app_GpioSensor.h"


//ElemType dat;
uint16_t dd;
int main(void)
{
    systick_config();
    bsp_uart0_int();
    appGpioSetsInit();
    appCanMessageInit();
    appMotorStepInit();
//    appNineMotorRunCurrentSet(7,0x20);
//    appNineMotorLockCurrentSet(7,0x99);
//    appNineMotorRunCurrentSet(2,1470);
//    appNineMotorLockCurrentSet(2,200);
//    appNineMotorRunCurrentSet(3,1470);
//    appNineMotorLockCurrentSet(3,200);
//    appNineMotorRunCurrentSet(4,1470);
//    appNineMotorLockCurrentSet(4,200);
//    appNineMotorRunCurrentSet(5,1470);
//    appNineMotorLockCurrentSet(5,200);    
//    appNineMotorRunCurrentSet(6,1470);
//    appNineMotorLockCurrentSet(6,200);    

//appNineMotorEnbleSet(0,0);
//    appMotorStepModeMove_T(7,0,800*1,5000);
//    appMotorStepModeMove_T(9,0,800*10,1000);
//    appMotorSpeedModeMove_T(6,10000);
//    appMotorSpeedModeMove_T(2,3000);
//    appMotorSpeedModeMove_T(3,3000);
//    appMotorSpeedModeMove_T(4,3000);
//    appMotorSpeedModeMove_T(5,3000);
//    appMotorSpeedModeMove_T(6,3000); 

//    appMotorSpeedModeMove_T(2,-5000);
//    appMotorSpeedModeMove_T(3,-1000);
//    appMotorSpeedModeMove_T(4,-6000);
//    appMotorSpeedModeMove_T(5,-9000);
//    appMotorSpeedModeMove_T(6,-10000);  
//    delay_1ms(1*1000); 
//    appMotorSpeedModeMove_T(6,-10000);
//    appMotorSpeedModeMove_T(2,0);
//    appMotorSpeedModeMove_T(3,0);
//    appMotorSpeedModeMove_T(4,0);
//    appMotorSpeedModeMove_T(5,0);
//    appMotorSpeedModeMove_T(6,0);     
//    appMotorSpeedModeMove_T(8,9000);

    while(1)
    {
        app_System_Led(500);        
//        log_debug("SensorStatus:0x%X \n",appGetSensorStatus(0));  
//        log_debug("5wayOutStatus:0x%X \n",appRead5wayOutputPinStatus(0));
//        log_debug("DipSwitchNum:0x%X \n",appGetDipSwitchNum());       
//        log_debug("faultstatus_3:0x%X \n",appNineMotorGetFaultStatus(3)); 
//        log_debug("faultstatus_4:0x%X \n",appNineMotorGetFaultStatus(4)); 
//        log_debug("faultstatus_5:0x%X \n",appNineMotorGetFaultStatus(5));  
//        log_debug("faultstatus_6:0x%X \n",appNineMotorGetFaultStatus(6));          
//        delay_1ms(1000*1); 
    

    }    
    return 0;
}











