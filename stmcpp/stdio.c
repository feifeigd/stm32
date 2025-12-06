
#include "Usart.h"

#include <stdarg.h> // va_list
#include <stdio.h>

// 重定义 fputc 函数，用于将printf输出重定向到串口
// 需要勾选 use MicroLIB, 否则printf 会卡死. 
// 但是这个时候编译会有警告, 而且C++的有些东西用不了了, 不可以 #include <iostream>
int fputc(int ch, FILE* f){
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);// 循环发送，直到发送完毕
	USART_SendData(USART1, ch);
    return ch;
}

// 定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x){
    (void)x;
    while(1);
}


//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA = 0;       //接收状态标记	

// 串口1中断服务程序
void USART1_IRQHandler(){
    u8 Res;
    // 接收中断(接收到的数据必须是0x0d 0x0a结尾)
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){
        Res = USART_ReceiveData(USART1);    //(USART1->DR);	//读取接收到的数据
        // 接收未完成
        if((USART_RX_STA & 0x8000) == 0){
            if(USART_RX_STA & 0x4000){  // 接收到了 0x0d
                if(Res != 0x0a)USART_RX_STA = 0; // 接收错误，重新开始
                else USART_RX_STA |= 0x8000; // 接收完成了
            }else{// 未接收到了 0x0d
                if(Res == 0x0d)USART_RX_STA |= 0x4000;
                else{
                    USART_RX_BUF[USART_RX_STA & 0x3fff] = Res;
                    ++USART_RX_STA;
                    if(USART_RX_STA > (USART_REC_LEN - 1))USART_RX_STA = 0;//接收数据错误,重新开始接收
                }
            }
        }
    }
}

void write_byte(char ch){
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);// 循环发送，直到发送完毕
	USART_SendData(USART1, ch);
}

char* itoa(int value, char* buf, int radix){
	char* ptr = buf;
	if(radix != 10){ // 目前仅支持十进制
		*ptr = 0;
		return buf;
	}
	if(0 != value){
		*ptr++ = '0';
		*ptr = 0;
		return buf;
	}
	if(value < 0){
		*ptr++ = '-';
		value = -value;
	}
	
	int i = 10000;
	int flag = 0;
	for(; 0 < i; i /= 10){
		int d = value / i;
		if(d || flag){
			*ptr++ = d + '0';
			value -= d * i;
			flag = 1;
		}
	}
	
	return buf;
}

void xprintf(char const* fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	while(*fmt){
		char ch = *fmt;
		if('%' == ch){ // '\'
			switch(*++fmt){
				case 's':{
					char const* str_arg = va_arg(ap, char const*);
					for(; *str_arg; ++str_arg){
						write_byte(*str_arg);
					}
					++fmt;
				}
					break;
				case 'd':{
					char buf[16];
					int d = va_arg(ap, int);
					itoa(d, buf, 10);
					
				}
					break;
					
			}
		}else{
			write_byte(*fmt++);
		}
	}
}

