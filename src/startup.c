#include <stm32f10x.h>

extern uint32_t _bss_start[];
extern uint32_t _bss_end[];
extern uint32_t _bss_size[];

extern uint32_t _data_vma_start[];
extern uint32_t _data_vma_end[];
extern uint32_t _data_vma_size[];

extern uint32_t _data_lma_start[];
extern uint32_t _data_lma_end[];
extern uint32_t _data_lma_size[];

extern void main();

void Reset_IRQHandler(void)
{
    for (uint32_t i = 0; i < _bss_size; i++)
    {
        _bss_start[i] = 0;
    }
     for (uint32_t i = 0; i < _data_vma_size; i++)
    {
        _data_vma_start[i] = _data_lma_start[i];
    }
    main();
    while(1)
    {

    }
}

void HardFault_IRQHandler(void)
{
    
}

