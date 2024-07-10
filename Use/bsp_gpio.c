#include "gd32f4xx.h"
#include  "bsp_gpio.h"

/*
系统灯初始化
*/
void  bsp_led_init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOE);
    /* configure led GPIO port */ 
    gpio_mode_set(LEDPRO, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,LEDPIN);
    gpio_output_options_set(LEDPRO, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,LEDPIN);
}
/*
拨码开关检测初始化
*/
void bsp_Dipswitch_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOC);
    
    gpio_mode_set(DIPSWITCH0_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,DIPSWITCH0_PIN);   
    gpio_mode_set(DIPSWITCH1_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,DIPSWITCH1_PIN);    
}


/*
传感器检测初始化
*/
void bsp_Sensor_iniit(void)
{
    /* enable the key clock */
    rcu_periph_clock_enable(RCU_GPIOA);     
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD); 
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_SYSCFG);

    /* configure button pin as input */
    gpio_mode_set(IN0_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN0_PIN);   
    gpio_mode_set(IN1_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN1_PIN); 
    gpio_mode_set(IN2_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN2_PIN);   
    gpio_mode_set(IN3_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN3_PIN);    
    gpio_mode_set(IN4_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN4_PIN);    
    
    gpio_mode_set(IN5_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN5_PIN); 
    gpio_mode_set(IN6_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN6_PIN);   
    gpio_mode_set(IN7_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN7_PIN);    
    gpio_mode_set(IN8_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN8_PIN);     

    gpio_mode_set(IN9_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN9_PIN); 
    gpio_mode_set(IN10_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN10_PIN);   
    gpio_mode_set(IN11_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN11_PIN);    
    gpio_mode_set(IN12_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN12_PIN);     

    gpio_mode_set(IN13_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN13_PIN);   
    gpio_mode_set(IN14_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN14_PIN); 
    gpio_mode_set(IN15_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN15_PIN);   
    gpio_mode_set(IN16_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN16_PIN);    
    gpio_mode_set(IN17_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN17_PIN); 
    
    gpio_mode_set(IN22_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN22_PIN);   
    gpio_mode_set(IN23_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN23_PIN); 
    gpio_mode_set(IN24_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN24_PIN);   
    gpio_mode_set(IN25_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN25_PIN);    
    gpio_mode_set(IN26_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN26_PIN); 
    gpio_mode_set(IN27_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,IN27_PIN);     
}


