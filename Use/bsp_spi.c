#include "systick.h"
#include "gd32f4xx.h"
#include "bsp_uart.h"

#define SET_SPI1_NSS_HIGH()          gpio_bit_set(GPIOB,GPIO_PIN_12)
#define SET_SPI1_NSS_LOW()           gpio_bit_reset(GPIOB,GPIO_PIN_12)
#define SET_SPI0_NSS1_HIGH()         gpio_bit_set(GPIOA,GPIO_PIN_4)
#define SET_SPI0_NSS1_LOW()          gpio_bit_reset(GPIOA,GPIO_PIN_4)
#define SET_SPI0_NSS2_HIGH()         gpio_bit_set(GPIOB,GPIO_PIN_0)
#define SET_SPI0_NSS2_LOW()          gpio_bit_reset(GPIOB,GPIO_PIN_0)

/*!
    \brief      configure the SPI peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bsp_spi1_Init(void)
{
    spi_parameter_struct spi_init_struct;
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_SPI1);
    
    /* configure SPI1 GPIO */
    gpio_af_set(GPIOB, GPIO_AF_5, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);

    /* set SPI1_NSS as GPIO*/
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);    
    
    /* configure SPI1 parameter */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_16BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_2EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_32;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(SPI1, &spi_init_struct);
    spi_enable(SPI1);
}
/*!
    \brief      configure the SPI peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bsp_spi0_Init(void)
{
    spi_parameter_struct spi_init_struct;
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_SPI0);
    
    /* configure SPI0 GPIO */
    gpio_af_set(GPIOA, GPIO_AF_5, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

    /* set SPI0_NSS1 as GPIO*/
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4); 
    /* set SPI0_NSS2 as GPIO*/    
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0); 
    SET_SPI0_NSS1_HIGH();    
    SET_SPI0_NSS2_HIGH();
    
    /* configure SPI1 parameter */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_16BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_64;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(SPI0, &spi_init_struct);
    spi_enable(SPI0);
}

/*
spi读设备寄存器
data:地址(8bit)+数据(8bit)
return:8462返回数据
*/
unsigned short bsp_spi1_readdata_16bits(unsigned short data)
{
    uint16_t status=0;
    
    //置一读标志
    data|=(uint16_t)(1<<14);
    
    SET_SPI1_NSS_LOW();
    //延迟片选
    delay_1ms(1);
    while(RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_TBE));
    spi_i2s_data_transmit(SPI1,data);
    while(RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_RBNE));
    status=spi_i2s_data_receive(SPI1);    
    SET_SPI1_NSS_HIGH();
    delay_1ms(1);
    return status;
}
/*
spi写设备寄存器
data:地址(8bit)+数据(8bit)
return:8462返回数据
*/
unsigned short bsp_spi1_writedata_16bits(unsigned short data)
{
    uint16_t status=0;
    //置写标志
    data&=(uint16_t)(~(1<<14));
    
    SET_SPI1_NSS_LOW();
    //延迟片选
    delay_1ms(1);
    while(RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_TBE));
    spi_i2s_data_transmit(SPI1,data);
    while(RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_RBNE));
    status=spi_i2s_data_receive(SPI1);      
    SET_SPI1_NSS_HIGH();
    delay_1ms(1);
    return status;
}
/*
spi0 读设备寄存器
num:1-NSS1(motor8)
    2-Nss2(motor9)
data:地址(3bit)+读写(1bit)+数据(12bit)
return:mps6602返回数据
*/
unsigned short bsp_spi0_readdata_16bits(unsigned char num,unsigned short data)
{
    uint16_t status=0;
        //置读标志
    data&=(uint16_t)(~(1<<12));
    if(num==1)
    { 
        SET_SPI0_NSS1_LOW();
        while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE));
        spi_i2s_data_transmit(SPI0,data);       
        while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE));
        status=spi_i2s_data_receive(SPI0);     
        SET_SPI0_NSS1_HIGH();
     }
     else if(num==2)
     {
        SET_SPI0_NSS2_LOW();
        while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE));
        spi_i2s_data_transmit(SPI0,data);
        while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE));
        status=spi_i2s_data_receive(SPI0);    
        SET_SPI0_NSS2_HIGH();           
     }
     return status;
}
/*
spi0 写设备寄存器
num:1-NSS1(motor8)
    2-Nss2(motor9)
data:地址(3bit)+读写(1bit)+数据(12bit)
return:mps6602返回数据
*/
unsigned short bsp_spi0_writedata_16bits(unsigned char num,unsigned short data)
{
    uint16_t cont=0x1f;
    uint16_t status=0;
        //置写标志
    data|=(uint16_t)(1<<12);
    if(num==1)
    {
        SET_SPI0_NSS1_LOW();
        while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE));
        spi_i2s_data_transmit(SPI0,data);       
        while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE));
        status=spi_i2s_data_receive(SPI0);  
        while(cont--){;}
        SET_SPI0_NSS1_HIGH();
        while(cont--){;}    
     }
     else if(num==2)
     {
        SET_SPI0_NSS2_LOW();
        while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE));
        spi_i2s_data_transmit(SPI0,data);
        while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE));
        status=spi_i2s_data_receive(SPI0);   
        while(cont--){;}         
        SET_SPI0_NSS2_HIGH();
        while(cont--){;}    
     }
     return status;
}
