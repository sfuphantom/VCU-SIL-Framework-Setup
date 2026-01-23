/*
 * os_portable.h - Emulation wrapper for vcu-fw's os_portable.h
 * 
 * This file replaces vcu-fw's os_portable.h for emulation builds.
 * It is placed at emulation/halcogen_vcu/include/os_portable.h so that
 * when FreeRTOS.h includes <halcogen_vcu/include/os_portable.h>, this
 * file is found first (because -Iemulation comes before -Ivcu-fw/VCU/halcogen_vcu/include).
 */

#ifndef PORTABLE_H
#define PORTABLE_H

#ifdef SIMULATING
    /* For emulation: Include Posix port's portmacro.h */
    #include "../../FreeRTOS_port/Posix/portmacro.h"
    
    /* Include MPU wrappers (which we've stubbed out for emulation) */
    #include "os_mpu_wrappers.h"
    
    /* Include the rest of vcu-fw's os_portable.h content */
    /* We need to replicate the function declarations but without ARM-specific attributes */
    
    /* Task function prototype */
    typedef void (*TaskFunction_t)( void * );
    
    /* Setup the stack of a new task so it is ready to be placed under the
     * scheduler control. */
    /* Note: Posix port signature includes pxEndOfStack, but vcu-fw code calls it without that parameter */
    /* We need to declare it to match vcu-fw's expectation (3 parameters) */
    StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters );
    
    /* Used by heap_5.c. */
    typedef struct HeapRegion
    {
        uint8_t *pucStartAddress;
        size_t xSizeInBytes;
    } HeapRegion_t;
    
    /* Used to define multiple heap regions for use by heap_5.c. */
    void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions );
    
    /* Map to the memory management routines required for the port. */
    void *pvPortMalloc( size_t xSize );
    void vPortFree( void *pv );
    void vPortInitialiseBlocks( void );
    size_t xPortGetFreeHeapSize( void );
    size_t xPortGetMinimumEverFreeHeapSize( void );
    
    /* Setup the hardware ready for the scheduler to take control. */
    void vPortSetupTimerInterrupt( void );
    
    /* Start the scheduler. */
    /* Note: Posix port declares this as static, so we don't declare it here */
    /* extern void vPortStartFirstTask( void ); */
    
    /* Used by queue.c to determine if data was read from a queue. */
    BaseType_t xPortStartScheduler( void );
    
    /* Used by queue.c to determine if data was read from a queue. */
    void vPortEndScheduler( void );
    
#else
    /* For hardware builds, this file should not be included */
    /* The build system should use vcu-fw's original os_portable.h */
    #error "This os_portable.h wrapper is for emulation only. Use vcu-fw's original for hardware builds."
#endif

#endif /* PORTABLE_H */

