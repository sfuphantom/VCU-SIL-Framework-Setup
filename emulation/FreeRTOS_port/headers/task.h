/*
 * task.h - Compatibility wrapper for vcu-fw's os_task.h
 * 
 * This header maps FreeRTOS V10 naming (task.h) to vcu-fw's naming (os_task.h)
 * for emulation builds.
 */

#ifndef TASK_H
#define TASK_H

#ifdef SIMULATING
    /* Include vcu-fw's task header with os_ prefix */
    #include "os_task.h"
#else
    /* For hardware builds, use vcu-fw's header directly */
    #include "os_task.h"
#endif

#endif /* TASK_H */

