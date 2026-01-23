/*
 * sci_emulation.c
 * 
 * Emulation implementation for SCI/UART driver
 * Redirects all output to task_logger instead of hardware UART
 */

#include "sci_emulation.h"
#include "../../vcu-fw/VCU/Phantom/hercules-phantom-lib/rtos-common/task_logger.h"
#include "../../vcu-fw/VCU/Phantom/hercules-phantom-lib/rtos-common/ansi_colors.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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

/* SCI state */
static struct {
    uint32_t baudrate;
    uint8_t rx_buffer[256];
    uint32_t rx_count;
} sci_state = {0};

/* Helper to get SCI name */
static const char* get_sci_name(sciBASE_t *sci)
{
    if (sci == sciREG) return "SCI_REG";
    if (sci == scilinREG) return "SCI_LIN";
    return "SCI_UNKNOWN";
}

void sciInit(void)
{
    memset(&sci_state, 0, sizeof(sci_state));
}

void sciSetFunctional(sciBASE_t *sci, uint32 port)
{
    LogColorFmt(CYN, "[UART] %s functional set to port %lu", get_sci_name(sci), port);
    (void)sci;
    (void)port;
}

void sciSetBaudrate(sciBASE_t *sci, uint32 baud)
{
    sci_state.baudrate = baud;
    LogColorFmt(CYN, "[UART] %s baudrate set to %lu", get_sci_name(sci), baud);
    (void)sci;
}

void sciSendByte(sciBASE_t *sci, uint8 byte)
{
    /* In emulation, output directly to stdout to avoid circular dependency with logger */
    putchar(byte);
    fflush(stdout);
    (void)sci;
}

void sciSend(sciBASE_t *sci, uint32 length, uint8 * data)
{
    if (data == NULL || length == 0) {
        return;
    }
    
    /* In emulation, output directly to stdout to avoid circular dependency with logger */
    /* The logger calls UARTprintf which calls sciSend, so we must output directly here */
    fwrite(data, 1, length, stdout);
    fflush(stdout);
    (void)sci;
}

uint32 sciReceiveByte(sciBASE_t *sci)
{
    /* In emulation, we could read from stdin or pipe */
    /* For now, return 0 (no data) */
    (void)sci;
    return 0;
}

void sciReceive(sciBASE_t *sci, uint32 length, uint8 * data)
{
    if (data == NULL || length == 0) {
        return;
    }
    
    /* In emulation, we could read from stdin or pipe */
    /* For now, fill with zeros */
    memset(data, 0, length);
    LogColorFmt(CYN, "[UART] %s RX: %lu bytes (simulated)", get_sci_name(sci), length);
    (void)sci;
}

void sciEnableNotification(sciBASE_t *sci, uint32 flags)
{
    LogColorFmt(CYN, "[UART] %s notifications enabled (flags: 0x%08X)", get_sci_name(sci), flags);
    (void)sci;
    (void)flags;
}

void sciDisableNotification(sciBASE_t *sci, uint32 flags)
{
    LogColorFmt(CYN, "[UART] %s notifications disabled (flags: 0x%08X)", get_sci_name(sci), flags);
    (void)sci;
    (void)flags;
}

void sciEnableLoopback(sciBASE_t *sci, loopBackType_t Loopbacktype)
{
    LogColorFmt(CYN, "[UART] %s loopback enabled", get_sci_name(sci));
    (void)sci;
    (void)Loopbacktype;
}

void sciDisableLoopback(sciBASE_t *sci)
{
    LogColorFmt(CYN, "[UART] %s loopback disabled", get_sci_name(sci));
    (void)sci;
}

void sciEnterResetState(sciBASE_t *sci)
{
    LogColorFmt(CYN, "[UART] %s entered reset state", get_sci_name(sci));
    (void)sci;
}

void sciExitResetState(sciBASE_t *sci)
{
    LogColorFmt(CYN, "[UART] %s exited reset state", get_sci_name(sci));
    (void)sci;
}

void sciGetConfigValue(sci_config_reg_t *config_reg, config_value_type_t type)
{
    /* Config values not needed in emulation */
    (void)config_reg;
    (void)type;
}

void scilinGetConfigValue(sci_config_reg_t *config_reg, config_value_type_t type)
{
    /* Config values not needed in emulation */
    (void)config_reg;
    (void)type;
}

void sciNotification(sciBASE_t *sci, uint32 flags)
{
    LogColorFmt(YEL, "[UART] %s notification (flags: 0x%08X)", get_sci_name(sci), flags);
    (void)sci;
    (void)flags;
}

