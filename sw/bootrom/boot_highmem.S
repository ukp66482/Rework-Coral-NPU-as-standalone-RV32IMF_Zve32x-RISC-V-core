/*
 * First Stage Bootloader (FSBL) for HighMem Memory Configuration
 * 
 * Memory Map (HighMem):
 *   ITCM:    0x00000000 - 0x000FFFFF (1024KB = 1MB)
 *   DTCM:    0x00100000 - 0x001FFFFF (1024KB = 1MB)
 *   CSR:     0x00200000 - 0x00200FFF (4KB)
 *   BootROM: 0x00210000 - 0x00211FFF (8KB)
 *   Flash:   0x20000000 (External)
 *
 * This bootloader copies the application from Flash to ITCM,
 * then jumps to execute from ITCM base address.
 *
 * Note: Copying full 1MB would take too long. We copy a reasonable
 * amount (64KB) which should cover most applications. For larger
 * applications, consider implementing a header-based size or
 * second-stage loader.
 */

.section .text
.global _start
_start:
    /* 1. Configuration constants for HighMem memory layout */
    li s0, 0x20000000       /* Source Address (Flash/External Memory) */
    li s1, 0x00000000       /* Destination Address (ITCM base) */
    li s2, 0x00010000       /* Size to copy (64KB - reasonable default) */
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
