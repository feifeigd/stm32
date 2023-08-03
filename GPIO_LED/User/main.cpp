

#include "stm32f10x_conf.h"

void Delay(u32 count);
void LED_Cfg(void);

int main(void){
	GPIO_InitTypeDef GPIO_InitStructure;	// gpio 初始化参数
	// GPIO 挂载在APB2 总线上，打开端口A和端口D时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 设置IO口速度
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	// 要初始化的IO口
	GPIO_Init(GPIOA, &GPIO_InitStructure);	// GPIO 组 
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
	
	while(1){
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);	// 设置为低电平		
		GPIO_SetBits(GPIOD, GPIO_Pin_2);	// 设置为高电平
		Delay(3000000);
		
		GPIO_SetBits(GPIOA, GPIO_Pin_8);// 设置为高电平
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);// 设置为低电平
		Delay(3000000);
	}
	return 0;
}

void Delay(u32 count){
	u32 i = 0;
	for(; i < count; ++i);
}

void LED_Cfg(void){
	/*GPIO_InitTypeDef led_gpio;*/
	
}
