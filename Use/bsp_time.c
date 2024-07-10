#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_uart.h"
#include "bsp_time.h"

/*
电机电流GPIO初始化
*/
void Timer3_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);

    gpio_mode_set(MOTORCUR1_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR1_Pin);
    gpio_mode_set(MOTORCUR2_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR2_Pin);
    gpio_mode_set(MOTORCUR3_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR3_Pin);
    gpio_mode_set(MOTORCUR4_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR4_Pin);
    
    gpio_output_options_set(MOTORCUR1_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR1_Pin);
    gpio_output_options_set(MOTORCUR2_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR2_Pin);
    gpio_output_options_set(MOTORCUR3_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR3_Pin);
    gpio_output_options_set(MOTORCUR4_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR4_Pin);
    
    gpio_af_set(MOTORCUR1_Port, GPIO_AF_2, MOTORCUR1_Pin);
    gpio_af_set(MOTORCUR2_Port, GPIO_AF_2, MOTORCUR2_Pin);
    gpio_af_set(MOTORCUR3_Port, GPIO_AF_2, MOTORCUR3_Pin);
    gpio_af_set(MOTORCUR4_Port, GPIO_AF_2, MOTORCUR4_Pin);    
}

/*
电机电流GPIO初始化
*/

void Timer8_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOE);

    gpio_mode_set(MOTORCUR5_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR5_Pin);
    gpio_mode_set(MOTORCUR6_Port,GPIO_MODE_AF,GPIO_PUPD_NONE,MOTORCUR6_Pin);

    gpio_output_options_set(MOTORCUR5_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR5_Pin);
    gpio_output_options_set(MOTORCUR6_Port,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MOTORCUR6_Pin);
    
    gpio_af_set(MOTORCUR5_Port, GPIO_AF_3, MOTORCUR5_Pin);
    gpio_af_set(MOTORCUR6_Port, GPIO_AF_3, MOTORCUR6_Pin);
  
}

/*
PWM_3
*/
void bsp_Timer3_PWM_Config(void)
{
    timer_oc_parameter_struct timer_ocintpara;

    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER3);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER3);
    Timer3_gpio_config();
    /* TIMER3 configuration */
    timer_initpara.prescaler         = 0;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = PWM_MAXVAL-1;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER3,&timer_initpara);


     /* CH1,CH2 and CH3 CH4 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE ;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(TIMER3,TIMER_CH_0,&timer_ocintpara);
    timer_channel_output_config(TIMER3,TIMER_CH_1,&timer_ocintpara);
    timer_channel_output_config(TIMER3,TIMER_CH_2,&timer_ocintpara);
    timer_channel_output_config(TIMER3,TIMER_CH_3,&timer_ocintpara);    


    timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_0,0);
    timer_channel_output_mode_config(TIMER3,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_1,0);
    timer_channel_output_mode_config(TIMER3,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_2,0);
    timer_channel_output_mode_config(TIMER3,TIMER_CH_2,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3,TIMER_CH_2,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER3,TIMER_CH_3,0);
    timer_channel_output_mode_config(TIMER3,TIMER_CH_3,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);
    /* TIMER3 counter enable */
    timer_enable(TIMER3);
}

