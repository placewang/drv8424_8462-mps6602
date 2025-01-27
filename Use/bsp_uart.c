#include <stdio.h>
#include "gd32f4xx.h"

uint32_t BaudRate=115200;

void bsp_uart0_int(void)
{    
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* configure the USART0 TX pin and USART0 RX pin */
    gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9);
    gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_10);

    /* configure USART0 TX as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    /* configure USART0 RX as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
   
    usart_baudrate_set(USART0, BaudRate);
    usart_word_length_set(USART0,8);
    usart_stop_bit_set(USART0,1);
    usart_parity_config(USART0,USART_PM_NONE);
    usart_data_first_config(USART0,USART_MSBF_LSB);
    usart_oversample_config(USART0,USART_OVSMOD_16);
    
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0,USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0,USART_FLAG_TBE));
    return ch;
}

























