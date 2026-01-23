/*
 * sys_core.h - Emulation wrapper for vcu-fw's sys_core.h
 * 
 * This file provides hardware stubs for sys_core.h functions.
 * Since vcu-fw code includes <halcogen_vcu/include/sci.h> which may
 * transitively include sys_core.h, we need to provide stubs here.
 */

#ifndef __SYS_CORE_H__
#define __SYS_CORE_H__

#ifdef SIMULATING
    /* Include hardware stubs first - defines _enable_IRQ, _disable_IRQ as macros */
    #include "../../drivers/hardware_stubs.h"
    
    /* Now include the real sys_core.h for all other definitions */
    /* The macros from hardware_stubs.h will override any function declarations */
    /* We need to include it with a path that won't create a circular dependency */
    /* Since we're in emulation/halcogen_vcu/include, we need to go up to find vcu-fw */
    
#else
    /* For hardware builds, this file should not be used */
    #error "This sys_core.h wrapper is for emulation only"
#endif

/* Include minimal declarations from sys_core.h that are needed */
/* We can't include the full file because it has circular dependencies */
/* Instead, we just ensure _enable_IRQ and _disable_IRQ are available via hardware_stubs.h */

#endif /* __SYS_CORE_H__ */

