/* Linker script for BootROM - Default Configuration */
/* BootROM is located at 0x40000 (8KB) */

MEMORY
{
    BOOTROM (rx) : ORIGIN = 0x00040000, LENGTH = 8K
}

SECTIONS
{
    .text : {
        *(.text)
        *(.text.*)
    } > BOOTROM

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > BOOTROM

    /DISCARD/ : {
        *(.comment)
        *(.note.*)
    }
}

ENTRY(_start)
