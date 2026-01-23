/*
 * gio_emulation.h
 * 
 * Emulation driver for GPIO (General Purpose Input/Output)
 * Logs GPIO state changes to terminal via task_logger
 */

#ifndef GIO_EMULATION_H
#define GIO_EMULATION_H

#include "reg_gio.h"  // Include register definitions from vcu-fw
#include "sys_common.h"  // For config_value_type_t
#include <stdint.h>

/* Define types we need - they're defined in vcu-fw's gio.h but we can't include it
 * directly because that would create a circular dependency with the wrapper */
#ifdef SIMULATING
    typedef struct {
        uint32 CONFIG_INTDET;
        uint32 CONFIG_POL;
        uint32 CONFIG_INTENASET;
        uint32 CONFIG_LVLSET;
        uint32 CONFIG_PORTADIR;
        uint32 CONFIG_PORTAPDR;
        uint32 CONFIG_PORTAPSL;
        uint32 CONFIG_PORTAPULDIS;
        uint32 CONFIG_PORTBDIR;
        uint32 CONFIG_PORTBPDR;
        uint32 CONFIG_PORTBPSL;
        uint32 CONFIG_PORTBPULDIS;
    } gio_config_reg_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations matching vcu-fw's gio.h interface */
void gioInit(void);
void gioSetDirection(gioPORT_t *port, uint32 dir);
void gioSetBit(gioPORT_t *port, uint32 bit, uint32 value);
void gioSetPort(gioPORT_t *port, uint32 value);
uint32 gioGetBit(gioPORT_t *port, uint32 bit);
uint32 gioGetPort(gioPORT_t *port);
void gioToggleBit(gioPORT_t *port, uint32 bit);
void gioEnableNotification(gioPORT_t *port, uint32 bit);
void gioDisableNotification(gioPORT_t *port, uint32 bit);
void gioNotification(gioPORT_t *port, uint32 bit);
void gioGetConfigValue(gio_config_reg_t *config_reg, config_value_type_t type);

#ifdef __cplusplus
}
#endif

#endif /* GIO_EMULATION_H */

