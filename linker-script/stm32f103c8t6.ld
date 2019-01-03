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
        * (.vectors);
    } > rom

    .text : ALIGN(4)
    {
        * (.text);
    } > rom

    .rodata : ALIGN(4)
    {
        * (.rodata);
    } > rom

    .stack ORIGIN(ram) : ALIGN(4)
    {
        . += _stack_size;
    } > ram

    .bss : ALIGN(4)
    {
        * (.bss);
    } > ram 
    
    .data : ALIGN(4)
    {
        * (.data);
    } > ram AT > rom

    _bss_start = ADDR(.bss);
    _bss_end = ADDR(.bss) + SIZEOF(.bss);
    _bss_size = SIZEOF(.bss);

    _data_vma_start = ADDR(.data);
    _data_vma_end = ADDR(.data) + SIZEOF(.data);
    _data_vma_size = SIZEOF(.data);

    _data_lma_start = LOADADDR(.data);
    _data_lma_end = LOADADDR(.data) + SIZEOF(.data);
    _data_lma_size = SIZEOF(.data);
} 