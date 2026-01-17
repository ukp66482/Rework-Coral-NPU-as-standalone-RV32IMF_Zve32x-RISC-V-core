/* Linker script for BootROM - HighMem Configuration */
/* BootROM is located at 0x210000 (8KB) */

MEMORY
{
    BOOTROM (rx) : ORIGIN = 0x00210000, LENGTH = 8K
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
