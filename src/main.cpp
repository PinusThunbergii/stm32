#include "clock.hpp"
#include <vector>
#include "utils.h"
#include "test_class.hpp"

char *global_str = "I`m global!!!";
int integer_global = 0x30313233;
int none_init_int;
void foo()
{
    char str[40] = "Hello world!!!";
    str[12] = 'G';
}

void wait(int times)
{
    for (; times > 0; times--)
    {
        __asm__("NOP");
    }
}

TestClass global_class_with_static_item_0(5);
TestClass global_class_with_static_item_1(2);
TestClass global_class_with_static_item_2(6);

extern "C" void EXTI1_IRQHandler()
{
    if(EXTI->PR & EXTI_PR_PR1)
    {
        EXTI->PR |= EXTI_PR_PR1;
        //soft_break_point();
    }
}

int main()
{
    enableHSE();
    foo();
    //Включаем таймер 1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    //Включаем таймера 2, 3, 4
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN;

    /*global_class_with_static_item.setI(55);
    std::vector<int> vec(0);
    vec.push_back(6);*/
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOA->CRH |= GPIO_CRH_CNF13_1; 
    GPIOC->CRH &= ~GPIO_CRH_MODE13;
    GPIOC->CRH |= GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1;
    //Выключаем jtag и овобождаем pa15, pb4, pb3
    AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    //Пробуем EVENTOUT и SEV Send event
    AFIO->EVCR |= AFIO_EVCR_PORT_PC | AFIO_EVCR_PIN_PX13 | AFIO_EVCR_EVOE;
    //
    GPIOA->CRH &= ~GPIO_CRH_CNF8;  // Сбрасываем биты CNF для бита 8. Режим 00 - Push-Pull
    GPIOA->CRH |= GPIO_CRH_CNF8_1; // Ставим режим для 8 го бита режим CNF  = 10 (альтернативная функция, Push-Pull)

    GPIOA->CRH &= ~GPIO_CRH_MODE8;                     // Сбрасываем биты MODE для бита 8
    GPIOA->CRH |= GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0; // Выставляем бит MODE для пятого пина. Режим MODE11 = Max Speed 50MHz

    RCC->CFGR &= ~(RCC_CFGR_MCO);  // Обнуляем MCO
    RCC->CFGR |= RCC_CFGR_MCO_HSE; // Выставлем для MCO сигнал с PLL/2
    SCB->SCR |= SCB_SCR_SEVONPEND; 

    GPIOB->CRL &= ~GPIO_CRL_CNF1;
    GPIOB->CRL &= ~(GPIO_CRL_MODE1_1 | GPIO_CRL_MODE1_0);
    GPIOB->CRL |= GPIO_CRL_CNF1_1;
    GPIOB->BSRR |= GPIO_BSRR_BR1;

    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRL &= ~(GPIO_CRL_MODE1_1 | GPIO_CRL_MODE1_0);
    GPIOA->CRL |= GPIO_CRL_CNF1_1;
    GPIOA->BSRR |= GPIO_BSRR_BR1;
    /*Настройка прерывания*/
     
    //Устанавливаем триггер на линию
    EXTI->RTSR |= EXTI_RTSR_TR1;
    //Потом в обработчике нужно "~сбросить"(выставить 1) pending bit EXTI->PR
    
    //Теперь надо к контролеру внешних прерываний подключить порт B
    //EXTICR[0] == EXTICR1 обслуживает линии EXTI c 0 по 3
    AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PB;

    //Надо разрешить прерывание в NVIC
    NVIC_EnableIRQ(EXTI1_IRQn);
    //Выставить приоритет прерываний
    //NVIC_SetPriority(EXTI1_IRQn, 10);
    //Выбрать линию EXTI, разрешить по ней прерыване/событие
    //для PB1 выбираем 1 линию
    EXTI->IMR |= EXTI_IMR_MR1;
    //разрешить глобальные прерывания
    __enable_irq();
    //EXTI->SWIER |= EXTI_SWIER_SWIER1;
    while (1)
    {
        wait(400000);
        GPIOC->BSRR |= GPIO_BSRR_BR13;
        wait(400000);
        GPIOC->BSRR |= GPIO_BSRR_BS13;
    }
    return 0;
}
