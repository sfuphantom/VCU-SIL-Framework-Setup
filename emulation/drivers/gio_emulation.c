/*
 * gio_emulation.c
 * 
 * Emulation implementation for GPIO driver
 * Logs all GPIO operations to terminal via task_logger
 */

#include "gio_emulation.h"
#include "../../vcu-fw/VCU/Phantom/hercules-phantom-lib/rtos-common/task_logger.h"
#include "../../vcu-fw/VCU/Phantom/hercules-phantom-lib/rtos-common/ansi_colors.h"
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

/* GPIO state storage */
static struct {
    uint32_t porta_dir;
    uint32_t portb_dir;
    uint32_t porta_data;
    uint32_t portb_data;
} gio_state = {0};

/* Helper function to get port name */
static const char* get_port_name(gioPORT_t *port)
{
    if (port == gioPORTA) return "GIO_PORTA";
    if (port == gioPORTB) return "GIO_PORTB";
    return "GIO_UNKNOWN";
}

void gioInit(void)
{
    memset(&gio_state, 0, sizeof(gio_state));
}

void gioSetDirection(gioPORT_t *port, uint32 dir)
{
    char msg[128];
    if (port == gioPORTA) {
        gio_state.porta_dir = dir;
        snprintf(msg, sizeof(msg), "[GPIO] %s direction set to 0x%08X", get_port_name(port), dir);
        LogColor(CYN, msg);
    } else if (port == gioPORTB) {
        gio_state.portb_dir = dir;
        snprintf(msg, sizeof(msg), "[GPIO] %s direction set to 0x%08X", get_port_name(port), dir);
        LogColor(CYN, msg);
    }
}

void gioSetBit(gioPORT_t *port, uint32 bit, uint32 value)
{
    uint32_t *port_data = (port == gioPORTA) ? &gio_state.porta_data : &gio_state.portb_data;
    
    if (value) {
        *port_data |= (1U << bit);
        LogColorFmt(GRN, "[GPIO] %s bit %lu set HIGH", get_port_name(port), bit);
    } else {
        *port_data &= ~(1U << bit);
        LogColorFmt(YEL, "[GPIO] %s bit %lu set LOW", get_port_name(port), bit);
    }
}

void gioSetPort(gioPORT_t *port, uint32 value)
{
    char msg[128];
    if (port == gioPORTA) {
        gio_state.porta_data = value;
    } else if (port == gioPORTB) {
        gio_state.portb_data = value;
    }
    snprintf(msg, sizeof(msg), "[GPIO] %s set to 0x%08X", get_port_name(port), value);
    LogColor(CYN, msg);
}

uint32 gioGetBit(gioPORT_t *port, uint32 bit)
{
    uint32_t port_data = (port == gioPORTA) ? gio_state.porta_data : gio_state.portb_data;
    uint32_t value = (port_data >> bit) & 1U;
    LogColorFmt(CYN, "[GPIO] %s bit %lu read: %lu", get_port_name(port), bit, value);
    return value;
}

uint32 gioGetPort(gioPORT_t *port)
{
    uint32_t value = (port == gioPORTA) ? gio_state.porta_data : gio_state.portb_data;
    LogColorFmt(CYN, "[GPIO] %s read: 0x%08X", get_port_name(port), value);
    return value;
}

void gioToggleBit(gioPORT_t *port, uint32 bit)
{
    uint32_t current = gioGetBit(port, bit);
    gioSetBit(port, bit, !current);
    LogColorFmt(MAG, "[GPIO] %s bit %lu toggled", get_port_name(port), bit);
}

void gioEnableNotification(gioPORT_t *port, uint32 bit)
{
    LogColorFmt(CYN, "[GPIO] %s bit %lu notification enabled", get_port_name(port), bit);
    (void)port;
    (void)bit;
}

void gioDisableNotification(gioPORT_t *port, uint32 bit)
{
    LogColorFmt(CYN, "[GPIO] %s bit %lu notification disabled", get_port_name(port), bit);
    (void)port;
    (void)bit;
}

void gioNotification(gioPORT_t *port, uint32 bit)
{
    LogColorFmt(YEL, "[GPIO] %s bit %lu notification triggered", get_port_name(port), bit);
    (void)port;
    (void)bit;
}

void gioGetConfigValue(gio_config_reg_t *config_reg, config_value_type_t type)
{
    /* Config values not needed in emulation */
    (void)config_reg;
    (void)type;
}

