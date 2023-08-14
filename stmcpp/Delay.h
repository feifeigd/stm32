#pragma once

#include "device.h"

class Delay{
	static u8 factor_us; // us 延时倍乘数
	static u16 factor_ms; // ms 延时倍乘数
    static bool inited;
public:
    static void init(){
		// framework misc.h
        // 选择外部时钟 HCLK/8
        SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
        factor_us = SystemCoreClock / 8000000; // 为系统时钟的 1/8
        factor_ms = (u16)factor_us * 1000;
    }

    // CTRL 的 ENABLE 位
    // 为 1 表示计数器在工作
    #define SYSTICK_ENABLE(CTRL) (CTRL & 1)
    // CTRL 的 CONTFLAG 位
    // 当倒计到0时，该位为 1
    #define SYSTICK_CONTFLAG(CTRL) (CTRL & (1 << 16))

    // 延时 us 
    static void us(u32 nus);

    // 延时 ms 
    // LOAD 为24位寄存器，所以最大延时为：
    // nms <= 0xffffff * 8 * 1000 / SYSCLK
    // SYSCLK 单位为Hz， nms 单位为ms，对72MHz条件下，nms <= 1864
    static void ms(u16 nms);
};
