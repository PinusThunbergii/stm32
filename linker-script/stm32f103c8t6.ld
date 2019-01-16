ENTRY(Reset_IRQHandler)
_stack_size = 1K;
_stack_pointer = 0x20000000 + _stack_size; /*1k*/
MEMORY
{
    rom( rx ) : ORIGIN = 0x08000000 , LENGTH = 128K
    ram( rwx ) : ORIGIN = 0x20000000 , LENGTH = 20K
}

SECTIONS
{
    .vectors : ALIGN(4)
    {
        * (.isr_vectors);
    } > rom

    .text : ALIGN(4)
    {
        * (.text .text.*);
        * (.text.*);
    } > rom

    .rodata : ALIGN(4)
    {
        * (.rodata);
        * (.rodata.*);
    } > rom

    .init.array : ALIGN(4)
    {
        * (.init_array);
        * (.init_array.*);
    } > rom

    .fini.array : ALIGN(4)
    {
        * (.fini_array);
        * (.fini_array.*)
    } > rom

    .ARM.exidx : ALIGN(4)
    {
        * (.ARM.exidx);
        * (.ARM.exidx.*);
        * (.gnu.linkonce.armexidx.*)
    } > rom

    .ARM.extab : ALIGN(4)
    {
        * (.ARM.extab);
        * (.ARM.extab.*);
    } > rom

    .stack ORIGIN(ram) : ALIGN(4)
    {
        . += _stack_size;
    } > ram

    .bss : ALIGN(4)
    {
        * (.bss);
        * (.bss.*);
    } > ram 
    
    .data : ALIGN(4)
    {
        * (.data);
        * (.data.*);
    } > ram AT > rom

    __bss_start__ = ADDR(.bss);
    __bss_end__ = ADDR(.bss) + SIZEOF(.bss);
    __bss_size = SIZEOF(.bss);

    __data_vma_start__ = ADDR(.data);
    __data_vma_end__ = ADDR(.data) + SIZEOF(.data);
    __data_vma_size = SIZEOF(.data);

    __data_lma_start__ = LOADADDR(.data);
    __data_lma_end__ = LOADADDR(.data) + SIZEOF(.data);
    __data_lma_size = SIZEOF(.data);

    __exidx_start = LOADADDR(.ARM.exidx );
    __exidx_end = LOADADDR(.ARM.exidx) + SIZEOF(.ARM.exidx);
    __exidx_size = SIZEOF(.ARM.exidx);

    __init_array_start = LOADADDR(.init.array);
    __init_array_end = LOADADDR(.init.array) + SIZEOF(.init.array);
    __init_array_size = SIZEOF(.init.array);

    __fini_array_start = LOADADDR(.fini.array);
    __fini_array_end = LOADADDR(.fini.array) + SIZEOF(.fini.array);
    __fini_array_size = SIZEOF(.fini.array);

    __stack_start = LOADADDR(.stack );
    __stack_end = LOADADDR(.stack) + SIZEOF(.stack);
    __stack_size = SIZEOF(.stack);
} 