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
 * This bootloader copies the application from Flash to ITCM,
 * then jumps to execute from ITCM base address.
 */

.section .text
.global _start
_start:
    /* 1. Configuration constants for Default memory layout */
    li s0, 0x20000000       /* Source Address (Flash/External Memory) */
    li s1, 0x00000000       /* Destination Address (ITCM base) */
    li s2, 0x00002000       /* Size to copy (8KB = full ITCM) */
    add s2, s2, s1          /* Calculate End Address */

copy_loop:
    /* 2. Copy Loop - 4 bytes at a time */
    lw t0, 0(s0)            /* Load word from Source */
    sw t0, 0(s1)            /* Store word to Destination */
    
    addi s0, s0, 4          /* Increment Source Pointer */
    addi s1, s1, 4          /* Increment Dest Pointer */
    
    blt s1, s2, copy_loop   /* Continue until done */

    /* 3. Synchronization */
    fence.i                 /* Ensure Instruction Cache/Prefetch is flushed */

    /* 4. Jump to Application at ITCM base */
    li t0, 0x00000000
    jr t0                   /* Jump to ITCM Base */
