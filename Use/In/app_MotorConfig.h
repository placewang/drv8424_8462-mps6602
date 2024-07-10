#ifndef _APPMOTORCONFIG_H
#define _APPMOTORCONFIG_H

//#include "app_Drv8424.h"
//#include "app_mps6602.h"
//#include "app_drv8462.h"

void app_NineStepperMotorsDefaultParameter(void);
void appDrv8424Init(void);
void appMps6602Init(void);
void appDrv8462Init(void);

int appNineMotorDirSet(unsigned char num,unsigned char dir);
int appNineMotorEnbleSet(unsigned char num,unsigned char Enb);
int appNineMotorGetFaultStatus(unsigned char num);
int appNineMotorRunCurrentSet(unsigned char num,unsigned short current);
int appNineMotorLockCurrentSet(unsigned char num,unsigned short current);
int appNineMotorMicrostepSet(unsigned char num,unsigned char microstep);

#endif







