#include "app_CanDataQueue.h"

Queue    CanRevQueue;                    //队列操作句柄  
ElemType CanDataBuff[CANDATALEN];		 //CAN队列缓存区



/*
 *  循环队列判满
 *  q 循环队列
*/
static int QueueFull(Queue *q){
    return (q -> rear + 1) % q->MAXSIZE == q -> front;
}

/*  循环队列判空q 循环队列*/
static int QueueEmpty(Queue *q){

    return q -> front == q -> rear;
}

/*
 * 初始化循环队列 
*/
void appCanQueueInit(Queue* q,ElemType * buffer, unsigned int len)
{
    q -> front =0;
	q -> rear = 0;
	q->MAXSIZE=len;
	q->data=buffer;
}
/*
 *  计算循环队列长度
 *  q 循环队列
*/
int appCanDataQueueLength(Queue *q){
    return (q -> rear - q -> front + q->MAXSIZE) % q->MAXSIZE;
}

/*
 *  循环队列 入队
 *  q 循环队列
 *  data 入队元素
*/
int appCanDataEnQueue(Queue* q, ElemType *data)
{
    if(q==NULL||data==NULL)
        return -1;    
    if(QueueFull(q)){
        return False;
    }
   // 队尾入队
    q ->data[q -> rear] = *data;
    // 更新队尾指针
    q -> rear = (q -> rear+1 )%q->MAXSIZE;;
    return True;
}

/*
 *  循环队列 出队
 *  q 循环队列
 *  *val 用来存出队元素的数据 
*/
int appCanDataDeQueue(Queue* q, ElemType *val)
{
    if(q==NULL||val==NULL)
        return -1;
    if(QueueEmpty(q)){
        return False;
    }
    // 队头元素出队
    *val = q ->data[q -> front];
    // 更新队头指针
    q -> front = (q -> front + 1) % q->MAXSIZE;
    return True;
}


