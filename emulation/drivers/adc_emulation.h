/*
 * adc_emulation.h
 * 
 * Emulation driver for ADC (Analog-to-Digital Converter)
 * Reads sensor values from IPC pipe or uses default values
 */

#ifndef ADC_EMULATION_H
#define ADC_EMULATION_H

#include "reg_adc.h"  // Include register definitions from vcu-fw
#include <stdint.h>

#ifdef SIMULATING
    /* Define types we need - avoid circular dependency with wrapper */
    typedef struct {
        uint32 id;
        uint16 value;
    } adcData_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations matching vcu-fw's adc.h interface */
void adcInit(void);
void adcStartConversion(adcBASE_t *adc, uint32 group);
void adcStopConversion(adcBASE_t *adc, uint32 group);
void adcResetFiFo(adcBASE_t *adc, uint32 group);
uint32 adcGetData(adcBASE_t *adc, uint32 group, adcData_t *data);
uint32 adcIsFifoFull(adcBASE_t *adc, uint32 group);
uint32 adcIsConversionComplete(adcBASE_t *adc, uint32 group);
void adcEnableNotification(adcBASE_t *adc, uint32 group);
void adcDisableNotification(adcBASE_t *adc, uint32 group);
void adcCalibration(adcBASE_t *adc);
uint32 adcMidPointCalibration(adcBASE_t *adc);
void adcSetEVTPin(adcBASE_t *adc, uint32 value);
uint32 adcGetEVTPin(adcBASE_t *adc);
void adcNotification(adcBASE_t *adc, uint32 group);

#ifdef __cplusplus
}
#endif

#endif /* ADC_EMULATION_H */

