#ifndef _BSPUART_H
#define _BSPUART_H

#include <stdio.h>

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


void bsp_uart0_int(void);



#endif





