#pragma once

#include "device.h"

#define USART_REC_LEN 200 //定义最大接收字节数 200


#ifdef __cplusplus

extern "C" void xprintf(char const* fmt, ...);

class Usart{
public:
    static void init(u32 bound);

    static void update();
    
    static int len;
    static int times;
};

#endif 
	

#ifdef __cplusplus
extern "C"{
#endif 
    extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
    extern u16 USART_RX_STA; 
#ifdef __cplusplus
}
#endif 
