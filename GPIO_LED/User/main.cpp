

#include <Application.h>
#include <Delay.h>
#include <Led.h>

void LED_Cfg(void);

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

#define TEST_CLOCK	RCC_APB2Periph_GPIOA
#define TEST_PORT 	GPIOA
#define TEST_PIN 	GPIO_Pin_15

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

int main(void){
	Application app;
	app.init();
	
	while(1){		
		
	// LED_OFF;
	// 	Delay(3000000);
	// LED_ON;
	// 	Delay(3000000);
		app.led.Toggle();
		Delay::ms(500);			
	}

	return 0;
}
