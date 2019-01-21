#include "clock.hpp"
#include "utils.h"

void enableHSE()
{
    uint32_t counter = waitCycles;
    RCC->CR |= RCC_CR_HSEON;
    uint32_t status = ~RCC_CR_HSERDY;
    do
    {
        status = RCC->CR & RCC_CR_HSERDY;
        counter--;
    } while (status != RCC_CR_HSERDY || counter == 0);
    if (status == RCC_CR_HSERDY)
    {
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Конфигурируем Flash на 2 цикла ожидания */
        /* Это нужно потому, что Flash не может работать на высокой частоте */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
        // Выбираем в качестве источника тактового сигнал HSE и множитель 9 в PLL
        RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9; //RCC_CFGR_PLLMULL9
        // AHB (Advenced high-speed bus) делитель 1
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
        // APB1 PCLK1 = 72MHz / 2 = 36 Mhz
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
        // APB2 PCLK2 = 72MHz
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
        // Включаем PLL
        RCC->CR |= RCC_CR_PLLON;
        // Ждем готовности PLL
        counter = waitCycles;
        do
        {
            status = RCC->CR & RCC_CR_PLLRDY;
            counter--;
        } while (status != RCC_CR_PLLRDY || counter == 0);
        // Сбрасываем SW
        RCC->CFGR &= (~RCC_CFGR_SW);
        // Выбираем PLL как источник SYSCLK
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        // Ждем пока PLL установиться как источник
        counter = waitCycles;
        do
        {
            status = RCC->CFGR & RCC_CFGR_SWS_PLL;
            counter--;
        } while (status != RCC_CFGR_SWS_PLL || counter == 0);

        // Включаем CSS ?систему контроля тактирования)
        RCC->CR |= RCC_CR_CSSON;
        // Включаем gpio и блок ремапинга выводов "Alternate function IO clock enable"
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
    }
    else
    {
        //Warning!!!
        soft_break_point();
    }
}

extern "C" void NMI_IRQHandler()
{
    if(RCC->CIR & RCC_CIR_CSSF)
    {
        RCC->CIR |= RCC_CIR_CSSC;
        enableHSE(); 
    }
}