/*
PWM_3
*/
void bsp_Timer8_PWM_Config(void)
{
    timer_oc_parameter_struct timer_ocintpara;

    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER8);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER8);
    Timer8_gpio_config();
    /* TIMER8 configuration */
    timer_initpara.prescaler         = 0;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = PWM_MAXVAL;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV2;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER8,&timer_initpara);


     /* CH1,CH2 and CH3 CH4 configuration in PWM mode */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE ;
    timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(TIMER8,TIMER_CH_0,&timer_ocintpara);
    timer_channel_output_config(TIMER8,TIMER_CH_1,&timer_ocintpara);
  


    timer_channel_output_pulse_value_config(TIMER8,TIMER_CH_0,0);
    timer_channel_output_mode_config(TIMER8,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER8,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_pulse_value_config(TIMER8,TIMER_CH_1,0);
    timer_channel_output_mode_config(TIMER8,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER8,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);

    /* TIMER8 counter enable */
    timer_enable(TIMER8);
}
//MT1_Step_gpioinit
void MtStep1gpio_init(void)
{

    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOG);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP1_PIN);
    gpio_output_options_set(MT_STEP1_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP1_PIN);

}
//MT1_StepTime_init
void bsp_Time1Step_init(void)
{
   timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER1);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER1);
    
    timer_deinit(TIMER1);
    MtStep1gpio_init();
    
    /* TIMER1 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER1);
    
    timer_interrupt_flag_clear(TIMER1,TIMER_INT_FLAG_UP);
    
    nvic_irq_enable(TIMER1_IRQn,0,0);
}
//MT2_Step_gpioinit
void MtStep2gpio_init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOG);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP2_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP2_PIN);
    gpio_output_options_set(MT_STEP2_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP2_PIN);

}
//MT2_StepTime_init
void bsp_Time2Step_init(void)
{
   timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER2);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_internal_clock_config(TIMER2);
    timer_deinit(TIMER2);
    
    MtStep2gpio_init();
    
    /* TIMER2 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER2);
    
    timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_UP);
    
    nvic_irq_enable(TIMER2_IRQn,0,0);
}
//MT3_Step_gpioinit
void MtStep3gpio_init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOB);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP3_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP3_PIN);
    gpio_output_options_set(MT_STEP3_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP3_PIN);
}
//MT3_StepTime_init
void bsp_Time4Step_init(void)
{
   timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER4);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_internal_clock_config(TIMER4);
    timer_deinit(TIMER4);
    
    MtStep3gpio_init();
    
    /* TIMER4 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER4,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER4);
    
    timer_interrupt_flag_clear(TIMER4,TIMER_INT_FLAG_UP);
    
    nvic_irq_enable(TIMER4_IRQn,0,0);
}

//MT4_Step_gpioinit
void MtStep4gpio_init(void)
{

    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOE);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP4_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP4_PIN);
    gpio_output_options_set(MT_STEP4_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP4_PIN);
}
//MT4_StepTime_init
void bsp_Time5Step_init(void)
{
   timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER5);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_internal_clock_config(TIMER5);
    timer_deinit(TIMER5);
    
    MtStep4gpio_init();
    
    /* TIMER4 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER5,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER5);
    
    timer_interrupt_flag_clear(TIMER5,TIMER_INT_FLAG_UP);
    
    nvic_irq_enable(TIMER5_DAC_IRQn,0,0);
}
//MT5_Step_gpioinit
void MtStep5gpio_init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOF);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP5_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP5_PIN);
    gpio_output_options_set(MT_STEP5_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP5_PIN);
}
//MT5_StepTime_init
void bsp_Time6Step_init(void)
{
   timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER6);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_internal_clock_config(TIMER6);
    timer_deinit(TIMER6);
    
    MtStep5gpio_init();
    
    /* TIMER4 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER6,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER6);
    
    timer_interrupt_flag_clear(TIMER6,TIMER_INT_FLAG_UP);
    
    nvic_irq_enable(TIMER6_IRQn,0,0);
}

//MT6_Step_gpioinit
void MtStep6gpio_init(void)
{

    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOF);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP6_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP6_PIN);
    gpio_output_options_set(MT_STEP6_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP6_PIN);
}
//MT6_StepTime_init
void bsp_Time9Step_init(void)
{
   timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER9);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_internal_clock_config(TIMER9);
    timer_deinit(TIMER9);
    
    MtStep6gpio_init();
    
    /* TIMER9 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER9,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER9);
    
    timer_interrupt_flag_clear(TIMER9,TIMER_INT_FLAG_UP);
    
    nvic_irq_enable(TIMER0_UP_TIMER9_IRQn,0,0);
}
//MT7_Step_gpioinit
void MtStep7gpio_init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOE);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP7_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP7_PIN);
    gpio_output_options_set(MT_STEP7_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP7_PIN);
}
//MT7_StepTime_init
void bsp_Time10Step_init(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER10);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER10);
    
    timer_deinit(TIMER10);
    
    MtStep7gpio_init();
    
    /* TIMER10 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER10,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER10);
    timer_interrupt_flag_clear(TIMER10, TIMER_INT_FLAG_UP); 
    nvic_irq_enable(TIMER0_TRG_CMT_TIMER10_IRQn,0,0);
}
//MT8_Step_gpioinit
void MtStep8gpio_init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOF);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP8_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP8_PIN);
    gpio_output_options_set(MT_STEP8_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP8_PIN);
}

//MT8_StepTime_init
void bsp_Time11Step_init(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER11);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER11);
    
    timer_deinit(TIMER11);
    
    MtStep8gpio_init();
    
    /* TIMER11 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER11,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER11);
    timer_interrupt_flag_clear(TIMER11, TIMER_INT_FLAG_UP);
    nvic_irq_enable(TIMER7_BRK_TIMER11_IRQn,0,0);
}
//MT9_Step_gpioinit
void MtStep9gpio_init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* configure led GPIO port */ 
    gpio_mode_set(MT_STEP9_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,MT_STEP9_PIN);
    gpio_output_options_set(MT_STEP9_PORT,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,MT_STEP9_PIN);
}

