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
    .vectors : {
        . = ALIGN(4);
        *(.vectors)
        . = ALIGN(4);
    } > rom

    
    .text : {
        . = ALIGN(4);
        *(.text)
        . = ALIGN(4);
    } > rom

    .rodata : {
        . = ALIGN(4);
        *(.rodata)
        . = ALIGN(4);
    } > rom

    .stack ORIGIN(ram) : {
        . += _stack_size;
        . = ALIGN(4);
    } > ram

    .bss : {
        . = ALIGN(4);
        _bss_start = .;
        *(.bss)
        . = ALIGN(4);
        _bss_end = .;
    } > ram 
    
    .data : {
        . = ALIGN(4);
        _data_start = .;
        *(.data)
        . = ALIGN(4);
        _data_end = .;

    } > ram AT > rom
   _data_l = LOADADDR(.data);
} 