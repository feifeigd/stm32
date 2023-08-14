#include "Delay.h"


u8 Delay::factor_us; // us 延时倍乘数
u16 Delay::factor_ms; // ms 延时倍乘数
bool Delay::inited;

// 延时 us 
void Delay::us(u32 nus){
    if(!inited)init();

    SysTick->LOAD = nus * factor_us;
    SysTick->VAL = 0;   // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开始倒数

    u32 temp{};
    do{
        temp = SysTick->CTRL;
    }while(SYSTICK_ENABLE(temp) && ! SYSTICK_CONTFLAG(temp));    // 等待时间到达

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  // 关闭计数器
    SysTick->VAL = 0;   // 清空计数器
}

// 延时 ms 
// LOAD 为24位寄存器，所以最大延时为：
// nms <= 0xffffff * 8 * 1000 / SYSCLK
// SYSCLK 单位为Hz， nms 单位为ms，对72MHz条件下，nms <= 1864
void Delay::ms(u16 nms){
    if(!inited)init();

    SysTick->LOAD = (u32)nms * factor_ms;
    SysTick->VAL = 0;   // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开始倒数
    
    u32 temp{};
    do{
        temp = SysTick->CTRL;
    }while(SYSTICK_ENABLE(temp) && ! SYSTICK_CONTFLAG(temp));    // 等待时间到达

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  // 关闭计数器
    SysTick->VAL = 0;   // 清空计数器
}