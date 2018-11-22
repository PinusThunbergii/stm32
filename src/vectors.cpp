#include <cstdio>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif    
extern size_t * _stack_pointer; 

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

 __attribute__ ((section(".vectors"))) size_t * vectors[] =
{
    (size_t*)&_stack_pointer, //FIX stack pointer
    (size_t*)&(Reset_IRQHandler),
    (size_t*)&(NMI_IRQHandler),
    (size_t*)&(HardFault_IRQHandler),
    (size_t*)&(MemManage_IRQHandler),
    (size_t*)&(BusFault_IRQHandler),
    (size_t*)&(UsageFault_IRQHandler),
    0,
    0,
    0,
    0,
    0,
    (size_t*)&(SVCall_IRQHandler),
    (size_t*)&(DebugMonitor_IRQHandler),
    (size_t*)&(PendSV_IRQHandler),
    (size_t*)&(SysTick_IRQHandler)
};

#ifdef __cplusplus
}
#endif  