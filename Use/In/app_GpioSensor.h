#ifndef _APPCPIOMOTORSENSOR_H
#define _APPCPIOMOTORSENSOR_H


void appGpioSetsInit(void);

void app_System_Led(unsigned short);

unsigned char appGetDipSwitchNum(void);

void appDrv88033_RST(void);

unsigned char appGetDrv88033FaultStatus(void);

int  appRead5wayOutputPinStatus(unsigned char);

int  app5wayOutputEnWrite(unsigned char,unsigned char);

int  appGetSensorStatus(unsigned char);




#endif



