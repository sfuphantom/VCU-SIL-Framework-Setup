# FreeRTOS Posix Port Integration

## Overview
This directory contains the FreeRTOS Posix port files used for Linux/MacOS emulation. The Posix port replaces the ARM Cortex-R port from vcu-fw during emulation builds.

## Structure
```
FreeRTOS_port/
├── Posix/
│   ├── port.c              - Posix port implementation
│   ├── portmacro.h         - Posix port macros
│   └── utils/
│       ├── wait_for_event.c
│       └── wait_for_event.h
└── README.md               - This file
```

## Version Compatibility

**vcu-fw FreeRTOS Version**: V7.4.0/V8.1.2/V9.0.0 (mixed)
**Posix Port Version**: V10.5.1

There is a version mismatch between vcu-fw's FreeRTOS kernel and the Posix port. This integration attempts to bridge the differences through:

1. **Conditional Compilation**: Use `#ifdef SIMULATING` to select Posix port
2. **Wrapper Headers**: Bridge API differences between versions
3. **Compatibility Layer**: Handle version-specific macros and functions

## Integration Strategy

### 1. Port Selection
When `SIMULATING` is defined:
- Use Posix port files from `emulation/FreeRTOS_port/Posix/`
- Use vcu-fw's FreeRTOS kernel files (`os_*.c` from `vcu-fw/VCU/halcogen_vcu/source/`)
- Use emulation-specific `FreeRTOSConfig.h`

When `SIMULATING` is not defined:
- Use ARM Cortex-R port from vcu-fw
- Use vcu-fw's FreeRTOS kernel files
- Use vcu-fw's `FreeRTOSConfig.h`

### 2. FreeRTOSConfig.h
An emulation-specific `FreeRTOSConfig.h` is created that:
- Maintains compatibility with vcu-fw's configuration
- Adjusts settings for Posix port (e.g., removes hardware-specific features)
- Enables runtime statistics using Posix port's implementation

### 3. Include Paths
The Makefile will set include paths to:
- `emulation/FreeRTOS_port/Posix/` (for Posix port headers)
- `vcu-fw/VCU/halcogen_vcu/include/` (for FreeRTOS kernel headers)
- Emulation-specific config directory

## Key Differences to Handle

### 1. Port Macros
- vcu-fw uses `os_portmacro.h` with ARM-specific macros
- Posix port uses `portmacro.h` with POSIX-specific macros
- **Solution**: Create wrapper that conditionally includes the correct header

### 2. Runtime Statistics
- vcu-fw: Uses `ulHighFrequencyTimerTicks` and hardware timer
- Posix port: Uses `ulPortGetRunTime()` with POSIX timers
- **Solution**: Use Posix port's implementation when `SIMULATING` is defined

### 3. MPU (Memory Protection Unit)
- vcu-fw: Has MPU support (ARM Cortex-R feature)
- Posix port: No MPU support
- **Solution**: Disable MPU-related code when `SIMULATING` is defined

### 4. Critical Sections
- vcu-fw: Uses SWI (Software Interrupt) for critical sections
- Posix port: Uses pthread mutexes
- **Solution**: Posix port handles this automatically

## Build Integration

The Makefile will:
1. Include Posix port source files when `SIMULATING` is defined
2. Exclude ARM port files (`os_port.c`, `os_portasm.asm`) when `SIMULATING` is defined
3. Use emulation-specific `FreeRTOSConfig.h`
4. Link with `-lpthread` for Posix port

## Testing

After integration, verify:
- [ ] FreeRTOS scheduler starts successfully
- [ ] Tasks are created and run
- [ ] Runtime statistics work correctly
- [ ] Critical sections function properly
- [ ] No compilation errors or warnings

## Notes

- The version mismatch may cause some API incompatibilities
- Some vcu-fw features that depend on ARM-specific hardware may not work in emulation
- The Posix port uses pthreads, which may have different timing characteristics than hardware timers

