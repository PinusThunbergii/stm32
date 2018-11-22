/*ENTRY(Reset_IRQHandler)*/
_stack_size = 1K;
_stack_pointer = 0x20000000 + _stack_size; /*1k*/
MEMORY
{
    rom( rx ) : ORIGIN = 0x08000000 , LENGTH = 128K
    ram( rwx ) : ORIGIN = 0x20000000 , LENGTH = 20K
}
/*lddfssssf*/
SECTIONS
{
    .vectors : {
        *(.vectors*)
    } > rom
    . += 64;
    . = ALIGN(4);
    .text : {
        _text_begin = .;
        *(.text*)
        _text_end = .;
    } > rom
    . = ALIGN(4);
    .bss : {
        *(.bss*)
    } > ram 
    . = ALIGN(4);
    .rodata : {
        *(.rodata*)
    } > rom
    . = ALIGN(4);
    .data : {
        *(.data*)
    } > ram AT > rom
    . = ALIGN(4);
} 