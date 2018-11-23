#include <cstdio>
#include <stdint.h>

#define vector_weak __attribute__((weak))
#define vector_default_handler __attribute__((alias("DefaultHandler")))

#ifdef __cplusplus
extern "C"
{
#endif
    extern size_t *_stack_pointer;

    void DefaultHandler(void) __attribute__((weak));
    void DefaultHandler(void)
    {
        while (1)
        {
            //simple hook
        }
    }

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

    __attribute__((section(".vectors"))) size_t *vectors[] =
        {
            (size_t *)&_stack_pointer, //FIX stack pointer
            (size_t *)&(Reset_IRQHandler),
            (size_t *)&(NMI_IRQHandler),
            (size_t *)&(HardFault_IRQHandler),
            (size_t *)&(MemManage_IRQHandler),
            (size_t *)&(BusFault_IRQHandler),
            (size_t *)&(UsageFault_IRQHandler),
            0,
            0,
            0,
            0,
            (size_t *)&(SVCall_IRQHandler),
            (size_t *)&(DebugMonitor_IRQHandler),
            0,
            (size_t *)&(PendSV_IRQHandler),
            (size_t *)&(SysTick_IRQHandler),

            (size_t *)&(WWDG_IRQHandler),
            (size_t *)&(PVD_IRQHandler),
            (size_t *)&(TAMPER_IRQHandler),
            (size_t *)&(RTC_IRQHandler),
            (size_t *)&(FLASH_IRQHandler),
            (size_t *)&(RCC_IRQHandler),
            (size_t *)&(EXTI0_IRQHandler),
            (size_t *)&(EXTI1_IRQHandler),
            (size_t *)&(EXTI2_IRQHandler),
            (size_t *)&(EXTI3_IRQHandler),
            (size_t *)&(EXTI4_IRQHandler),
            (size_t *)&(DMA1_Channel1_IRQHandler),
            (size_t *)&(DMA1_Channel2_IRQHandler),
            (size_t *)&(DMA1_Channel3_IRQHandler),
            (size_t *)&(DMA1_Channel4_IRQHandler),
            (size_t *)&(DMA1_Channel5_IRQHandler),
            (size_t *)&(DMA1_Channel6_IRQHandler),
            (size_t *)&(DMA1_Channel7_IRQHandler),
            (size_t *)&(ADC1_2_IRQHandler),
            (size_t *)&(USB_HP_CAN1_TX_IRQHandler),
            (size_t *)&(USB_LP_CAN1_RX0_IRQHandler),
            (size_t *)&(CAN1_RX1_IRQHandler),
            (size_t *)&(CAN1_SCE_IRQHandler),
            (size_t *)&(EXTI9_5_IRQHandler),
            (size_t *)&(TIM1_BRK_IRQHandler),
            (size_t *)&(TIM1_UP_IRQHandler),
            (size_t *)&(TIM1_TRG_COM_IRQHandler),
            (size_t *)&(TIM1_CC_IRQHandler),
            (size_t *)&(TIM2_IRQHandler),
            (size_t *)&(TIM3_IRQHandler),
            (size_t *)&(TIM4_IRQHandler),
            (size_t *)&(I2C1_EV_IRQHandler),
            (size_t *)&(I2C1_ER_IRQHandler),
            (size_t *)&(I2C2_EV_IRQHandler),
            (size_t *)&(I2C2_ER_IRQHandler),
            (size_t *)&(SPI1_IRQHandler),
            (size_t *)&(SPI2_IRQHandler),
            (size_t *)&(USART1_IRQHandler),
            (size_t *)&(USART2_IRQHandler),
            (size_t *)&(USART3_IRQHandler),
            (size_t *)&(EXTI15_10_IRQHandler),
            (size_t *)&(RTCAlarm_IRQHandler),
            (size_t *)&(USBWakeUp_IRQHandler)
    };

#ifdef __cplusplus
}
#endif