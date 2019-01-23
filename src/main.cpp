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
    if (EXTI->PR & EXTI_PR_PR1)
    {
        EXTI->PR |= EXTI_PR_PR1;
        //soft_break_point();
    }
}

void initialize_timer1()
{
    /*
    ETH-----PA12
    CH1*****PA8
    CH2-----PA9
    CH3*****PA10
    CH4-----PA11
    BKIN****PB12
    CH1N----PB13
    CH2N****PB14
    CH3N----PB15
    
    *------------*---------------------------------*---------------------------------*
    |            |        Configuration            |        GPIO configuration       |
    *------------*---------------------------------*---------------------------------*
    |            | Input capture channel x         | Input floating                  |
    |    CHx     |---------------------------------*---------------------------------*
    |            | Output compare channel x        | Alternate function push-pull    |
    *------------*---------------------------------*---------------------------------*
    |    CHxN    | Complementary output channel x  | Alternate function push-pull    |
    *------------*---------------------------------*---------------------------------*
    |    BKIN    | Break input                     | Input floating                  |
    *------------*---------------------------------*---------------------------------*
    |    ETR     | External trigger timer input    | Input floating                  |
    *------------*---------------------------------*---------------------------------*

    */
    //Настраиаемт gpio CH1-4
    GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF11);
    GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11);
    //GPIO Output mode max speed 50MHz MODE[1:0] 11, alternate function push-pull CNF[1:0] 10
    GPIOA->CRH |= GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0 | GPIO_CRH_CNF8_1;
    GPIOA->CRH |= GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_CNF9_1;
    GPIOA->CRH |= GPIO_CRH_MODE10_1 | GPIO_CRH_MODE11_0 | GPIO_CRH_CNF12_1;
    GPIOA->CRH |= GPIO_CRH_MODE11_1 | GPIO_CRH_MODE11_0 | GPIO_CRH_CNF11_1;

    //Подаем тактирование на таймер 1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    //Включаем буферизацию главных регистров, center-aligned mode, ?прерывание когда считает вниз
    //CEN включаем таймер
    TIM1->CR1 |= TIM_CR1_CMS_0; //TIM_CR1_ARPE | TIM_CR1_CMS_1 |
    //PWM mode 2
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; /// | TIM_CCMR1_OC1M_0
    TIM1->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
    //Включаем выход OC1 активный 0 | TIM_CCER_CC1P
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC4E ;
    //Период 1000
    TIM1->ARR = 1000 - 1;
    //
    // CK_PSC/240 72MHz => 300KHz
    TIM1->PSC = 72 - 1; //240-1;
    TIM1->CCR1 = 500 - 1;
    TIM1->CCR4 = 250 - 1;
    TIM1->BDTR |= TIM_BDTR_MOE;
    //Сбросим Slave mode selection в 000, тогда при CEN=1 тактироваться буде от CK_INT
    //TIM1->SMCR &= ~TIM_SMCR_SMS;
    //Запускаем
    TIM1->CR1 |= TIM_CR1_CEN;

    /*//делитель
    TIM1->PSC = 7200;
    //значение перезагрузки
    TIM1->ARR = 100;
    //коэф. заполнения
    TIM1->CCR1 = 50;
    //настроим на выход канал 4, активный уровень низкий
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;
    //разрешим использовать выводы таймера как выходы
    TIM1->BDTR |= TIM_BDTR_MOE;
    //PWM mode 1, прямой ШИМ 4 канал
    TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
    //если надо настроить первый канал, это можно сделать так
    //TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
    //считаем вверх
    TIM1->CR1 &= ~TIM_CR1_DIR;
    //выравнивание по фронту, Fast PWM
    TIM1->CR1 &= ~TIM_CR1_CMS;
    //включаем счётчик
    TIM1->CR1 |= TIM_CR1_CEN;*/

   /* RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; //такты
    TIM1->CCER = 0;                     //обнуляем CCER (выключаем каналы)
    TIM1->ARR = 100-1;                    // максимальное значение, до которого таймер ведет счет
    TIM1->PSC = 7200 - 1;               // предделитель
    TIM1->BDTR |= TIM_BDTR_MOE;         // Разрешаем вывод сигнала на выводы

    //для первого ШИМ-сигнала используем канал 1

    //задаем скважность в регистр сравнения канала (значения от 0 до TIM1->ARR)

    TIM1->CCR1 = 50-1;

    // Включаем режим канал в режим ШИМ

    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

    // Разрешаем вывод не инвертированного сигнала на ногу МК

    TIM1->CCER |= TIM_CCER_CC1E;

    // Разрешаем вывод не инвертированного сигнала на ногу МК

    //для второго ШИМ-сигнала используем канал 4

    //задаем скважность в регистр сравнения канала (значения от 0 до TIM1->ARR)

    TIM1->CCR4 = 25-1;

    // Включаем канал в режим ШИМ

    TIM1->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;

    // Разрешаем вывод не инвертированного сигнала на ногу МК

    TIM1->CCER |= TIM_CCER_CC4E;

    // Запускаем счет

    TIM1->CR1 |= TIM_CR1_CEN;*/
}
uint32_t pwm_arr[] = {0, 0, 6553, 13107, 19660, 26214, 32768,
                      39321, 45875, 52428, 58982, 65535};
int main()
{
    enableHSE();
    foo();
    //Включаем таймер 1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    //Включаем таймера 2, 3, 4
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN;
    initialize_timer1();

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
   /*0 GPIOA->CRH &= ~GPIO_CRH_CNF8;  // Сбрасываем биты CNF для бита 8. Режим 00 - Push-Pull
    GPIOA->CRH |= GPIO_CRH_CNF8_1; // Ставим режим для 8 го бита режим CNF  = 10 (альтернативная функция, Push-Pull)

    GPIOA->CRH &= ~GPIO_CRH_MODE8;                     // Сбрасываем биты MODE для бита 8
    GPIOA->CRH |= GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0; // Выставляем бит MODE для пятого пина. Режим MODE11 = Max Speed 50MHz*/

   /* RCC->CFGR &= ~(RCC_CFGR_MCO);  // Обнуляем MCO
    RCC->CFGR |= RCC_CFGR_MCO_HSE; // Выставлем для MCO сигнал с PLL/2
    SCB->SCR |= SCB_SCR_SEVONPEND;*/

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
    //NVIC_EnableIRQ(EXTI1_IRQn);
    //Выставить приоритет прерываний
    //NVIC_SetPriority(EXTI1_IRQn, 10);
    //Выбрать линию EXTI, разрешить по ней прерыване/событие
    //для PB1 выбираем 1 линию
    EXTI->IMR |= EXTI_IMR_MR1;
    //разрешить глобальные прерывания
    __enable_irq();
    //EXTI->SWIER |= EXTI_SWIER_SWIER1;
    int i = 0;
    while (1)
    {
        wait(4000);
        GPIOC->BSRR |= GPIO_BSRR_BR13;
        wait(4000);
        GPIOC->BSRR |= GPIO_BSRR_BS13;
    }
    return 0;
}
