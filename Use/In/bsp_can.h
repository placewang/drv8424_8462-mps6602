#ifndef CAN_H
#define CAN_H

#define CAN_BAUDRATE    1000               //波特率
#define CANREVIDBASS_1  0x378              //接受帧起始ID
//#define CANREVIDBASS_2  0x370            //接受帧起始ID
//#define CANREVIDBASS_3  0x330            //接受帧起始ID
#define CANSENDID       0x778              //发送帧ID


extern void (*CanDataEnQueueCallback)(void *dat);


void bsp_can0_init(void);
unsigned char bsp_Can0_Message(unsigned char *,unsigned char ,unsigned short);    


#endif



