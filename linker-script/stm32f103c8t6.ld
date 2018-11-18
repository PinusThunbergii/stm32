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
    . = ALIGN(4);
    .text : {
        *(.text*)
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