//MT9_StepTime_init
void bsp_Time12Step_init(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER12);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    
    timer_internal_clock_config(TIMER12);
    
    timer_deinit(TIMER12);
    
    MtStep9gpio_init();
    
    /* TIMER12 configuration */
    timer_initpara.prescaler         = 168-1;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 0;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER12,&timer_initpara);

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER12);
    timer_interrupt_flag_clear(TIMER12, TIMER_INT_FLAG_UP);   
    nvic_irq_enable(TIMER7_UP_TIMER12_IRQn,0,0);
}

/*MT1*/
//电机1中断处理回调
void (*Step1_TIM1InterruptCallback)(void);
void TIMER1_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER1,TIMER_INT_UP);
    Step1_TIM1InterruptCallback();
}
/*MT2*/
//电机2中断处理回调
void (*Step2_TIM2InterruptCallback)(void);
void TIMER2_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER2,TIMER_INT_UP);
    Step2_TIM2InterruptCallback();
}

/*MT3*/
//电机2中断处理回调
void (*Step3_TIM4InterruptCallback)(void);
void TIMER4_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER4,TIMER_INT_UP);
    Step3_TIM4InterruptCallback();
}
/*MT4*/
//电机4中断处理回调
void (*Step4_TIM5InterruptCallback)(void);
void TIMER5_DAC_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER5,TIMER_INT_UP);
    Step4_TIM5InterruptCallback();
}
/*MT5*/
//电机5中断处理回调
void (*Step5_TIM6InterruptCallback)(void);
void TIMER6_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER6,TIMER_INT_UP);
    Step5_TIM6InterruptCallback();
}
/*MT6*/
//电机6中断处理回调
void (*Step6_TIM9InterruptCallback)(void);
void TIMER0_UP_TIMER9_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER9,TIMER_INT_UP);
    Step6_TIM9InterruptCallback();
}
/*MT7*/
void (*Step7_TIM10InterruptCallback)(void);
void TIMER0_TRG_CMT_TIMER10_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER10,TIMER_INT_UP);
    Step7_TIM10InterruptCallback();
}
/*MT8*/
void (*Step8_TIM11InterruptCallback)(void);
void TIMER7_BRK_TIMER11_IRQHandler(void)
{    
    timer_interrupt_flag_clear(TIMER11,TIMER_INT_UP);
    Step8_TIM11InterruptCallback();
}
/*MT9*/
void (*Step9_TIM12InterruptCallback)(void);
void TIMER7_UP_TIMER12_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER12,TIMER_INT_UP);
    Step9_TIM12InterruptCallback();
}


