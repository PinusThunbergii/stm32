#include <stdint.h>

void Reset_IRQHandler(void) __attribute__(weak);
void NMI_IRQHandler(void);
void HardFault_IRQHandler(void);
void MemManage_IRQHandler(void);
void BusFault_IRQHandler(void);
void UsageFault_IRQHandler(void);
void SVCall_IRQHandler(void);
void DebugMonitor_IRQHandler(void);
void PendSV_IRQHandler(void);
void SysTick_IRQHandler(void);