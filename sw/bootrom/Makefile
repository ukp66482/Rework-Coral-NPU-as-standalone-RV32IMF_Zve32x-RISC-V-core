# Makefile for CoralNPU BootROM
# Builds boot.hex files for both default and highmem memory configurations

# Toolchain
CROSS_COMPILE ?= riscv64-unknown-elf-
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

# Architecture flags (include Zifencei for fence.i instruction)
ASFLAGS = -march=rv32imf_zifencei -mabi=ilp32f
LDFLAGS = -m elf32lriscv

# Linker script for BootROM
# Default: BootROM at 0x40000
# HighMem: BootROM at 0x210000

.PHONY: all clean default highmem

all: default highmem

# =============================================================================
# Default Configuration (BootROM @ 0x40000)
# =============================================================================
default: boot_default.hex

boot_default.o: boot_default.S
	$(AS) $(ASFLAGS) -o $@ $<

boot_default.elf: boot_default.o bootrom_default.ld
	$(LD) $(LDFLAGS) -T bootrom_default.ld -o $@ $<

boot_default.bin: boot_default.elf
	$(OBJCOPY) -O binary $< $@

boot_default.hex: boot_default.elf
	$(OBJCOPY) -O binary $< boot_default.bin
	od -An -tx1 -v boot_default.bin | tr -d ' \n' | fold -w32 | awk '{for(i=length; i>0; i-=2) printf "%s", substr($$0,i-1,2); print ""}' > $@

boot_default.dis: boot_default.elf
	$(OBJDUMP) -d $< > $@

# =============================================================================
# HighMem Configuration (BootROM @ 0x210000)
# =============================================================================
highmem: boot_highmem.hex

boot_highmem.o: boot_highmem.S
	$(AS) $(ASFLAGS) -o $@ $<

boot_highmem.elf: boot_highmem.o bootrom_highmem.ld
	$(LD) $(LDFLAGS) -T bootrom_highmem.ld -o $@ $<

boot_highmem.bin: boot_highmem.elf
	$(OBJCOPY) -O binary $< $@

boot_highmem.hex: boot_highmem.elf
	$(OBJCOPY) -O binary $< boot_highmem.bin
	od -An -tx1 -v boot_highmem.bin | tr -d ' \n' | fold -w32 | awk '{for(i=length; i>0; i-=2) printf "%s", substr($$0,i-1,2); print ""}' > $@

boot_highmem.dis: boot_highmem.elf
	$(OBJDUMP) -d $< > $@

# =============================================================================
# Clean
# =============================================================================
clean:
	rm -f *.o *.elf *.bin *.hex *.dis
