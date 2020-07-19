#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Simple makefile for a build system that supports cortex-M0+ target arch and
# x86_64 host arch.
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#	<FILE>.i - generate <FILE>.i preprocessed output for each given *.c source file
#	<FILE>.asm - generate <FILE>.asm with assembly output for each given
#	*.c source file and for the final output executable
#	<FILE>.o - generate <FILE>.o object file for each given *.c source file
#	compile-all - compile all object files, but DO NOT link
#	build - compile all object files and link into a final executable
#	clean - remove all generated files
#	all - same as build, but print a final executable memory size info
#
# Platform Overrides:
#	CPU - ARM Cortex Architecture (cortex-m0plus, cortex-m4)
#	ARCH - ARM Architecture (armvxx)
#	ISA - Instruction Set Architecture (thumb)
#	FLOAT_ABI - Whether to use hardware instructions or software library \
#				functions for FPO (hard)
#	FPU - Target FPU architecture, that is the floating-point hardware \
#		  available on the target.
#	SPECS - Specs file to give to the linker (nosys.specs, nano.specs)
#------------------------------------------------------------------------------
include sources.mk
# Platform Overrides
PLATFORM ?= HOST
TARGET ?= c1m2
VERBOSE ?=
COURSE1 ?=

# Architectures Specific Flags
LINKER_FILE ?= msp432p401r.lds
CPU ?= cortex-m4
ISA ?= thumb
ARCH ?= armv7e-m
FLOAT_ABI ?= hard
FPU ?= fpv4-sp-d16
SPECS ?= nosys.specs

# Generic flags
CFLAGS := -Wall -Werror -g -O0 -std=c99
CPPFLAGS := -D$(PLATFORM) $(INCLUDES)
LDFLAGS := -Wl,-Map=$(TARGET).map
DEPFLAGS = -M -MP

# Add VERBOSE and COURSE1 macros if set
ifneq ($(VERBOSE),)
	CPPFLAGS += -D$(VERBOSE)
endif

ifneq ($(COURSE1),)
	CPPFLAGS += -D$(COURSE1)
endif

# Compiler Flags and Defines
ifeq ($(PLATFORM),HOST)
CC := $(shell which gcc)
LD := $(shell which ld)
SIZE := $(shell which size)
OBJDUMP := $(shell which objdump)

else ifeq ($(PLATFORM),MSP432)
CC := $(shell which arm-none-eabi-gcc)
LD := $(shell which arm-none-eabi-ld)
CFLAGS += \
	-mcpu=$(CPU) \
	-m$(ISA) \
	-march=$(ARCH) \
	-mfloat-abi=$(FLOAT_ABI) \
	-mfpu=$(FPU) \
	--specs=$(SPECS)
LDFLAGS += -T $(LINKER_FILE)
SIZE := $(shell which arm-none-eabi-size)
OBJDUMP := $(shell which arm-none-eabi-objdump)
OBJDUMP += -m $(ARCH)

else
$(error Platform provided is not supported in this Build System)
endif

ifeq ($(CC)$(LD)$(SIZE),)
$(error Can not find toolchain for $(PLATFORM))
endif
OBJS := $(SOURCES:.c=.o)
# Implicit rules
%.i : %.c
	@echo "Preprocessing $<..."
	$(CC) -E $(CPPFLAGS) $< -o $@
	@echo ""

%.asm : %.c
	@echo "Translating $< to $@..."
	$(CC) -S $(CFLAGS) $(CPPFLAGS) $< -o $@
	@echo ""

$(TARGET).asm : $(TARGET).out
	@echo "Translating $< to $@..."
	$(OBJDUMP) -dwz --source-comment='>>> ' $< > $(TARGET).asm
	@echo ""

%.o : %.c
	@echo "Compiling $< to $@..."
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	@echo ""

%.d : %.c
	@echo "Generating dependencies for $@..."
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $< -o $@
	@echo ""

# Just compile
.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: build
build: $(TARGET).out

$(TARGET).out: $(OBJS)
	@echo "Linking $^..."
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo ""

.PHONY: all
all: build
	@echo ""
	@echo "============================"
	@echo "Successfully built $(TARGET).out:"
	$(SIZE) $(TARGET).out

.PHONY: clean
clean:
	rm -rf $(TARGET).out *.asm *.map src/*.o src/*.i src/*.asm src/*.d \
		src/$(TARGET).out src/$(TARGET).map
	
