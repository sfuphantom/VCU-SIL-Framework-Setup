/*
 * os_portable.h - Emulation wrapper for vcu-fw's os_portable.h
 * 
 * This file replaces vcu-fw's os_portable.h for emulation builds.
 * It includes the Posix port's portmacro.h instead of the ARM port's os_portmacro.h.
 * 
 * NOTE: This file must be placed in an include path that comes BEFORE 
 * vcu-fw/VCU/halcogen_vcu/include in the compiler's include search path.
 * 
 * For hardware builds, this file should not be used - vcu-fw's original
 * os_portable.h will be included directly.
 */

#ifndef PORTABLE_H
#define PORTABLE_H

#ifdef SIMULATING
    /* For emulation: Include Posix port's portmacro.h */
    /* Include path assumes -Iemulation is in compiler include path */
    #include "FreeRTOS_port/Posix/portmacro.h"
    
    /* The Posix portmacro.h defines:
     * - portENTER_CRITICAL, portEXIT_CRITICAL (so os_portable.h won't try to include os_portmacro.h)
     * - portDISABLE_INTERRUPTS, portENABLE_INTERRUPTS
     * - portYIELD, portYIELD_FROM_ISR
     * - All type definitions (StackType_t, BaseType_t, TickType_t, etc.)
     * - portBYTE_ALIGNMENT
     */
    
    /* Define portBYTE_ALIGNMENT_MASK if needed (from vcu-fw's os_portable.h) */
    #if portBYTE_ALIGNMENT == 32
        #define portBYTE_ALIGNMENT_MASK ( 0x001f )
    #elif portBYTE_ALIGNMENT == 16
        #define portBYTE_ALIGNMENT_MASK ( 0x000f )
    #elif portBYTE_ALIGNMENT == 8
        #define portBYTE_ALIGNMENT_MASK ( 0x0007 )
    #elif portBYTE_ALIGNMENT == 4
        #define portBYTE_ALIGNMENT_MASK ( 0x0003 )
    #elif portBYTE_ALIGNMENT == 2
        #define portBYTE_ALIGNMENT_MASK ( 0x0001 )
    #elif portBYTE_ALIGNMENT == 1
        #define portBYTE_ALIGNMENT_MASK ( 0x0000 )
    #else
        #error "Invalid portBYTE_ALIGNMENT"
    #endif
    
    /* Additional portable layer definitions that might be needed */
    /* Most are already in portmacro.h, but we ensure compatibility here */
    
#else
    /* For hardware builds, this file should not be included */
    /* The build system should use vcu-fw's original os_portable.h */
    #error "This os_portable.h wrapper is for emulation only. Use vcu-fw's original for hardware builds."
#endif

#endif /* PORTABLE_H */

