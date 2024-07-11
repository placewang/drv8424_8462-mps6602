# �����ӿڼ����Ӧ�ú���˵��
#### �����ļ����
![alt text](40d2d36445bd849570fbe22fdd0e40e.png)  
### �ϵ��ʼ������
~~~
|��startup_gd32f407_427.s
  |_int main(void)
      ����systick_config()           "����systick�ж�ʱ��1ms"
      ����bsp_uart0_int()            "printf���Դ�ӡ�ӿ�"
      |_appGpioSetsInit()          "IO��ʼ��" 
      |  |_bsp_led_init()                           "ϵͳ�Ƴ�ʼ��"
      |  |_bsp_Out24V_init()                        "24V5·���8803�����������"
      |  |_bsp_Sensor_iniit()                       "����������ʼ��"
      |  |_bsp_Dipswitch_init()                     "���뿪�ؼ���ʼ��"   
      |  |_bsp_StepperMotorMicrostep_init()         "���ϸ�ֳ�ʼ��"
      |  |_bsp_StepperMotorEN_DiR_FUAL_NRST_init()  "���ʹ��,����,���ϼ��,��λ"
      |_appCanMessageInit()        "CAN��ϢӦ�ó�ʼ��"
      |  |_bsp_can0_init()                          "CanӲ������"
      |  |_CanDataEnQueueCallback                   "������ӻص�����ָ���ַ��ֵ"
      |  |_appCanQueueInit();                       " �������ݶ�������"
      |_appMotorStepInit()         "����������Ƴ�ʼ��"
      |  |_Step1_TIM1InterruptCallback              "�����жϴ���ص�����_1"
      |  |          :                               
      |  |_Step9_TIM12InterruptCallback             "�����жϴ���ص�����_9"
      |  |_bsp_TimexStep_init()                     "��1·��ʱ����ʼ��"
      |  |          :
      |  |_bsp_TimexStep_init() ()                  "��9·��ʱ����ʼ��"
      |  |_app_NineStepperMotorsDefaultParameter()  "9·����ϵ�Ĭ�ϲ���"     
      |  |_appDrv8424Init()                         "��������,PWM,config"
      |  |_appDrv8462Init()                         "����,spi1Init,config" 
      |  |_appMps6602Init()                         "����,spi0Init,config" 
      |_appPowerDetectionInit()    "��Դ����ʼ��(DMA��ѯ��ʽ)"
    while(1)
    {  //ָʾ��״̬��תms
       app_System_Led(500) 
    }
~~~
### �����ӿ�˵��
## systeme
~~~
������systick�ж�ʱ��1ms,�ж����ȼ����,���������õ���ʱ�䶼���ڴ�
void SysTick_Handler(void)
~~~
## GPIO
~~~
#include "app_GpioSensor.h"
"ָʾ��״̬��תtime:���ʱ��"
void app_System_Led(unsigned short)
"��ȡ����� return bit-ID0 bit-ID1"
unsigned char appGetDipSwitchNum(void);
"4·���DRV8803��λ"
void appDrv88033_RST(void);
"��ȡDrv8803����״̬ ����Ч"
unsigned char appGetDrv88033FaultStatus(void);
"
5·������� 1-4·��DRV8803 - ����Ч  ��5·  ����©���- ����Ч 
num   : 1-5·  0-ȫ��
status: 1-��  0-��
return: -1-����������� 1-ִ����� 0-δִ��   
"
int  appRead5wayOutputPinStatus(unsigned char);
"
��5·����ܽ�״̬
num   : 1-5·   0-ȫ��: bit0-out1,bit1-out2, bit2-out3,bit3-out4,bit4-out5
return: -1-�����������  1-ִ����� 0-δִ��   
"
int  app5wayOutputEnWrite(unsigned char,unsigned char);
"
��ȡ������״̬
num   : 1-24· 
        0-ȫ��: bit0-IN0...bit23-IN27
return: -1-�����������  
"
int  appGetSensorStatus(unsigned char);
~~~
## uart0
~~~
����printf���Դ�ӡ�ӿڣ�������Ĭ��115200bps,
bsp_uart.h�ṩ���½ӿ�; �궨��LOG_ENABLEΪ��ӡ����
#define LOG_ENABLE      1
#if LOG_ENABLE 
    #define log_info(...)    printf(__VA_ARGS__)
    #define log_error(...)   printf(__VA_ARGS__)
    #define log_warning(...) printf(__VA_ARGS__)
    #define log_debug(...)   printf(__VA_ARGS__)
#else
    #define log_info(...)
    #define log_warning(...)
    #define log_error(...)
    #define log_debug(...)
#endif
#define log_funcName()   log_debug("call %s \n", __FUNCTION__)
~~~
## can0
~~~
������Ĭ��1Mbps�����������ж�,�ж����ȼ����,����ID������Ϊ�б�ģʽ��ͨ�����������޸�
 /* 1MBps */
#if CAN_BAUDRATE == 1000
      can_parameter.prescaler = 2;
#elif CAN_BAUDRATE == 500
      can_parameter.prescaler = 4;    
#elif CAN_BAUDRATE == 250
      can_parameter.prescaler = 8;      
#endif   
/*�б�ģʽ����ID*/
#ifdef CANREVIDBASS_2
    can_filter.filter_number=1;
    can_filter.filter_list_high = (CANREVIDBASS_2)<<5; 
    can_filter.filter_mask_high = (CANREVIDBASS_2)<<5;    
    can_filter_init(&can_filter);
    #endif 
    #ifdef CANREVIDBASS_3
    can_filter.filter_number=2;
    can_filter.filter_list_high = (CANREVIDBASS_3)<<5; 
    can_filter.filter_mask_high = (CANREVIDBASS_3)<<5;    
    can_filter_init(&can_filter);    
