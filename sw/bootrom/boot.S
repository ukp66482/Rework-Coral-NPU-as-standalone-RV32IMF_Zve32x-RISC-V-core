
.section .text
.global _start
_start:
    /* First Stage Bootloader (FSBL) Demo */
    
    /* 1. Configuration constants */
    li s0, 0x20000000       /* Source Address (Flash/External Memory) */
    li s1, 0x00000000       /* Destination Address (ITCM) */
    li s2, 0x00001000       /* Size to copy (4KB) */
    add s2, s2, s1          /* Calculate End Address */

copy_loop:
    /* 2. Copy Loop */
    lw t0, 0(s0)            /* Load word from Source */
    sw t0, 0(s1)            /* Store word to Destination */
    
    addi s0, s0, 4          /* Increment Source Pointer */
    addi s1, s1, 4          /* Increment Dest Pointer */
    
    blt s1, s2, copy_loop   /* Continue until done */

    /* 3. Synchronization */
    fence.i                 /* Ensure Instruction Cache/Prefetch is flushed */

    /* 4. Jump to Application */
    li t0, 0x0
    jr t0                   /* Jump to ITCM Base */
