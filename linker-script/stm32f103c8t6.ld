MEMORY
{
    rom(rx) : ORIGIN=0x0800000, LENGHT=128K
    ram(rwx) : ORIGIN=0x20000000, LENGHT=20K
}

SECTIONS
{
    .vectors : {
        . = ALIGN(4);
        *(.vectors*)
        . = ALIGN(4);
    } > rom
    .text : {
        *(.text*)
        . = ALIGN(4);
    }
    .bss : {

    } > ram
    .rodata : {

    } > rom
    .data : {

    }

}
