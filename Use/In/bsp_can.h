#ifndef CAN_H
#define CAN_H

#define CAN_BAUDRATE    1000               //������
#define CANREVIDBASS_1  0x378              //����֡��ʼID
//#define CANREVIDBASS_2  0x370            //����֡��ʼID
//#define CANREVIDBASS_3  0x330            //����֡��ʼID
#define CANSENDID       0x778              //����֡ID


extern void (*CanDataEnQueueCallback)(void *dat);


void bsp_can0_init(void);
unsigned char bsp_Can0_Message(unsigned char *,unsigned char ,unsigned short);    


#endif



