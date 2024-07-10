#ifndef _APPDRV8424_H
#define _APPDRV8424_H

int appGetScissorsClipGetMotorFault(unsigned char num);
int appScissorsClipMotorMicrostepSet(unsigned char,unsigned char);
int appScissorsClipMotorDirSet(unsigned char,unsigned char dir);
int appScissorsClipMotorEnbleSet(unsigned char,unsigned char Enb);
int appScissorsClipMotorCurrentSet(unsigned char,unsigned short current);


#endif