#endif
app_CanDataQueue.cΪ���ݶ��в��������������������void CAN0_RX0_IRQHandler(void)���
#include "app_CanMessage.h"
#include "app_CanDataQueue.h"
"ѭ�����г���"
#define  CANDATALEN  50
"���в������"
Queue    CanRevQueue;                          
"CAN���л�����"
ElemType CanDataBuff[CANDATALEN]	            
"����������ӻص�"
void (*CanDataEnQueueCallback)(void *dat)       
"ѭ���������"
int appCanDataEnQueue(Queue* q, ElemType *data) 
"ѭ�����г���"
int appCanDataDeQueue(Queue* q, ElemType *val) 
"Can0������Ϣ"
int appCanDataSend(unsigned char *data,unsigned char len,unsigned short id)
~~~
## ADC_DMA
~~~
#include "app_AdcPower.h"
"
��ȡ����ѹֵ(0-3.3)δ�˲�
DC12V:12V��ѹֵ
DC24V:24V��ѹֵ
"
int appGetPowerVoltageValue(float* DC12V,float* DC24V)
"
��ȡ���ʵ�ʵ�ѹֵ(0-12/24V)δ�˲�
DC12V:12V��ѹֵ
DC24V:24V��ѹֵ
"
int appGetPowerActualVoltageValue(float* DC12V,float* DC24V)
~~~
## StepMotor
___
### config  
~~~
#include "app_MotorConfig.h"
"9·����ϵ�Ĭ�ϲ�����ֵ  -���е��� -�������� -����˶�Ĭ��������"
void app_NineStepperMotorsDefaultParameter(void);
"9·���ʹ��/ʧ������ num: 1-9  0-ȫ��;  En: 0/!0  "
int appNineMotorEnbleSet(unsigned char num,unsigned char Enb);
"�������״̬��ȡ(�͵�ƽ��Ч) num: 1-9 bit0;  0-ȫ�� bit0--bit8"
int appNineMotorGetFaultStatus(unsigned char num);
"
9·������������ò���¼ ��������IC�������ڷ�ʽ����ʲ�֧��Ⱥ����
����ʹ�ö�ӦIC�ӿ�(drv8424,drv8462,mps6602)
num: 1-9 
current:����ֵ
"
int appNineMotorRunCurrentSet(unsigned char num,unsigned short current);
"
9·����������������ò���¼ ��������IC�������ڷ�ʽ����ʲ�֧��Ⱥ����,
����ʹ�ö�ӦIC�ӿ�(drv8424,drv8462,mps6602)
num: 1-9 
current:����ֵ
"
int appNineMotorLockCurrentSet(unsigned char num,unsigned short current);
"
9·���ϸ������(�ϵ�Ĭ������4ϸ��)��������ICϸ�ֵ��ڷ�ʽ�����֧��4�����
����ʹ�ö�ӦIC�ӿ�(drv8424,drv8462,mps6602))
num: 1--�����,�Ҽ���
     2-�Ҽ�1,�Ҽ�2,���1,���2
     7-�������
     8/9-���ߵ��   
     0-ȫ�� 
microstep:  0-ȫ��  
            2-1/2�� 
            4-1/4��  
            8-1/8��
"
int appNineMotorMicrostepSet(unsigned char num,unsigned char microstep);
~~~
#### StepMove
~~~
bsp_Time1Step_init()bsp_Time2Step_init()bsp_Time4Step_init()bsp_Time5Step_init()
bsp_Time6Step_init()bsp_Time9Step_init()bsp_Time10Step_init()bsp_Time11Step_init()
bsp_Time12Step_init();9����ʱ�������Ķ�ʱ�ж����ȼ����������CAN����һ��
"
appMotorStepModeMove_T()��appMotorSpeedModeMove_T()���Ǹ�λ�ñ���ֵEnCoder�������
��������ģʽ����������,���ⳡ���±������ע��SpeedModeת��StepModeҪִ�л���У׼
"
~~~
![alt text](image.png)
~~~
#include "app_Motorstep.h"
"
����λ��ָ���ص��˶�����(����) appMotorStepModeMove_T�е��ô˺����ӿ�
tye��1:��ֹ��ǰ�˶�����ͣ��,����ʱ��STEPCOUNT����������(�������һ��λ��ָ��)
    !1(Ĭ��):�ȵ�ǰ�˶�����,����ʣ��N��δ������������(�ص�λ��ָ�������λ�ã�    
mtn:������
"
static int appScissorsClipOverlappingMotion(MotorStep* Mstep, uint8_t mtn,uint8_t tye)
"   \brief �Ը����Ĳ����ƶ��������
 *  \param mode   1:����� 0:�߾��� 
 *  \param step   �ƶ��Ĳ���(>0��ת��<0��ת).
 *  \param speed  Hz
"
int appMotorStepModeMove_T(unsigned char stepnum,unsigned char mode,int step,unsigned int speed)         
"   \brief �Ը������ٶ��ƶ��������
*   \param  stepnum:������ 1-9
*   \param speed(Hz):>0��ת��<0��ת  ==0����ֹͣ
"
int appMotorSpeedModeMove_T(unsigned char stepnum,int speed)
~~~
___