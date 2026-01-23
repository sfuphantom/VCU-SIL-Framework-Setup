# Makefile for VCU Firmware Emulation (Linux/MacOS)
# Builds vcu-fw with FreeRTOS Posix port and emulation drivers
# ONLY uses files from vcu-fw submodule (and emulation layer)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -O0 -std=c11 \
         -Wno-unused-parameter \
         -Wno-unused-variable \
         -Wno-unused-function \
         -Wno-format \
         -Wno-format-security \
         -Wno-void-pointer-to-int-cast \
         -Wno-int-to-void-pointer-cast \
         -Wno-sign-compare \
         -Wno-int-in-bool-context \
         -Wno-shift-overflow \
         -Wno-macro-redefined \
         -Wno-pointer-sign \
         -Wno-varargs \
         -Wno-return-type \
         -Wno-constant-conversion

LDFLAGS = -lpthread

# OS detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lrt
endif

# Directories
BUILD_DIR = build
VCU_FW_DIR = vcu-fw/VCU
HALCOGEN_DIR = $(VCU_FW_DIR)/halcogen_vcu
PHANTOM_DIR = $(VCU_FW_DIR)/Phantom
EMULATION_DIR = emulation

# Preprocessor definitions
DEFINES = -DSIMULATING \
          -D_POSIX_C_SOURCE=200809L \
          -D_CRT_SECURE_NO_WARNINGS \
          -DVCU_SIM_MODE

# Automatically include hardware_stubs.h for all files
# This ensures _enable_IRQ, _disable_IRQ, etc. are available to vcu-fw code
INCLUDE_FLAGS = -include $(EMULATION_DIR)/drivers/hardware_stubs.h

# Include paths - ORDER IS CRITICAL!
# Emulation headers must come FIRST so they override vcu-fw headers
# Note: FreeRTOS.h includes <halcogen_vcu/include/FreeRTOSConfig.h>
# So we need -I$(VCU_FW_DIR) to make that path resolve, but emulation wrapper comes first
INCLUDES = -I$(EMULATION_DIR)/FreeRTOS_port/headers \
           -I$(EMULATION_DIR)/FreeRTOS_port \
           -I$(EMULATION_DIR)/FreeRTOS_port/Posix \
           -I$(EMULATION_DIR)/halcogen_vcu/include \
           -I$(EMULATION_DIR)/halcogen_emulation/include \
           -I$(EMULATION_DIR)/drivers \
           -I$(EMULATION_DIR) \
           -I$(VCU_FW_DIR) \
           -I$(HALCOGEN_DIR)/include \
           -I$(HALCOGEN_DIR)/include_sim \
           -I$(PHANTOM_DIR) \
           -I$(PHANTOM_DIR)/data_structures \
           -I$(PHANTOM_DIR)/Drivers/UART \
           -I$(PHANTOM_DIR)/Drivers/DAC_SPI \
           -I$(PHANTOM_DIR)/Drivers/EEPROM \
           -I$(PHANTOM_DIR)/Drivers/RGB_LED \
           -I$(PHANTOM_DIR)/Drivers/RTD_Buzzer \
           -I$(PHANTOM_DIR)/Drivers/STATE_MACHINE \
           -I$(PHANTOM_DIR)/tasks \
           -I$(PHANTOM_DIR)/tasks/headers \
           -I$(PHANTOM_DIR)/hercules-phantom-lib/rtos-common \
           -I$(PHANTOM_DIR)/hardware/vcu_hw \
           -I$(PHANTOM_DIR)/support

# FreeRTOS kernel source files (from vcu-fw)
FREERTOS_KERNEL_SRC = $(HALCOGEN_DIR)/source/os_tasks.c \
                      $(HALCOGEN_DIR)/source/os_queue.c \
                      $(HALCOGEN_DIR)/source/os_list.c \
                      $(HALCOGEN_DIR)/source/os_timer.c \
                      $(HALCOGEN_DIR)/source/os_event_groups.c \
                      $(HALCOGEN_DIR)/source/os_croutine.c \
                      $(HALCOGEN_DIR)/source/os_heap.c

# FreeRTOS Posix port source files (for emulation)
FREERTOS_PORT_SRC = $(EMULATION_DIR)/FreeRTOS_port/Posix/port.c \
                    $(EMULATION_DIR)/FreeRTOS_port/Posix/port_wrapper.c \
                    $(EMULATION_DIR)/FreeRTOS_port/Posix/utils/wait_for_event.c

# vcu-fw application source files
# Note: vcu-fw's main.c is included via wrapper to rename main() -> vcu_fw_main()
VCU_FW_APP_SRC = $(EMULATION_DIR)/main_emulation.c \
                 $(EMULATION_DIR)/vcu_fw_main_wrapper.c \
                 $(PHANTOM_DIR)/data_structures/vcu_common.c \
                 $(PHANTOM_DIR)/data_structures/vcu_data.c \
                 $(PHANTOM_DIR)/Drivers/UART/Phantom_sci.c \
                 $(PHANTOM_DIR)/Drivers/DAC_SPI/MCP48FV_DAC_SPI.c \
                 $(PHANTOM_DIR)/Drivers/EEPROM/eeprom_driver.c \
                 $(PHANTOM_DIR)/Drivers/RGB_LED/RGB_LED.c \
                 $(PHANTOM_DIR)/Drivers/RTD_Buzzer/RTD_Buzzer.c \
                 $(PHANTOM_DIR)/Drivers/STATE_MACHINE/state_machine.c \
                 $(PHANTOM_DIR)/tasks/source/task_eeprom.c \
                 $(PHANTOM_DIR)/tasks/source/task_pedal_readings.c \
                 $(PHANTOM_DIR)/tasks/source/task_throttle.c \
                 $(PHANTOM_DIR)/tasks/source/task_watchdog.c \
                 $(PHANTOM_DIR)/hercules-phantom-lib/rtos-common/task_logger.c \
                 $(PHANTOM_DIR)/hercules-phantom-lib/rtos-common/task_event_handler.c \
                 $(PHANTOM_DIR)/hercules-phantom-lib/rtos-common/phantom_timer.c

# Emulation driver source files
EMULATION_DRIVER_SRC = $(EMULATION_DIR)/drivers/adc_emulation.c \
                       $(EMULATION_DIR)/drivers/gio_emulation.c \
                       $(EMULATION_DIR)/drivers/sci_emulation.c \
                       $(EMULATION_DIR)/drivers/rti_emulation.c \
                       $(EMULATION_DIR)/drivers/het_emulation.c \
                       $(EMULATION_DIR)/drivers/hardware_stubs.c

# All source files - ONLY from vcu-fw and emulation layer
ALL_SRC = $(FREERTOS_KERNEL_SRC) \
          $(FREERTOS_PORT_SRC) \
          $(VCU_FW_APP_SRC) \
          $(EMULATION_DRIVER_SRC)

# Object files
OBJ = $(ALL_SRC:%.c=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BUILD_DIR)/vcu-firmware-emulation

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJ)
	@echo "Linking $(TARGET)..."
	@mkdir -p $(@D)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile C files to object files
$(BUILD_DIR)/%.o: %.c
	@echo "Compiling $<..."
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDE_FLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Help target
help:
	@echo "VCU Firmware Emulation Makefile"
	@echo ""
	@echo "This Makefile ONLY uses files from vcu-fw submodule (and emulation layer)"
	@echo ""
	@echo "Targets:"
	@echo "  make          - Build the emulation executable"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make run      - Build and run the executable"
	@echo "  make help     - Show this help message"
	@echo ""
	@echo "Output: $(TARGET)"

.PHONY: all clean run help
