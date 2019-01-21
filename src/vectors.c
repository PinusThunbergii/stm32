//#include <cstdio>
#include <stdint.h>
#include "utils.h"
#define vector_weak __attribute__((weak))
#define vector_default_handler __attribute__((alias("DefaultHandler")))
typedef void (* const FunctionPointer)(void);

#ifdef __cplusplus
extern "C"
{
#endif
    extern uint32_t *_stack_pointer;


    void DefaultHandler(void)
    {
        while (1)
        {
            //simple hook
            soft_break_point();
        }
    }
    __attribute__ ((noreturn))
    vector_weak vector_default_handler void Reset_IRQHandler(void);
    vector_weak vector_default_handler void NMI_IRQHandler(void);
    vector_weak vector_default_handler void HardFault_IRQHandler(void);
    vector_weak vector_default_handler void MemManage_IRQHandler(void);
    vector_weak vector_default_handler void BusFault_IRQHandler(void);
    vector_weak vector_default_handler void UsageFault_IRQHandler(void);
    vector_weak vector_default_handler void SVCall_IRQHandler(void);
    vector_weak vector_default_handler void DebugMonitor_IRQHandler(void);
    vector_weak vector_default_handler void PendSV_IRQHandler(void);
    vector_weak vector_default_handler void SysTick_IRQHandler(void);

    vector_weak vector_default_handler void WWDG_IRQHandler(void);
    vector_weak vector_default_handler void PVD_IRQHandler(void);
    vector_weak vector_default_handler void TAMPER_IRQHandler(void);
    vector_weak vector_default_handler void RTC_IRQHandler(void);
    vector_weak vector_default_handler void FLASH_IRQHandler(void);
    vector_weak vector_default_handler void RCC_IRQHandler(void);
    vector_weak vector_default_handler void EXTI0_IRQHandler(void);
    vector_weak vector_default_handler void EXTI1_IRQHandler(void);
    vector_weak vector_default_handler void EXTI2_IRQHandler(void);
    vector_weak vector_default_handler void EXTI3_IRQHandler(void);
    vector_weak vector_default_handler void EXTI4_IRQHandler(void);
    vector_weak vector_default_handler void DMA1_Channel1_IRQHandler(void);
    vector_weak vector_default_handler void DMA1_Channel2_IRQHandler(void);
    vector_weak vector_default_handler void DMA1_Channel3_IRQHandler(void);
    vector_weak vector_default_handler void DMA1_Channel4_IRQHandler(void);
    vector_weak vector_default_handler void DMA1_Channel5_IRQHandler(void);
    vector_weak vector_default_handler void DMA1_Channel6_IRQHandler(void);
    vector_weak vector_default_handler void DMA1_Channel7_IRQHandler(void);
    vector_weak vector_default_handler void ADC1_2_IRQHandler(void);
    vector_weak vector_default_handler void USB_HP_CAN1_TX_IRQHandler(void);
    vector_weak vector_default_handler void USB_LP_CAN1_RX0_IRQHandler(void);
    vector_weak vector_default_handler void CAN1_RX1_IRQHandler(void);
    vector_weak vector_default_handler void CAN1_SCE_IRQHandler(void);
    vector_weak vector_default_handler void EXTI9_5_IRQHandler(void);
    vector_weak vector_default_handler void TIM1_BRK_IRQHandler(void);
    vector_weak vector_default_handler void TIM1_UP_IRQHandler(void);
    vector_weak vector_default_handler void TIM1_TRG_COM_IRQHandler(void);
    vector_weak vector_default_handler void TIM1_CC_IRQHandler(void);
    vector_weak vector_default_handler void TIM2_IRQHandler(void);
    vector_weak vector_default_handler void TIM3_IRQHandler(void);
    vector_weak vector_default_handler void TIM4_IRQHandler(void);
    vector_weak vector_default_handler void I2C1_EV_IRQHandler(void);
    vector_weak vector_default_handler void I2C1_ER_IRQHandler(void);
    vector_weak vector_default_handler void I2C2_EV_IRQHandler(void);
    vector_weak vector_default_handler void I2C2_ER_IRQHandler(void);
    vector_weak vector_default_handler void SPI1_IRQHandler(void);
    vector_weak vector_default_handler void SPI2_IRQHandler(void);
    vector_weak vector_default_handler void USART1_IRQHandler(void);
    vector_weak vector_default_handler void USART2_IRQHandler(void);
    vector_weak vector_default_handler void USART3_IRQHandler(void);
    vector_weak vector_default_handler void EXTI15_10_IRQHandler(void);
    vector_weak vector_default_handler void RTCAlarm_IRQHandler(void);
    vector_weak vector_default_handler void USBWakeUp_IRQHandler(void);

    __attribute__((section(".isr_vectors"))) FunctionPointer vectors[] =
        {
            (FunctionPointer)&_stack_pointer, //FIX stack pointer
            (Reset_IRQHandler),
            (NMI_IRQHandler),
            (HardFault_IRQHandler),
            (MemManage_IRQHandler),
            (BusFault_IRQHandler),
            (UsageFault_IRQHandler),
            0,
            0,
            0,
            0,
            (SVCall_IRQHandler),
            (DebugMonitor_IRQHandler),
            0,
            (PendSV_IRQHandler),
            (SysTick_IRQHandler),

            (WWDG_IRQHandler),
            (PVD_IRQHandler),
            (TAMPER_IRQHandler),
            (RTC_IRQHandler),
            (FLASH_IRQHandler),
            (RCC_IRQHandler),
            (EXTI0_IRQHandler),
            (EXTI1_IRQHandler),
            (EXTI2_IRQHandler),
            (EXTI3_IRQHandler),
            (EXTI4_IRQHandler),
            (DMA1_Channel1_IRQHandler),
            (DMA1_Channel2_IRQHandler),
            (DMA1_Channel3_IRQHandler),
            (DMA1_Channel4_IRQHandler),
            (DMA1_Channel5_IRQHandler),
            (DMA1_Channel6_IRQHandler),
            (DMA1_Channel7_IRQHandler),
            (ADC1_2_IRQHandler),
            (USB_HP_CAN1_TX_IRQHandler),
            (USB_LP_CAN1_RX0_IRQHandler),
            (CAN1_RX1_IRQHandler),
            (CAN1_SCE_IRQHandler),
            (EXTI9_5_IRQHandler),
            (TIM1_BRK_IRQHandler),
            (TIM1_UP_IRQHandler),
            (TIM1_TRG_COM_IRQHandler),
            (TIM1_CC_IRQHandler),
            (TIM2_IRQHandler),
            (TIM3_IRQHandler),
            (TIM4_IRQHandler),
            (I2C1_EV_IRQHandler),
            (I2C1_ER_IRQHandler),
            (I2C2_EV_IRQHandler),
            (I2C2_ER_IRQHandler),
            (SPI1_IRQHandler),
            (SPI2_IRQHandler),
            (USART1_IRQHandler),
            (USART2_IRQHandler),
            (USART3_IRQHandler),
            (EXTI15_10_IRQHandler),
            (RTCAlarm_IRQHandler),
            (USBWakeUp_IRQHandler)
    };

#ifdef __cplusplus
}
#endif