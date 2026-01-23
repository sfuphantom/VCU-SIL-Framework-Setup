/*
 * sci_emulation.h
 * 
 * Emulation driver for SCI (Serial Communication Interface / UART)
 * Redirects all UART output to task_logger
 */

#ifndef SCI_EMULATION_H
#define SCI_EMULATION_H

#include "reg_sci.h"  // Include register definitions from vcu-fw
#include "sys_common.h"  // For config_value_type_t
#include "hardware_stubs.h"  // For _enable_IRQ, _disable_IRQ stubs
#include <stdint.h>

#ifdef SIMULATING
    /* Define types we need - avoid circular dependency with wrapper */
    typedef struct {
        uint32 CONFIG_GCR0;
        uint32 CONFIG_GCR1;
        uint32 CONFIG_SETINT;
        uint32 CONFIG_SETINTLVL;
        uint32 CONFIG_FORMAT;
        uint32 CONFIG_BRS;
        uint32 CONFIG_PIO0;
        uint32 CONFIG_PIO1;
        uint32 CONFIG_PIO6;
        uint32 CONFIG_PIO7;
        uint32 CONFIG_PIO8;
    } sci_config_reg_t;
    
    /* loopBackType_t is already defined in sci.h, don't redefine it */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations matching vcu-fw's sci.h interface */
void sciInit(void);
void sciSetFunctional(sciBASE_t *sci, uint32 port);
void sciSetBaudrate(sciBASE_t *sci, uint32 baud);
void sciSendByte(sciBASE_t *sci, uint8 byte);
void sciSend(sciBASE_t *sci, uint32 length, uint8 * data);
uint32 sciReceiveByte(sciBASE_t *sci);
void sciReceive(sciBASE_t *sci, uint32 length, uint8 * data);
void sciEnableNotification(sciBASE_t *sci, uint32 flags);
void sciDisableNotification(sciBASE_t *sci, uint32 flags);
void sciEnableLoopback(sciBASE_t *sci, loopBackType_t Loopbacktype);
void sciDisableLoopback(sciBASE_t *sci);
void sciEnterResetState(sciBASE_t *sci);
void sciExitResetState(sciBASE_t *sci);
void sciGetConfigValue(sci_config_reg_t *config_reg, config_value_type_t type);
void scilinGetConfigValue(sci_config_reg_t *config_reg, config_value_type_t type);
void sciNotification(sciBASE_t *sci, uint32 flags);

#ifdef __cplusplus
}
#endif

#endif /* SCI_EMULATION_H */

