/*
 * port_wrapper.c
 * 
 * Wrapper functions to bridge vcu-fw's expected signatures with Posix port's implementations
 */

#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

/* Forward declaration of Posix port's pxPortInitialiseStack with 4 parameters */
extern portSTACK_TYPE * pxPortInitialiseStack_Posix( portSTACK_TYPE * pxTopOfStack,
                                                     portSTACK_TYPE * pxEndOfStack,
                                                     pdTASK_CODE pxCode,
                                                     void * pvParameters );

/* Wrapper function that matches vcu-fw's expected signature (3 parameters) */
/* vcu-fw calls pxPortInitialiseStack with only 3 parameters, but Posix port needs 4 */
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
    /* For Posix port, pxEndOfStack is not used (stack is managed by pthread) */
    /* We can pass NULL or pxTopOfStack as a dummy value */
    return (StackType_t *)pxPortInitialiseStack_Posix( (portSTACK_TYPE *)pxTopOfStack,
                                                        NULL,  /* pxEndOfStack not used in Posix port */
                                                        (pdTASK_CODE)pxCode,
                                                        pvParameters );
}

