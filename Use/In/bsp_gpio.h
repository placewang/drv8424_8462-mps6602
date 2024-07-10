#ifndef  _BSPGPIO_H
#define  _BSPGPIO_H

//LED
#define LEDPRO    GPIOE
#define LEDPIN    GPIO_PIN_0
//拨码
#define DIPSWITCH0_PORT GPIOC
#define DIPSWITCH1_PORT GPIOC
#define DIPSWITCH0_PIN  GPIO_PIN_11
#define DIPSWITCH1_PIN  GPIO_PIN_12
//传感器
#define IN0_PORT   GPIOC
#define IN1_PORT   GPIOA 
#define IN2_PORT   GPIOA 
#define IN3_PORT   GPIOC 
#define IN4_PORT   GPIOC
#define IN5_PORT   GPIOG 
#define IN6_PORT   GPIOC 
#define IN7_PORT   GPIOC 
#define IN8_PORT   GPIOG 
#define IN9_PORT   GPIOG 
#define IN10_PORT  GPIOD 
#define IN11_PORT  GPIOD 
#define IN12_PORT  GPIOD 
#define IN13_PORT  GPIOD 
#define IN14_PORT  GPIOD 
#define IN15_PORT  GPIOD 
#define IN16_PORT  GPIOD 
#define IN17_PORT  GPIOD 
#define IN22_PORT  GPIOG 
#define IN23_PORT  GPIOG 
#define IN24_PORT  GPIOG 
#define IN25_PORT  GPIOG 
#define IN26_PORT  GPIOB 
#define IN27_PORT  GPIOB 
//pin
#define IN0_PIN    GPIO_PIN_10  
#define IN1_PIN    GPIO_PIN_15  
#define IN2_PIN    GPIO_PIN_8  
#define IN3_PIN    GPIO_PIN_9  
#define IN4_PIN    GPIO_PIN_8
#define IN5_PIN    GPIO_PIN_8  
#define IN6_PIN    GPIO_PIN_6  
#define IN7_PIN    GPIO_PIN_7  
#define IN8_PIN    GPIO_PIN_6
#define IN9_PIN    GPIO_PIN_7  
#define IN10_PIN   GPIO_PIN_15  
#define IN11_PIN   GPIO_PIN_14 
#define IN12_PIN   GPIO_PIN_13
#define IN13_PIN   GPIO_PIN_12
#define IN14_PIN   GPIO_PIN_11  
#define IN15_PIN   GPIO_PIN_10  
#define IN16_PIN   GPIO_PIN_9 
#define IN17_PIN   GPIO_PIN_8
#define IN22_PIN   GPIO_PIN_5
#define IN23_PIN   GPIO_PIN_4
#define IN24_PIN   GPIO_PIN_3  
#define IN25_PIN   GPIO_PIN_2  
#define IN26_PIN   GPIO_PIN_11 
#define IN27_PIN   GPIO_PIN_10
//电机使能端口
#define MT1EN_PORT   GPIOD
#define MT2EN_PORT   GPIOG
#define MT3EN_PORT   GPIOG
#define MT4EN_PORT   GPIOE
#define MT5EN_PORT   GPIOF
#define MT6EN_PORT   GPIOF
#define MT7EN_PORT   GPIOE
#define MT8EN_PORT   GPIOF
#define MT9EN_PORT   GPIOC
//pin
#define MT1EN_PIN   GPIO_PIN_6
#define MT2EN_PIN   GPIO_PIN_11
#define MT3EN_PIN   GPIO_PIN_15
#define MT4EN_PIN   GPIO_PIN_2
#define MT5EN_PIN   GPIO_PIN_0
#define MT6EN_PIN   GPIO_PIN_3
#define MT7EN_PIN   GPIO_PIN_11
#define MT8EN_PIN   GPIO_PIN_7
#define MT9EN_PIN   GPIO_PIN_1
//电机故障检测端口
#define MT1NFAULT_PORT   GPIOG
#define MT2NFAULT_PORT   GPIOG
#define MT3NFAULT_PORT   GPIOB
#define MT4NFAULT_PORT   GPIOC
#define MT5NFAULT_PORT   GPIOC
#define MT6NFAULT_PORT   GPIOC
#define MT7NFAULT_PORT   GPIOE
#define MT8NFAULT_PORT   GPIOF
#define MT9NFAULT_PORT   GPIOC
//pin
#define MT1NFAULT_PIN   GPIO_PIN_10
#define MT2NFAULT_PIN   GPIO_PIN_14
#define MT3NFAULT_PIN   GPIO_PIN_5
#define MT4NFAULT_PIN   GPIO_PIN_13
#define MT5NFAULT_PIN   GPIO_PIN_14
#define MT6NFAULT_PIN   GPIO_PIN_15
#define MT7NFAULT_PIN   GPIO_PIN_10
#define MT8NFAULT_PIN   GPIO_PIN_10
#define MT9NFAULT_PIN   GPIO_PIN_3
//电机方向端口
#define MT1DIR_PORT     GPIOD
#define MT2DIR_PORT     GPIOG 
#define MT3DIR_PORT     GPIOB
#define MT4DIR_PORT     GPIOE
#define MT5DIR_PORT     GPIOF
#define MT6DIR_PORT     GPIOF 
#define MT7DIR_PORT     GPIOE 
#define MT8DIR_PORT     GPIOF 
#define MT9DIR_PORT     GPIOC 
//pin
#define MT1DIR_PIN   GPIO_PIN_7
#define MT2DIR_PIN   GPIO_PIN_12
#define MT3DIR_PIN   GPIO_PIN_3
#define MT4DIR_PIN   GPIO_PIN_3
#define MT5DIR_PIN   GPIO_PIN_1
#define MT6DIR_PIN   GPIO_PIN_4
#define MT7DIR_PIN   GPIO_PIN_12
#define MT8DIR_PIN   GPIO_PIN_8
#define MT9DIR_PIN   GPIO_PIN_2
//电机配置端口（DRV8424细分）
#define JD_M0_PORT     GPIOD   
#define JD_M1_PORT     GPIOD
#define JD_M0_PIN      GPIO_PIN_2 
#define JD_M1_PIN      GPIO_PIN_3   
//pin
#define JZ_M0_PORT     GPIOD
#define JZ_M1_PORT     GPIOD
#define JZ_M0_PIN      GPIO_PIN_4
#define JZ_M1_PIN      GPIO_PIN_5
//电机复位端口（mps6602）
#define MT8_NRST_PORT  GPIOF  
#define MT9_NRST_PORT  GPIOC 
//pin
#define MT8_NRST_PIN   GPIO_PIN_6
#define MT9_NRST_PIN   GPIO_PIN_0
//24V5路输出端口
#define OUT1_EN_PORT    GPIOG
#define OUT2_EN_PORT    GPIOG
#define OUT3_EN_PORT    GPIOE
#define OUT4_EN_PORT    GPIOE
#define OUT5_EN_PORT    GPIOE
#define OUT_NFAULT_PORT GPIOF
#define OUT_RST_PORT    GPIOF
//pin
#define OUT1_EN_PIN     GPIO_PIN_0
#define OUT2_EN_PIN     GPIO_PIN_1
#define OUT3_EN_PIN     GPIO_PIN_7
#define OUT4_EN_PIN     GPIO_PIN_8
#define OUT5_EN_PIN     GPIO_PIN_9
#define OUT_NFAULT_PIN  GPIO_PIN_14
#define OUT_RST_PIN     GPIO_PIN_15

void bsp_led_init(void);
void bsp_Dipswitch_init(void);
void bsp_Sensor_iniit(void);
void bsp_StepperMotorEN_DiR_FUAL_NRST_init(void);
void bsp_StepperMotorMicrostep_init(void);
void bsp_Out24V_init(void);

#endif




