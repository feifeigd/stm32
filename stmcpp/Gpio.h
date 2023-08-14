#pragma once

#include "device.h"

namespace stmcpp{
    class Gpio{
        // 挂载 APB2 时钟总线
        uint32_t RCC_APB2Periph_{RCC_APB2Periph_GPIOA};
        GPIO_TypeDef* GPIOx_{GPIOA};
        uint32_t pin_{GPIO_Pin_0};

        
        GPIO_InitTypeDef GPIO_InitStructure_{};	// gpio 初始化参数
	public:
        Gpio() = default;
		Gpio(uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint32_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);

        void Init();

        // 开启 I/O 端口时钟
        void Enable(){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_, ENABLE);
        }

        void Disable(){
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_, DISABLE);
        }

        void SetBit(){
            GPIO_SetBits(GPIOx_, pin_);
        }

        void ResetBit(){            
            GPIO_ResetBits(GPIOx_, pin_);
        }

        void Toggle(){
            GPIOx_->ODR ^= pin_;
        }
    };
}
