#ifndef _APPMOTORSTEP_H
#define _APPMOTORSTEP_H


//����ģʽ
#define MODE_S       0           //�ٶ�ģʽ
#define MODE_P       1           //λ��ģʽ
//�Ӽ��ټ������
#define TIM1COUNTCYCLE    0.000001   //��������

/*����ٶȾ����е��ĸ�״̬*/
#define STOP              0 // ֹͣ״̬
#define ACCEL             1 // ����״̬
#define DECEL             2 // ����״̬
#define RUN               3 // ����״̬
/*������*/
enum MotorNum
{
    Motor1 =1,
    Motor2,
    Motor3,
    
    Motor4,
    Motor5,
    Motor6,
    
    Motor7,
    Motor8,
    Motor9
};

/*���μӼ������*/
typedef struct 
{
    //����˶������� 
    unsigned char  FwDir;         
    /*��ʱ��ʹ�÷�תģʽ����Ҫ���������жϲ����һ����������*/
	unsigned char i; 
    /*λ��ģʽ/�ٶ�ģʽ*/
    unsigned char mode;               
	/*��ǰ���״̬*/
	unsigned char run_state ; 
	/*��ת����*/
	unsigned char dir ; 
    //��������   
    unsigned short LockCurrent;  
    //���е���
    unsigned short RunCurrent;   
	/* �����£��£�һ����ʱ����*/
	unsigned short new_step_delay;
	/* ���ٹ��������һ����ʱ���������ڣ�*/
	unsigned short last_accel_delay;
    /*����ϵ��*/
    unsigned short accel_step;    
	/*������*/
	int  step_delay;  
	/*����λ��*/
	int  decel_start; 
	/*���ٲ���*/
	int  decel_val;   
	/*��С���*/
	int  min_delay;   
	/*���ٲ���*/
	int  accel_count; 
    /*��������*/
	int  rest;
    /*���������*/
    int  Encoder;    
	/* ���ƶ�����������*/
	unsigned int step_count;
    /*Ŀ��λ��*/
    unsigned int TargetStepCont;
   
}MotorStep;

extern unsigned short STEPCOUNT;   //�Ӽ��ٲ���


void appMotorStepInit(void);
MotorStep* GetMorotParameterPointer(unsigned char num);
int appMotorSpeedModeMove_T(unsigned char stepnum,int speed);
int appMotorStepModeMove_T(unsigned char stepnum,unsigned char mode,int step,unsigned int speed);

#endif











