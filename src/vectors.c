#include <stdint.h>

extern uint32_t stack_pointer; 

void DefaultHandler(void) __attribute__((weak));
void DefaultHandler(void)
{
    while (1)
    {
        //simple hook
    }
}

void Reset_IRQHandler(void)        __attribute__((weak, alias("DefaultHandler")));
void NMI_IRQHandler(void)          __attribute__((weak, alias("DefaultHandler")));
void HardFault_IRQHandler(void)    __attribute__((weak, alias("DefaultHandler")));
void MemManage_IRQHandler(void)    __attribute__((weak, alias("DefaultHandler")));
void BusFault_IRQHandler(void)     __attribute__((weak, alias("DefaultHandler")));
void UsageFault_IRQHandler(void)   __attribute__((weak, alias("DefaultHandler")));
void SVCall_IRQHandler(void)       __attribute__((weak, alias("DefaultHandler")));
void DebugMonitor_IRQHandler(void) __attribute__((weak, alias("DefaultHandler")));
void PendSV_IRQHandler(void)       __attribute__((weak, alias("DefaultHandler")));
void SysTick_IRQHandler(void)      __attribute__((weak, alias("DefaultHandler")));

 __attribute__ ((section(".vectors"))) uint32_t  vectors[] =
{
    0, //FIX stack pointer
    &(Reset_IRQHandler),
    &(NMI_IRQHandler),
    &(HardFault_IRQHandler),
    &(MemManage_IRQHandler),
    &(BusFault_IRQHandler),
    &(UsageFault_IRQHandler),
    0,
    0,
    0,
    0,
    0,
    &(SVCall_IRQHandler),
    &(DebugMonitor_IRQHandler),
    &(PendSV_IRQHandler),
    &(SysTick_IRQHandler)
};

