#include "clock.h"

void enableHSE()
{
    RCC->CR |= RCC_CR_HSEON; 
    uint32_t counter = 4000; 
    while((RCC->CR & RCC_CR_HSERDY) == 0);
    if((RCC->CR & RCC_CR_HSERDY))
    {
        FLASH->ACR |= FLASH_ACR_PRFTBE;
 
    	/* Конфигурируем Flash на 2 цикла ожидания */
    	/* Это нужно потому, что Flash не может работать на высокой частоте */
 
    	FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    	FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

        // Выбираем в качестве источника тактового сигнал HSE и множитель 9 в PLL
        RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9; 
        // AHB (Advenced high-speed bus) делитель 1 
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
        // APB1 PCLK1 = 72MHz / 2 = 36 Mhz 
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
        // APB2 PCLK2 = 72MHz  
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
        // Включаем PLL
        RCC->CR |= RCC_CR_PLLON;
        // Ждем готовности PLL
        while(!(RCC->CR & RCC_CR_PLLRDY));
        // Сбрасываем SW
        RCC->CFGR &= (~RCC_CFGR_SW);
        // Выбираем PLL как источник SYSCLK
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        // Ждем пока PLL установиться как источник
        while( !(RCC->CFGR & RCC_CFGR_SWS_PLL));
    }
    else
    {
        //Warning!!!
    }
}