#include <stm32f10x.h>

extern uint32_t __bss_start__[];
extern uint32_t __bss_end__[];
extern uint32_t __bss_size__[];

extern uint32_t __data_vma_start__[];
extern uint32_t __data_vma_end__[];
extern uint32_t __data_vma_size__[];

extern uint32_t __data_lma_start__[];
extern uint32_t __data_lma_end__[];
extern uint32_t __data_lma_size__[];

typedef void (*functionPointer)(void);
extern functionPointer __init_array_start[0];
extern functionPointer __init_array_end[0];
extern uint32_t __init_array_size[];

extern functionPointer __fini_array_start[];
extern functionPointer __fini_array_end[];
extern uint32_t __fini_array_size[];

extern uint32_t __stack_start[];
extern uint32_t __stack_end[];
extern uint32_t __stack_size[];

extern void main();
void zero_bss();
void copy_data();



void zero_bss()
{
    uint32_t *dst = __bss_start__;
    while(dst < &__bss_end__)
    {
        *(dst++) = (uint32_t)0u;
    }
}

void copy_data()
{
    uint32_t *src = __data_lma_start__;
    uint32_t *dst = __data_vma_start__;
    while(dst < &__data_vma_end__)
    {
        *(dst++) = *(src++);
    }
}

void call_constructors()
{
    functionPointer *func = __init_array_start;
    while(func < __init_array_end)
    {
        (*func)();
        func++;
    }
}

void call_destructors()
{
    functionPointer *func = __fini_array_start;
    while(func < __fini_array_end)
    {
        (*func)();
        func++;
    }
}

void Reset_IRQHandler(void)
{

    zero_bss();
    copy_data();
    call_constructors();
    main();
    call_destructors();
    while(1)
    {

    }
}

void HardFault_IRQHandler(void)
{
    while(1)
    {

    }
}

