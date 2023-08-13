#pragma once

#include "Gpio.h"

namespace stmcpp{
	
    class Led : public Gpio{
    public:
        using Gpio::Gpio;
        
        void On(){
            SetBit();
        }
        void Off(){
            ResetBit();
        }
    };

}
