#include <stdint.h>

// Simple Mailbox to verify execution
#define MAILBOX_BASE 0x30000
volatile uint32_t* const mailbox = (volatile uint32_t*)MAILBOX_BASE;

int main() {
    // Write signature to mailbox
    mailbox[0] = 0xCAFEFEED;
    mailbox[1] = 0x12345678;
    
    // Write to verify BSS/Data clearing (optional, simplified here)
    
    // Halt (WFI loop or special CSR if needed)
    while(1) {
        asm volatile ("wfi");
    }
    return 0;
}
