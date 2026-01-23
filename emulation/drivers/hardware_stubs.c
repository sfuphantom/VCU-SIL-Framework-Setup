/*
 * hardware_stubs.c
 * 
 * Implementation stubs for hardware-specific functions that don't exist on macOS
 * These are linker stubs to satisfy undefined symbol errors
 */

#include <stdint.h>
#include <stddef.h>

#ifdef SIMULATING

/* ============================================================================
 * TI FEE (Flash EEPROM Emulation) Stubs
 * ============================================================================ */

#include "ti_fee.h"
#include "ti_fee_types.h"

void TI_Fee_Init(void)
{
    /* Stub - EEPROM not needed in emulation */
}

Std_ReturnType TI_Fee_InvalidateBlock(uint16 BlockNumber)
{
    (void)BlockNumber;
    return 0; /* E_OK */
}

Std_ReturnType TI_Fee_Read(uint16 BlockNumber, uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length)
{
    (void)BlockNumber;
    (void)BlockOffset;
    (void)DataBufferPtr;
    (void)Length;
    return 0; /* E_OK */
}

Std_ReturnType TI_Fee_WriteAsync(uint16 BlockNumber, uint8* DataBufferPtr)
{
    (void)BlockNumber;
    (void)DataBufferPtr;
    return 0; /* E_OK */
}

void TI_Fee_MainFunction(void)
{
    /* Stub - no-op in emulation */
}

TI_Fee_ErrorCodeType TI_FeeErrorCode(uint8 u8EEPIndex)
{
    (void)u8EEPIndex;
    return 0; /* TI_FEE_OK */
}

void TI_Fee_ErrorRecovery(TI_Fee_ErrorCodeType ErrorCode, uint8 u8VirtualSector)
{
    (void)ErrorCode;
    (void)u8VirtualSector;
}

TI_FeeJobResultType TI_Fee_GetJobResult(uint8 u8EEPIndex)
{
    (void)u8EEPIndex;
    return 0; /* TI_FEE_OK */
}

Std_ReturnType TI_Fee_EraseImmediateBlock(uint16 BlockNumber)
{
    (void)BlockNumber;
    return 0; /* E_OK */
}

Std_ReturnType TI_Fee_WriteSync(uint16 BlockNumber, uint8* DataBufferPtr)
{
    (void)BlockNumber;
    (void)DataBufferPtr;
    return 0; /* E_OK */
}

Std_ReturnType TI_Fee_Shutdown(void)
{
    return 0; /* E_OK */
}

boolean TI_Fee_Format(uint32 u32FormatKey)
{
    (void)u32FormatKey;
    return FALSE;
}

Std_ReturnType TI_Fee_ReadSync(uint16 BlockNumber, uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length)
{
    (void)BlockNumber;
    (void)BlockOffset;
    (void)DataBufferPtr;
    (void)Length;
    return 0; /* E_OK */
}

/* TI_Fee_u32ActCpyVS and TI_Fee_u8ErrEraseVS are global variables, not functions */
uint32 TI_Fee_u32ActCpyVS = 0;
uint8 TI_Fee_u8ErrEraseVS = 0;

/* TI_Fee_GetStatus returns TI_FeeModuleStatusType */
#include "ti_fee_types.h"  /* For TI_FeeModuleStatusType */
TI_FeeModuleStatusType TI_Fee_GetStatus(uint8 u8EEPIndex)
{
    (void)u8EEPIndex;
    return IDLE; /* Return idle status */
}

/* ============================================================================
 * MIBSPI (SPI) Stubs
 * ============================================================================ */

#include "mibspi.h"

void mibspiInit(void)
{
    /* Stub - SPI not needed in emulation */
}

void mibspiSetData(mibspiBASE_t *mibspi, uint32 group, uint16 * data)
{
    (void)mibspi;
    (void)group;
    (void)data;
}

uint32 mibspiGetData(mibspiBASE_t *mibspi, uint32 group, uint16 * data)
{
    (void)mibspi;
    (void)group;
    if (data != NULL) {
        *data = 0;
    }
    return 0;
}

void mibspiTransfer(mibspiBASE_t *mibspi, uint32 group)
{
    (void)mibspi;
    (void)group;
}

/* mibspiIsTransferComplete returns boolean (typically uint8 or int) */
#include "hal_stdtypes.h"  /* For boolean type */
boolean mibspiIsTransferComplete(mibspiBASE_t *mibspi, uint32 group)
{
    (void)mibspi;
    (void)group;
    return TRUE; /* Always complete in emulation */
}

/* ============================================================================
 * IPC Pipe Stubs
 * ============================================================================ */

/* Forward declare Pipe type if needed */
typedef struct {
    int fd;
} Pipe;

extern Pipe SimulationPipe;

int read_from_pipe(Pipe pipe, char *buffer, size_t size)
{
    (void)pipe;
    (void)buffer;
    (void)size;
    return 0; /* No data read */
}

/* ============================================================================
 * ARM Software Interrupt Stub
 * ============================================================================ */

void swiSwitchToMode(uint32 mode)
{
    (void)mode;
    /* ARM-specific software interrupt - no-op on macOS */
}

#endif /* SIMULATING */

