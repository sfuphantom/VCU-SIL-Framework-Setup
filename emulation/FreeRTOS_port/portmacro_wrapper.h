/*
 * portmacro_wrapper.h
 * 
 * This wrapper header conditionally includes either:
 * - vcu-fw's ARM Cortex-R port (os_portmacro.h) when building for hardware
 * - Posix port (portmacro.h) when building for emulation (SIMULATING defined)
 * 
 * This allows the same codebase to work with both ports without modification.
 */

#ifndef PORTMACRO_WRAPPER_H
#define PORTMACRO_WRAPPER_H

#ifdef SIMULATING
    /* Use Posix port for emulation */
    /* Include path assumes -Iemulation is in compiler include path */
    #include "FreeRTOS_port/Posix/portmacro.h"
    
    /* Map Posix port macros to vcu-fw naming if needed */
    /* Most macros should be compatible, but we can add mappings here if necessary */
    
#else
    /* Use vcu-fw's ARM Cortex-R port for hardware */
    /* Include path assumes vcu-fw/VCU/halcogen_vcu/include is in compiler include path */
    #include "os_portmacro.h"
    
#endif

#endif /* PORTMACRO_WRAPPER_H */

