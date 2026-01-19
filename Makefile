# Makefile for VCU-SIL-Framework-Setup
# Compiles on Mac/Linux using GCC/Clang with FreeRTOS Posix port

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g -O0 -std=c11
LDFLAGS = -lpthread

# Detect OS and adjust flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lrt
endif

# Directories
BUILD_DIR = build
DEBUG_DIR = Debug

# Include directories (matching WIN32.vcxproj)
INCLUDES = -IFreeRTOS/Source/include \
           -IFreeRTOS/Source/portable/ThirdParty/GCC/Posix \
           -IFreeRTOS/Common/Include \
           -IFreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/Include \
           -ITrace_Recorder_Configuration \
           -Idata_structures \
           -Itasks/headers \
           -Itasks/source \
           -Ihercules-phantom-lib/rtos-common \
           -IDrivers/UART \
           -IDrivers/STATE_MACHINE \
           -Ihardware/vcu_hw \
           -Ihalcogen_vcu/include_sim \
           -Itasks \
           -IDrivers/DAC_SPI \
           -Ihalcogen_vcu/include_sim_source \
           -Isupport

# Preprocessor definitions (matching WIN32.vcxproj, adapted for Posix)
DEFINES = -D_POSIX_C_SOURCE=200809L \
          -D_CRT_SECURE_NO_WARNINGS

# Source files (matching WIN32.vcxproj)
FREERTOS_SRC = FreeRTOS/Source/event_groups.c \
               FreeRTOS/Source/portable/MemMang/heap_5.c \
               FreeRTOS/Source/stream_buffer.c \
               FreeRTOS/Source/timers.c \
               FreeRTOS/Source/list.c \
               FreeRTOS/Source/portable/ThirdParty/GCC/Posix/port.c \
               FreeRTOS/Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c \
               FreeRTOS/Source/queue.c \
               FreeRTOS/Source/tasks.c

FREERTOS_PLUS_SRC = FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/trcKernelPort.c \
                    FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace/trcSnapshotRecorder.c

FREERTOS_DEMO_SRC = FreeRTOS/Common/Minimal/AbortDelay.c \
                    FreeRTOS/Common/Minimal/BlockQ.c \
                    FreeRTOS/Common/Minimal/blocktim.c \
                    FreeRTOS/Common/Minimal/countsem.c \
                    FreeRTOS/Common/Minimal/death.c \
                    FreeRTOS/Common/Minimal/dynamic.c \
                    FreeRTOS/Common/Minimal/EventGroupsDemo.c \
                    FreeRTOS/Common/Minimal/flop.c \
                    FreeRTOS/Common/Minimal/GenQTest.c \
                    FreeRTOS/Common/Minimal/integer.c \
                    FreeRTOS/Common/Minimal/IntSemTest.c \
                    FreeRTOS/Common/Minimal/MessageBufferAMP.c \
                    FreeRTOS/Common/Minimal/PollQ.c \
                    FreeRTOS/Common/Minimal/QPeek.c \
                    FreeRTOS/Common/Minimal/QueueOverwrite.c \
                    FreeRTOS/Common/Minimal/QueueSet.c \
                    FreeRTOS/Common/Minimal/QueueSetPolling.c \
                    FreeRTOS/Common/Minimal/recmutex.c \
                    FreeRTOS/Common/Minimal/semtest.c \
                    FreeRTOS/Common/Minimal/StaticAllocation.c \
                    FreeRTOS/Common/Minimal/MessageBufferDemo.c \
                    FreeRTOS/Common/Minimal/StreamBufferDemo.c \
                    FreeRTOS/Common/Minimal/StreamBufferInterrupt.c \
                    FreeRTOS/Common/Minimal/TaskNotify.c \
                    FreeRTOS/Common/Minimal/TaskNotifyArray.c \
                    FreeRTOS/Common/Minimal/TimerDemo.c

PROJECT_SRC = data_structures/vcu_common.c \
              data_structures/vcu_data.c \
              Drivers/DAC_SPI/MCP48FV_DAC_SPI.c \
              Drivers/STATE_MACHINE/state_machine.c \
              Drivers/UART/Phantom_sci.c \
              hercules-phantom-lib/rtos-common/phantom_timer.c \
              hercules-phantom-lib/rtos-common/task_event_handler.c \
              hercules-phantom-lib/rtos-common/task_logger.c \
              main.c \
              main_blinky.c \
              main_full.c \
              Run-time-stats-utils.c \
              support/IPC.c \
              tasks/source/task_eeprom.c \
              tasks/source/task_pedal_readings.c \
              tasks/source/task_throttle.c \
              tasks/source/task_watchdog.c

ALL_SRC = $(FREERTOS_SRC) $(FREERTOS_PLUS_SRC) $(FREERTOS_DEMO_SRC) $(PROJECT_SRC)

# Object files
OBJS = $(ALL_SRC:%.c=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BUILD_DIR)/VCU-firmware-local

# Default target
all: $(TARGET)

# Create build directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/FreeRTOS/Source/portable/ThirdParty/GCC/Posix/utils
	mkdir -p $(BUILD_DIR)/FreeRTOS/Source/portable/MemMang
	mkdir -p $(BUILD_DIR)/FreeRTOS/Common/Minimal
	mkdir -p $(BUILD_DIR)/FreeRTOS-Plus/Source/FreeRTOS-Plus-Trace
	mkdir -p $(BUILD_DIR)/data_structures
	mkdir -p $(BUILD_DIR)/Drivers/DAC_SPI
	mkdir -p $(BUILD_DIR)/Drivers/STATE_MACHINE
	mkdir -p $(BUILD_DIR)/Drivers/UART
	mkdir -p $(BUILD_DIR)/hercules-phantom-lib/rtos-common
	mkdir -p $(BUILD_DIR)/support
	mkdir -p $(BUILD_DIR)/tasks/source

# Compile source files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

# Link executable
$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(DEBUG_DIR)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run

