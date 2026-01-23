/*
 * FreeRTOSConfig.h - Emulation Configuration
 * 
 * This is an emulation-specific FreeRTOS configuration file for Linux/MacOS.
 * It is based on vcu-fw's FreeRTOSConfig.h but adapted for the Posix port.
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions are based on vcu-fw's configuration but adapted
 * for Posix port emulation on Linux/MacOS.
 *----------------------------------------------------------*/

/* Scheduler behavior */
#define configUSE_PREEMPTION          1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0  /* Posix port doesn't support this */
#define configUSE_FPU                           1
#define configUSE_IDLE_HOOK           0
#define configUSE_TICK_HOOK           0
#define configUSE_TRACE_FACILITY      1
#define configUSE_16_BIT_TICKS        0

/* Clock and tick configuration */
#define configCPU_CLOCK_HZ            ( ( unsigned portLONG ) 1000000000 ) /* 1GHz for emulation */
#define configTICK_RATE_HZ            ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES          ( 6 )
#define configMINIMAL_STACK_SIZE      ( ( unsigned portSHORT ) 128 )
#define configTOTAL_HEAP_SIZE         ( ( size_t ) 12000 )
#define configMAX_TASK_NAME_LEN       ( 16 )
#define configIDLE_SHOULD_YIELD       1

/* Runtime statistics - use Posix port's implementation */
#define configGENERATE_RUN_TIME_STATS 1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1

/* Memory management */
#define configUSE_MALLOC_FAILED_HOOK  0
#define configUSE_TIME_SLICING        1  /* Round-robin time-scheduling for same priority Tasks */
#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 1
#define configUSE_TICKLESS_IDLE                 0  /* Disable for emulation */

/* Co-routine definitions */
#define configUSE_CO_ROUTINES           0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Mutexes */
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1

/* Semaphores */
#define configUSE_COUNTING_SEMAPHORES   1

/* Queues */
#define configUSE_QUEUE_SETS            1

/* Timers */
#define configUSE_TIMERS                1
#define configTIMER_TASK_PRIORITY       (3)
#define configTIMER_QUEUE_LENGTH        10
#define configTIMER_TASK_STACK_DEPTH    (configMINIMAL_STACK_SIZE*2)

/* API includes */
#define INCLUDE_vTaskPrioritySet            1
#define INCLUDE_uxTaskPriorityGet           1
#define INCLUDE_vTaskDelete                 1
#define INCLUDE_vTaskCleanUpResources       0
#define INCLUDE_vTaskSuspend                1
#define INCLUDE_xTaskResumeFromISR          1
#define INCLUDE_vTaskDelayUntil             1
#define INCLUDE_vTaskDelay                  1
#define INCLUDE_xTaskGetSchedulerState      1
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#define INCLUDE_xTaskAbortDelay             1
#define INCLUDE_eTaskGetState               1
#define INCLUDE_xTaskGetHandle              1
#define INCLUDE_xTaskGetIdleTaskHandle      1
#define INCLUDE_xTaskGetCurrentTaskHandle   1  /* Required for mutexes */

/* Runtime statistics - Posix port implementation */
/* The Posix port provides ulPortGetRunTime() which is used by portGET_RUN_TIME_COUNTER_VALUE() */
/* No need to define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS or portGET_RUN_TIME_COUNTER_VALUE */
/* They are handled by the Posix port's portmacro.h */

/* Debug ASSERT */
#define configASSERT( x ) if( ( x ) == pdFALSE ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* MPU (Memory Protection Unit) - Not supported in Posix port */
/* All MPU-related code should be disabled when SIMULATING is defined */

#endif /* FREERTOS_CONFIG_H */

