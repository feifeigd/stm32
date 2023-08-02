

#include "stm32f10x_conf.h"
#include <stm32f10x.h>

void Delay(u32 count);
void LED_Cfg(void);
int main(void){
	GPIO_InitTypeDef GPIO_InitStructure;	/* gpio */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);/* rcc */
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	
	while(1){
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		
		GPIO_SetBits(GPIOD, GPIO_Pin_2);
		Delay(3000000);
		
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		Delay(3000000);
	}
}

void Delay(u32 count){
	u32 i = 0;
	for(; i < count; ++i);
}

void LED_Cfg(void){
	/*GPIO_InitTypeDef led_gpio;*/
	
}
