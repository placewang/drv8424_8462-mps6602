#ifndef _BSPTIME_H
#define _BSPTIME_H

#define  PWM_MAXVAL                  4000                        //PWM占空比最大值


//电流控制端口
#define MOTORCUR1_Port  GPIOB
#define MOTORCUR2_Port  GPIOB
#define MOTORCUR3_Port  GPIOB
#define MOTORCUR4_Port  GPIOB
#define MOTORCUR5_Port  GPIOE
#define MOTORCUR6_Port  GPIOE
//pin
#define MOTORCUR1_Pin 	GPIO_PIN_6
#define MOTORCUR2_Pin 	GPIO_PIN_7
#define MOTORCUR3_Pin 	GPIO_PIN_8
#define MOTORCUR4_Pin 	GPIO_PIN_9
#define MOTORCUR5_Pin 	GPIO_PIN_5
#define MOTORCUR6_Pin 	GPIO_PIN_6
//脉冲控制端口
#define MT_STEP1_PORT   GPIOG
#define MT_STEP2_PORT   GPIOG
#define MT_STEP3_PORT   GPIOB
#define MT_STEP4_PORT   GPIOE
#define MT_STEP5_PORT   GPIOF
#define MT_STEP6_PORT   GPIOF
#define MT_STEP7_PORT   GPIOE
#define MT_STEP8_PORT   GPIOF
#define MT_STEP9_PORT   GPIOA
//pin
#define MT_STEP1_PIN    GPIO_PIN_9
#define MT_STEP2_PIN    GPIO_PIN_13
#define MT_STEP3_PIN    GPIO_PIN_4
#define MT_STEP4_PIN    GPIO_PIN_4
#define MT_STEP5_PIN    GPIO_PIN_2
#define MT_STEP6_PIN    GPIO_PIN_5
#define MT_STEP7_PIN    GPIO_PIN_13
#define MT_STEP8_PIN    GPIO_PIN_9
#define MT_STEP9_PIN    GPIO_PIN_1
//电机中断处理回调
extern void (*Step1_TIM1InterruptCallback)(void);
extern void (*Step2_TIM2InterruptCallback)(void);
extern void (*Step3_TIM4InterruptCallback)(void);
extern void (*Step4_TIM5InterruptCallback)(void);
extern void (*Step5_TIM6InterruptCallback)(void);
extern void (*Step6_TIM9InterruptCallback)(void);
extern void (*Step7_TIM10InterruptCallback)(void);
extern void (*Step8_TIM11InterruptCallback)(void);
extern void (*Step9_TIM12InterruptCallback)(void);

void bsp_Timer8_PWM_Config(void);
void bsp_Timer3_PWM_Config(void);
void bsp_Time1Step_init(void);
void bsp_Time2Step_init(void);
void bsp_Time4Step_init(void);
void bsp_Time5Step_init(void);
void bsp_Time6Step_init(void);
void bsp_Time9Step_init(void);
void bsp_Time10Step_init(void);
void bsp_Time11Step_init(void);
void bsp_Time12Step_init(void);

#endif

