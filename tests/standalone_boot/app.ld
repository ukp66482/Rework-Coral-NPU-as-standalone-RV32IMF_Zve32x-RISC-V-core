OUTPUT_ARCH( "riscv" )

MEMORY {
    /* ITCM where FSBL copies the code to */
    ITCM(rx) : ORIGIN = 0x00000000, LENGTH = 32K
    DTCM(rw) : ORIGIN = 0x00010000, LENGTH = 32K
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