/*
电机使能,方向，故障检测,复位初始化
*/
void  bsp_StepperMotorEN_DiR_FUAL_NRST_init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD); 
    rcu_periph_clock_enable(RCU_GPIOG);    
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOB);
    /*************************************EN_init*************************************/
    //m1 
    gpio_mode_set(MT1EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT1EN_PIN);
    gpio_output_options_set(MT1EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT1EN_PIN);
    //m2
    gpio_mode_set(MT2EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT2EN_PIN);
    gpio_output_options_set(MT2EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT2EN_PIN);
    //m3
    gpio_mode_set(MT3EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT3EN_PIN);
    gpio_output_options_set(MT3EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT3EN_PIN);
    //m4
    gpio_mode_set(MT4EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT4EN_PIN);
    gpio_output_options_set(MT4EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT4EN_PIN);
    //m5
    gpio_mode_set(MT5EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT5EN_PIN);
    gpio_output_options_set(MT5EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT5EN_PIN);
    //m6
    gpio_mode_set(MT6EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT6EN_PIN);
    gpio_output_options_set(MT6EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT6EN_PIN);
    //m7
    gpio_mode_set(MT7EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT7EN_PIN);
    gpio_output_options_set(MT7EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT7EN_PIN);
    //m8
    gpio_mode_set(MT8EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT8EN_PIN);
    gpio_output_options_set(MT8EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT8EN_PIN);
    //m9
    gpio_mode_set(MT9EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT9EN_PIN);
    gpio_output_options_set(MT9EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT9EN_PIN);
    /*************************************DIR int**************************************/
    //m1
    gpio_mode_set(MT1DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT1DIR_PIN);
    gpio_output_options_set(MT1DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT1DIR_PIN);    
    //m2
    gpio_mode_set(MT2DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT2DIR_PIN);
    gpio_output_options_set(MT2DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT2DIR_PIN);
    //m3
    gpio_mode_set(MT3DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT3DIR_PIN);
    gpio_output_options_set(MT3DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT3DIR_PIN);    
    //m4
    gpio_mode_set(MT4DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT4DIR_PIN);
    gpio_output_options_set(MT4DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT4DIR_PIN);
    //m5
    gpio_mode_set(MT5DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT5DIR_PIN);
    gpio_output_options_set(MT5DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT5DIR_PIN);    
    //m6
    gpio_mode_set(MT6DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT6DIR_PIN);
    gpio_output_options_set(MT6DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT6DIR_PIN);    
    //m7
    gpio_mode_set(MT7DIR_PORT,GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT7DIR_PIN);
    gpio_output_options_set(MT7DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT7DIR_PIN);    
    //m8
    gpio_mode_set(MT8DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT8DIR_PIN);
    gpio_output_options_set(MT8DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT8DIR_PIN);    
    //m9
    gpio_mode_set(MT9DIR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT9DIR_PIN);
    gpio_output_options_set(MT9DIR_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT9DIR_PIN);     
    /****************************NFAULT_init****************************************/
    gpio_mode_set(MT1NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT1NFAULT_PIN); 
    gpio_mode_set(MT2NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT2NFAULT_PIN);
    gpio_mode_set(MT3NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT3NFAULT_PIN);    
    gpio_mode_set(MT4NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT4NFAULT_PIN); 
    gpio_mode_set(MT5NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT5NFAULT_PIN);
    gpio_mode_set(MT6NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT6NFAULT_PIN); 
    gpio_mode_set(MT7NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT7NFAULT_PIN); 
    gpio_mode_set(MT8NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT8NFAULT_PIN);
    gpio_mode_set(MT9NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,MT9NFAULT_PIN); 
    /***************************************NRST********************************/
    //m8
    gpio_mode_set(MT8_NRST_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT8_NRST_PIN);
    gpio_output_options_set(MT8_NRST_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT8_NRST_PIN);    
    //m9
    gpio_mode_set(MT9_NRST_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT9_NRST_PIN);
    gpio_output_options_set(MT9_NRST_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,MT9_NRST_PIN);  
    gpio_bit_set(MT8_NRST_PORT,MT8_NRST_PIN);
    gpio_bit_set(MT9_NRST_PORT,MT9_NRST_PIN);
   
}
/*
电机细分初始化
*/
void  bsp_StepperMotorMicrostep_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOD); 
    
    gpio_mode_set(JD_M0_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,JD_M0_PIN);
    gpio_mode_set(JD_M1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,JD_M1_PIN);    
    gpio_mode_set(JZ_M0_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,JZ_M0_PIN);   
    gpio_mode_set(JZ_M1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,JZ_M1_PIN);    
    
    gpio_output_options_set(JD_M0_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,JD_M0_PIN);    
    gpio_output_options_set(JD_M1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,JD_M1_PIN);
    gpio_output_options_set(JZ_M0_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,JZ_M0_PIN);    
    gpio_output_options_set(JZ_M1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,JZ_M1_PIN);    
}
/*
24V5路输出，8803故障输出输入，初始化
*/
void bsp_Out24V_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOG);    
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    
    gpio_mode_set(OUT1_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,OUT1_EN_PIN);
    gpio_mode_set(OUT2_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,OUT2_EN_PIN);    
    gpio_mode_set(OUT3_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,OUT3_EN_PIN);
    gpio_mode_set(OUT4_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,OUT4_EN_PIN);    
    gpio_mode_set(OUT5_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,OUT5_EN_PIN); 
    gpio_mode_set(OUT_RST_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,OUT_RST_PIN); 
    
    gpio_output_options_set(OUT1_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,OUT1_EN_PIN);
    gpio_output_options_set(OUT2_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,OUT2_EN_PIN);
    gpio_output_options_set(OUT3_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,OUT3_EN_PIN);
    gpio_output_options_set(OUT4_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,OUT4_EN_PIN);
    gpio_output_options_set(OUT5_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,OUT5_EN_PIN);
    gpio_output_options_set(OUT_RST_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,OUT_RST_PIN);  
    //IN
    gpio_mode_set(OUT_NFAULT_PORT,GPIO_MODE_INPUT, GPIO_PUPD_NONE,OUT_NFAULT_PIN);     
    
}











