/*
 * First Stage Bootloader (FSBL) for Default Memory Configuration
 * 
 * Memory Map (Default):
 *   ITCM:    0x00000000 - 0x00001FFF (8KB)
 *   DTCM:    0x00010000 - 0x00017FFF (32KB)
 *   CSR:     0x00030000 - 0x00030FFF (4KB)
 *   BootROM: 0x00040000 - 0x00041FFF (8KB)
 *   Flash:   0x20000000 (External)
 *
 * Flash Layout:
 *   Flash + 0x0000: Code (.text, .crt) -> ITCM (8KB)
 *   Flash + 0x2000: Data (.data)       -> DTCM (256 bytes)
 *
 * This bootloader copies:
 *   1. Code from Flash to ITCM (8KB)
 *   2. Data from Flash+0x2000 to DTCM (256 bytes)
 * Then jumps to execute from ITCM base address.
 */

.section .text
.global _start
_start:
    /*===========================================
     * PHASE 1: Copy Code to ITCM
     * Flash 0x20000000 -> ITCM 0x00000000 (8KB)
     *===========================================*/
    li s0, 0x20000000       /* Source: Flash base */
    li s1, 0x00000000       /* Destination: ITCM base */
    li s2, 0x00002000       /* Size: 8KB (full ITCM) */
    add s2, s2, s1          /* End Address = ITCM + 8KB */

copy_itcm:
    lw t0, 0(s0)            /* Load word from Flash */
    sw t0, 0(s1)            /* Store word to ITCM */
    addi s0, s0, 4          /* Increment Source */
    addi s1, s1, 4          /* Increment Dest */
    blt s1, s2, copy_itcm   /* Loop until done */

    /*===========================================
     * PHASE 2: Copy Data to DTCM
     * Flash+0x2000 -> DTCM 0x10000 (256 bytes)
     * This copies the .data section for initialized globals
     *===========================================*/
    li s0, 0x20002000       /* Source: Flash + 8KB offset */
    li s1, 0x00010000       /* Destination: DTCM base */
    li s2, 0x00010100       /* End: DTCM + 256 bytes */

copy_dtcm:
    lw t0, 0(s0)            /* Load word from Flash */
    sw t0, 0(s1)            /* Store word to DTCM */
    addi s0, s0, 4          /* Increment Source */
    addi s1, s1, 4          /* Increment Dest */
    blt s1, s2, copy_dtcm   /* Loop until done */

    /*===========================================
     * PHASE 3: Synchronization & Jump
     *===========================================*/
    fence.i                 /* Flush instruction cache */

    li t0, 0x00000000
    jr t0                   /* Jump to ITCM Base */
