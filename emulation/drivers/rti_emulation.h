/*
 * rti_emulation.h
 * 
 * Emulation driver for RTI (Real-Time Interrupt / Timer)
 * Uses POSIX timers for emulation
 */

#ifndef RTI_EMULATION_H
#define RTI_EMULATION_H

#include "reg_rti.h"  // Include register definitions from vcu-fw
#include "sys_common.h"  // For config_value_type_t
#include <stdint.h>

/* Forward declare rti_config_reg_t - full definition is in rti.h but we avoid circular includes */
/* The real rti.h is included through the wrapper at emulation/halcogen_emulation/include/rti.h */
typedef struct rti_config_reg {
    uint32 CONFIG_GCTRL;
    uint32 CONFIG_TBCTRL;
    uint32 CONFIG_CAPCTRL;
    uint32 CONFIG_COMPCTRL;
    uint32 CONFIG_UDCP0;
    uint32 CONFIG_UDCP1;
    uint32 CONFIG_UDCP2;
    uint32 CONFIG_UDCP3;
} rti_config_reg_t;

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations matching vcu-fw's rti.h interface */
void rtiInit(void);
void rtiStartCounter(uint32 counter);
void rtiStopCounter(uint32 counter);
void rtiSetPeriod(uint32 compare, uint32 period);
uint32 rtiGetPeriod(uint32 compare);
void rtiEnableNotification(uint32 notification);
void rtiDisableNotification(uint32 notification);
/* rtiNotification is defined in vcu-fw/VCU/Phantom/main.c, not in emulation */
void rtiGetConfigValue(rti_config_reg_t *config_reg, config_value_type_t type);

#ifdef __cplusplus
}
#endif

#endif /* RTI_EMULATION_H */

