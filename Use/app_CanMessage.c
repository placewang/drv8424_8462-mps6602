#include "bsp_can.h"
#include "app_CanDataQueue.h"

/*
����������ӻص�����
*/
static void appCanDataInQueue(void* dat)
{
    if(dat==NULL)
        return;
    appCanDataEnQueue(&CanRevQueue,(ElemType*)dat); 
}
/*
CAN��ϢӦ�ó�ʼ��
    -CanӲ������
    -������ӻص�����ָ���ַ��ֵ
    -�������ݶ�������
*/
void appCanMessageInit(void)
{
    bsp_can0_init();
    CanDataEnQueueCallback=appCanDataInQueue;
    appCanQueueInit(&CanRevQueue,CanDataBuff,CANDATALEN);
}

/*
Can������Ϣ
data:��������
len: ���ͳ���
id: ����CANID
*/

int appCanDataSend(unsigned char *data,unsigned char len,unsigned short id)
{
    uint8_t  Can0transmit_mailbox = 0;
    uint16_t Can0sendtimeout=0;
    
   if(data==NULL||len>8||len==0)
   {
     return -1;
   }
   Can0transmit_mailbox=bsp_Can0_Message(data,len,id);
   Can0sendtimeout=0;
   while(can_transmit_states(CAN0,Can0transmit_mailbox)!=CAN_TRANSMIT_OK&&Can0sendtimeout<=0xfff0)
   {
        Can0sendtimeout++;
   }   
   return 0;
}









