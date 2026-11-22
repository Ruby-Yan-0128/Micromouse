/*
 * delay.c
 * BASED ON DWT_DELAY LIBRARY: https://github.com/keatis/dwt_delay
 */

#include "main.h"
#include "delay.h"

// Turns on the cycle counter, which counts up by 1 every clock tick
void Delay_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

// Delays for us microseconds
void delayMicroseconds(uint32_t us)
{
    uint32_t startTick = DWT->CYCCNT,
    delayTicks = us * (SystemCoreClock / 1000000); // Our MCU runs at 96 MHz, so each microsecond lasts 96 clock ticks

    while (DWT->CYCCNT - startTick < delayTicks);
}
