/*
 * F021.h - Emulation stub for TI Flash API (F021)
 * 
 * F021 is the TI Flash API library header. For emulation, we provide
 * minimal stubs to satisfy compilation. Flash operations are not needed
 * in emulation.
 */

#ifndef F021_H
#define F021_H

#ifdef SIMULATING

#include <stdint.h>
#include <stdbool.h>

/* Flash API types - minimal stubs for emulation */
typedef enum {
    Fapi_Status_Success = 0,
    Fapi_Status_FsmReady = 0,
    Fapi_Error_Fail = 1
} Fapi_StatusType;

typedef enum {
    Fapi_FlashStatusType_Success = 0
} Fapi_FlashStatusType;

/* Flash sector and bank types - needed by Device_types.h */
typedef struct {
    uint32_t u32SectorSize;
    uint32_t u32SectorAddr;
} Fapi_FlashSectorType;

typedef struct {
    uint32_t u32BankSize;
    Fapi_FlashSectorType *pSectors;
    uint32_t u32SectorCount;
} Fapi_FlashBankType;

/* Endianness definition - needed by ti_fee_types.h */
/* ti_fee_types.h checks for _LITTLE_ENDIAN or _BIG_ENDIAN */
/* We're on a little-endian system (x86_64 Mac/Linux), so only define _LITTLE_ENDIAN */
#ifndef _LITTLE_ENDIAN
#define _LITTLE_ENDIAN 1
#endif
/* Don't define _BIG_ENDIAN - only one should be defined */

/* Flash API function declarations - stubs for emulation */
/* These are typically provided by the TI F021 Flash API library */
/* For emulation, we just declare them to satisfy compilation */

#ifdef __cplusplus
extern "C" {
#endif

/* Flash initialization - no-op in emulation */
static inline void Fapi_initializeAPI(void) { }

/* Flash status - return success in emulation */
static inline Fapi_StatusType Fapi_getFsmStatus(void) {
    return Fapi_Status_Success;
}

/* Flash erase - no-op in emulation */
static inline Fapi_StatusType Fapi_issueAsyncCommandWithAddress(uint32_t command, uint32_t address) {
    (void)command;
    (void)address;
    return Fapi_Status_Success;
}

/* Flash program - no-op in emulation */
static inline Fapi_StatusType Fapi_setActiveFlashBank(uint32_t bank) {
    (void)bank;
    return Fapi_Status_Success;
}

#ifdef __cplusplus
}
#endif

/* Flash register structure - not used in emulation */
typedef volatile struct {
    uint32_t dummy[256];
} Fapi_FmcRegistersType;

/* Flash register pointer - point to dummy structure */
#define FMC_REGS ((Fapi_FmcRegistersType *)0xFFF87000U)

#else
    /* For hardware builds, include the real F021.h if available */
    #error "F021.h not found. This is a TI Flash API library header that must be provided separately for hardware builds."
#endif

#endif /* F021_H */

