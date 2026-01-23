/*
 * rti_emulation.c
 * 
 * Emulation implementation for RTI (timer) driver
 * Simple stubs since RTI is not actively used in vcu-fw
 */

#include "rti_emulation.h"
#include "../../vcu-fw/VCU/Phantom/hercules-phantom-lib/rtos-common/task_logger.h"
#include "../../vcu-fw/VCU/Phantom/hercules-phantom-lib/rtos-common/ansi_colors.h"
#include "rti.h"  // Include through wrapper to get RTI constants (rtiNOTIFICATION_COMPARE0, etc.)
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* Helper function for printf-style LogColor */
static void LogColorFmt(const char* color, const char* fmt, ...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    LogColor(color, buf);
}

void rtiInit(void)
{
    LogColor(CYN, "[RTI] RTI emulation initialized (stub - not actively used)");
}

void rtiStartCounter(uint32 counter)
{
    LogColorFmt(CYN, "[RTI] Counter %lu start requested (stub)", counter);
    (void)counter;
}

void rtiStopCounter(uint32 counter)
{
    LogColorFmt(CYN, "[RTI] Counter %lu stop requested (stub)", counter);
    (void)counter;
}

uint32 rtiResetCounter(uint32 counter)
{
    LogColorFmt(CYN, "[RTI] Counter %lu reset requested (stub)", counter);
    (void)counter;
    return 0;
}

void rtiSetPeriod(uint32 compare, uint32 period)
{
    LogColorFmt(CYN, "[RTI] Compare %lu period set to %lu (stub)", compare, period);
    (void)compare;
    (void)period;
}

uint32 rtiGetPeriod(uint32 compare)
{
    LogColorFmt(CYN, "[RTI] Get period for compare %lu (stub, returning 0)", compare);
    (void)compare;
    return 0;
}

uint32 rtiGetCurrentTick(uint32 compare)
{
    LogColorFmt(CYN, "[RTI] Get current tick for compare %lu (stub, returning 0)", compare);
    (void)compare;
    return 0;
}

void rtiEnableNotification(uint32 notification)
{
    LogColorFmt(CYN, "[RTI] Notification 0x%08X enabled (stub)", notification);
    (void)notification;
}

void rtiDisableNotification(uint32 notification)
{
    LogColorFmt(CYN, "[RTI] Notification 0x%08X disabled (stub)", notification);
    (void)notification;
}

/* rtiNotification is already defined in vcu-fw/VCU/Phantom/main.c */
/* We don't need to redefine it here - the one in main.c will be used */

void rtiGetConfigValue(rti_config_reg_t *config_reg, config_value_type_t type)
{
    /* Config values not needed in emulation */
    (void)config_reg;
    (void)type;
}
