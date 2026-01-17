OUTPUT_ARCH( "riscv" )

MEMORY {
    /* ITCM where FSBL copies the code to */
    /* HighMem config: ITCM 1MB, DTCM at 0x100000 */
    ITCM(rx) : ORIGIN = 0x00000000, LENGTH = 1024K
    DTCM(rw) : ORIGIN = 0x00100000, LENGTH = 1024K
}

SECTIONS {
    .text : {
        *(.text.startup)
        *(.text*)
    } > ITCM

    .data : {
        *(.data*)
        *(.rodata*)
        *(.sdata*)
    } > DTCM
    
    .bss : {
        *(.bss*)
        *(.sbss*)
    } > DTCM
}
