#ifndef __QUEUE__H
#define __QUEUE__H

#include "gd32f4xx.h"

#define  True  1
#define  False 0
#define  CANDATALEN                     50


typedef can_receive_message_struct ElemType;

// 定义循环队列结构体
typedef struct Queue{
	unsigned int front;	  //队列头下标
	unsigned int rear;	  //队列尾下标
	unsigned int MAXSIZE; //队列缓存长度（初始化时赋值）
	ElemType *data;
}Queue;

extern Queue    CanRevQueue;                    //队列操作句柄  
extern ElemType CanDataBuff[CANDATALEN];		 //CAN队列缓存区

void appCanQueueInit(Queue* q,ElemType * buffer, unsigned int len);
int appCanDataDeQueue(Queue* , ElemType *);
int appCanDataEnQueue(Queue* , ElemType *);
int appCanDataQueueLength(Queue *q);


#endif




