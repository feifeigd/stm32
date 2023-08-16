

#include "Delay.h"
#include "Gpio.h"
#include "Usart.h"
#include <stdio.h>

// extern "C" int fputc(int ch, FILE* f);
// extern "C" FILE __stdout;

using namespace stmcpp;

int Usart::len;
int Usart::times;

void Usart::init(u32 bound){
    // USART1_TX PA.9
    // 复用推挽输出模式
    Gpio PA_9{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_9, GPIO_Mode_AF_PP, GPIO_Speed_50MHz};
    PA_9.Init();
    
    // USART1_RX PA.10
    // 浮空输入模式
    Gpio PA_10{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_10, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz};
    PA_10.Init();

    // NVIC 配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

    NVIC_InitTypeDef NVIC_InitStructure{};
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   // 抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 复位串口1
    USART_DeInit(USART1);
    USART_InitTypeDef USART_InitStructure{};
    USART_InitStructure.USART_BaudRate = bound; // 一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  // 一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No; // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 收发模式
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  // 开启串口时钟，一定要在 USART_Init 之前调用
    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 开启中断
    USART_Cmd(USART1, ENABLE);
}

void Usart::update(){
    if(USART_RX_STA & 0x8000){  // 接收完成
        len = USART_RX_STA & 0x3fff; 
        printf("what you send are len=%d, USART_RX_STA=0x%x:\r\n", len, USART_RX_STA);
		// USART_RX_BUF[len] = 0;
        for(int t = 0; t < len; ++t){
            // fputc( USART_RX_BUF[t], &__stdout);
            USART1->DR = USART_RX_BUF[t];
            while ((USART1->SR & 0x40) == 0)
            {
                // 等待发送结束
            }            
        }
        printf("\r\n\r\n");
        USART_RX_STA = 0;
    }else{
        ++times;
        if(times % 200)printf("please input data, and press enter .\r\n\r\n");
        Delay::ms(1000);
    }
}
