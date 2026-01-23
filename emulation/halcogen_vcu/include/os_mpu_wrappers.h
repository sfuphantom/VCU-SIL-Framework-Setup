/*
 * os_mpu_wrappers.h - Emulation wrapper for vcu-fw's os_mpu_wrappers.h
 * 
 * This file replaces vcu-fw's os_mpu_wrappers.h for emulation builds.
 * It removes ARM-specific MPU (Memory Protection Unit) attributes that
 * don't work on Linux/MacOS.
 */

#ifndef MPU_WRAPPERS_H
#define MPU_WRAPPERS_H

#ifdef SIMULATING
    /* For emulation, we don't need MPU wrappers - just define empty macros */
    #define PRIVILEGED_FUNCTION
    #define PRIVILEGED_DATA
    #define FREERTOS_SYSTEM_CALL
    
    /* Include the rest of the file's content if needed */
    /* Most of it is just function declarations with PRIVILEGED_FUNCTION */
    
#else
    /* For hardware builds, include the real file */
    #include "vcu-fw/VCU/halcogen_vcu/include/os_mpu_wrappers.h"
#endif

#endif /* MPU_WRAPPERS_H */

