#ifndef _BSPSPI_H
#define _BSPSPI_H

void bsp_spi1_Init(void);
void bsp_spi0_Init(void);
unsigned short bsp_spi1_readdata_16bits(unsigned short );
unsigned short bsp_spi1_writedata_16bits(unsigned short);
unsigned short bsp_spi0_readdata_16bits(unsigned char,unsigned short);
unsigned short bsp_spi0_writedata_16bits(unsigned char,unsigned short);

#endif



