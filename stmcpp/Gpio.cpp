#include "Gpio.h"

using namespace stmcpp;

Gpio::Gpio(uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint32_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
    : RCC_APB2Periph_{RCC_APB2Periph}, GPIOx_{GPIOx}, pin_{pin}{
    GPIO_InitStructure_.GPIO_Pin    = pin_;
    GPIO_InitStructure_.GPIO_Mode   = mode;
    GPIO_InitStructure_.GPIO_Speed  = speed;
}

void Gpio::Init(){
    bool disable_jtag = false;
    if((RCC_APB2Periph_GPIOA == RCC_APB2Periph_ && pin_ == GPIO_Pin_15) 
    || (RCC_APB2Periph_GPIOB == RCC_APB2Periph_ && (pin_ == GPIO_Pin_3 || pin_ == GPIO_Pin_4) )){
        disable_jtag = true;
    }
    if(disable_jtag){
        RCC_APB2Periph_ |= RCC_APB2Periph_AFIO;
    }
    Enable();
    if(disable_jtag){
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    }

    GPIO_Init(GPIOx_, &GPIO_InitStructure_);
}
