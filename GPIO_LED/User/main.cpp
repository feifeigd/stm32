
#include <Application.h>
#include <Delay.h>
#include <Led.h>
#include <Usart.h>

// 3个G 正常
// 2个3.3V 正常
// 5V 正常
// VB，R 未测试

// B0~B1, B5 ~ B15 亮


// B3 B4 不亮
// A15 不亮
// 参考 STM32F103 使用PA15 PB4 PB3作为普通IO方法
// 可以点亮 https://blog.csdn.net/weixin_41667051/article/details/86504127

// A0 ~ A12 亮

// C13~C15 亮

/*
STM32F103C8T6 核心板双排管脚测试:

P3
 1 VBAT   未测试
 2 PC13   亮
 3 PC14   亮
 4 PC15   亮
 5 PA0    亮
 6 PA1    亮
 7 PA2    亮
 8 PA3    亮
 9 PA4    亮
10 PA5    亮
11 PA6    亮
12 PA7    亮
13 PB0    亮
14 PB1    亮
15 PB10   亮
16 PB11   亮
17 NRST   未测试
18 VCC3V3 正常
19 GND    正常
20 GND    正常

P4
 1 VC3V3 正常
 2 GND   正常
 3 5V    正常
 4 PB9   亮
 5 PB8   亮
 6 PB7   亮
 7 PB6   亮
 8 PB5   亮
 9 PB4   亮
10 PB3   亮
11 PA15  可以，要做引脚重映射
12 PA12  亮
13 PA11  亮
14 PA10  亮
15 PA9   亮
16 PA8   亮
17 PB15  亮
18 PB14  亮
19 PB13  亮
20 PB12  亮

*/

#define TEST_CLOCK	RCC_APB2Periph_GPIOC
#define TEST_PORT 	GPIOC
#define TEST_PIN 	GPIO_Pin_13


#define LED_ON app.led.On()
#define LED_OFF app.led.Off()

class Application: stmcpp::Application{
public:
		
	virtual bool init() override{
		led = stmcpp::Led{TEST_CLOCK, TEST_PORT, TEST_PIN, GPIO_Mode_Out_PP, GPIO_Speed_50MHz};
		led.Init();
		return true;
	};
	
	stmcpp::Led led;
};


#include <cstdio> // printf
//#include <iostream>
#include <vector>

void Timer_Config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InternalClockConfig(TIM2);
	TIM_DeInit(TIM2);
	// Period / (72M / (Prescaler + 1)) = _ 秒
	// 1000 / (72000000 / 36000) = 0.5 秒
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure{
		.TIM_Prescaler = 36000 - 1, // 预分频数
		.TIM_CounterMode = TIM_CounterMode_Up, // 定时器计数为向上计数模式
		.TIM_Period = 1000, // 定时器周期
		.TIM_ClockDivision = TIM_CKD_DIV1, // TIM2 时钟分频，1表示不分频
	};
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除定时器2的溢出标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能定时器2溢出中断
	TIM_Cmd(TIM2, ENABLE); // 定时器使能
	
	// 配置NVIC（以分组2为例）
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
	
}

	Application app;
int main(void){
	app.init();
	Timer_Config();
		
	Usart::init(9600);
	auto v = new std::vector<int>{00};
	delete v;
	// 发送欢迎信息
	char welcome[] = "STM32F103C8T6 Serial Test\r\n";
	printf("%s", welcome);
	
	while(1){
		// 闪烁LED，指示系统运行
		//app.led.Toggle();
		Delay::ms(500);
		Usart::update();		
	}

	return 0;
}

extern "C" void TIM2_IRQHandler(){
	static bool flag_bit = false;
	
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); // 清除溢出中断标志位
		flag_bit = !flag_bit;
		if(flag_bit){
			app.led.Off();
		}else{
			app.led.On();
		}		
	}
}

