#include "bsp_can.h"
#include "app_CanDataQueue.h"

/*
接收数据入队回调处理
*/
static void appCanDataInQueue(void* dat)
{
    if(dat==NULL)
        return;
    appCanDataEnQueue(&CanRevQueue,(ElemType*)dat); 
}
/*
CAN消息应用初始化
    -Can硬件配置
    -数据入队回调函数指针地址赋值
    -接收数据队列配置
*/
void appCanMessageInit(void)
{
    bsp_can0_init();
    CanDataEnQueueCallback=appCanDataInQueue;
    appCanQueueInit(&CanRevQueue,CanDataBuff,CANDATALEN);
}

/*
Can发送消息
data:发送数据
len: 发送长度
id: 发送CANID
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









