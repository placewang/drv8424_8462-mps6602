#include "gd32f4xx.h"
#include "bsp_can.h"

static void can_config(void)
{
    can_parameter_struct            can_parameter;
    can_filter_parameter_struct     can_filter;
    
    can_struct_para_init(CAN_INIT_STRUCT, &can_parameter);
    can_struct_para_init(CAN_FILTER_STRUCT, &can_filter);
    /* initialize CAN register */
    can_deinit(CAN0);
    
    /* initialize CAN parameters */
    can_parameter.time_triggered = DISABLE;
    can_parameter.auto_bus_off_recovery = ENABLE;
    can_parameter.auto_wake_up = DISABLE;
    can_parameter.auto_retrans = ENABLE;
    can_parameter.rec_fifo_overwrite = DISABLE;
    can_parameter.trans_fifo_order = DISABLE;
    can_parameter.working_mode = CAN_NORMAL_MODE;
    can_parameter.resync_jump_width = CAN_BT_SJW_1TQ;
    can_parameter.time_segment_1 = CAN_BT_BS1_15TQ;
    can_parameter.time_segment_2 = CAN_BT_BS2_5TQ;
    
 /* 1MBps */
#if CAN_BAUDRATE == 1000
      can_parameter.prescaler = 2;
#elif CAN_BAUDRATE == 500
      can_parameter.prescaler = 4;    
#elif CAN_BAUDRATE == 250
      can_parameter.prescaler = 8;      
#endif   
    /* initialize CAN */
    can_init(CAN0, &can_parameter);
    
    /* initialize filter */ 
    can_filter.filter_number=0;
    can_filter.filter_mode = CAN_FILTERMODE_LIST;
    can_filter.filter_bits = CAN_FILTERBITS_32BIT;
    can_filter.filter_list_high = (CANREVIDBASS_1)<<5;
    can_filter.filter_list_low  = 0x0000;
    can_filter.filter_mask_high = (CANREVIDBASS_1)<<5;
    can_filter.filter_mask_low  = 0x0000;
    can_filter.filter_fifo_number = CAN_FIFO0;
    can_filter.filter_enable = ENABLE;    
    can_filter_init(&can_filter);
    /*列表模式接收ID*/
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
    

    nvic_irq_enable(CAN0_RX0_IRQn,0,0);
    can_interrupt_enable(CAN0, CAN_INT_RFNE0);
}


static void can_gpio_config(void)
{
    /* enable CAN clock */
    rcu_periph_clock_enable(RCU_CAN0);
    rcu_periph_clock_enable(RCU_GPIOA);
    
    /* configure CAN0 GPIO */
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_11);
    gpio_af_set(GPIOA, GPIO_AF_9, GPIO_PIN_11);
    
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_af_set(GPIOA, GPIO_AF_9, GPIO_PIN_12);
}

void bsp_can0_init(void)
{
    can_gpio_config();
    can_config();
}
/*
发送CAN0数据
data:发送数据
len: 发送长度
id: 发送CANID
*/


uint8_t bsp_Can0_Message(uint8_t *data,uint8_t len,uint16_t id)
{
    char i=0;
    can_trasnmit_message_struct transmit_message;
    transmit_message.tx_sfid = id;
    transmit_message.tx_efid = 0x00;
    transmit_message.tx_ft = CAN_FT_DATA;
    transmit_message.tx_ff = CAN_FF_STANDARD;
    transmit_message.tx_dlen = len;   
    
    for(i=0;i<len;i++)
    {
        transmit_message.tx_data[i] = data[i];
    }
    return can_message_transmit(CAN0, &transmit_message); 
}

//接收数据入队回调
void (*CanDataEnQueueCallback)(void *dat); 

/*!
    \brief      this function handles CAN0 RX0 exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void CAN0_RX0_IRQHandler(void)
{
    /* check the receive message */
    can_receive_message_struct  rev_message;
    if(can_interrupt_flag_get(CAN0,CAN_INT_FLAG_RFL0))
    {
        can_message_receive(CAN0,CAN_FIFO0,&rev_message);
        CanDataEnQueueCallback((void*)(&rev_message));              
        can_interrupt_flag_clear(CAN0,CAN_INT_FLAG_RFL0);
    } 
}

