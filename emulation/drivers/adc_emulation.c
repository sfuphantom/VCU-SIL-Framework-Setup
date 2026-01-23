/*
 * adc_emulation.c
 * 
 * Emulation implementation for ADC driver
 * Reads sensor values from IPC pipe or uses default/simulated values
 */

#include "adc_emulation.h"
#include <string.h>
#include <stdio.h>

/* Default ADC values for emulation */
static uint16_t default_adc_values[32] = {
    2048,  // Channel 0 - mid-range default
    2048,  // Channel 1
    2048,  // Channel 2
    2048,  // Channel 3
    // ... add more defaults as needed
};

/* ADC state */
static struct {
    uint32_t conversion_active[3];  // One per group
    uint32_t fifo_data[3][16];      // FIFO buffers per group
    uint32_t fifo_count[3];        // FIFO counts
} adc_state = {0};

void adcInit(void)
{
    /* Initialize emulation state */
    memset(&adc_state, 0, sizeof(adc_state));
    
    /* Try to connect to IPC pipe for sensor data */
    /* Pipe connection is handled elsewhere, we just use it here */
}

void adcStartConversion(adcBASE_t *adc, uint32 group)
{
    if (group < 3) {
        adc_state.conversion_active[group] = 1;
        /* In emulation, conversion completes immediately */
        /* We'll simulate this by setting conversion complete flag */
    }
}

void adcStopConversion(adcBASE_t *adc, uint32 group)
{
    if (group < 3) {
        adc_state.conversion_active[group] = 0;
    }
}

void adcResetFiFo(adcBASE_t *adc, uint32 group)
{
    if (group < 3) {
        adc_state.fifo_count[group] = 0;
        memset(adc_state.fifo_data[group], 0, sizeof(adc_state.fifo_data[group]));
    }
}

uint32 adcGetData(adcBASE_t *adc, uint32 group, adcData_t *data)
{
    if (group >= 3 || data == NULL) {
        return 0;
    }
    
    /* Use default/simulated values in emulation */
    data->id = 0;
    data->value = default_adc_values[0];
    
    return 1; /* Return number of data items read */
}

uint32 adcIsFifoFull(adcBASE_t *adc, uint32 group)
{
    if (group < 3) {
        return (adc_state.fifo_count[group] >= 16) ? 1 : 0;
    }
    return 0;
}

uint32 adcIsConversionComplete(adcBASE_t *adc, uint32 group)
{
    if (group < 3) {
        return adc_state.conversion_active[group] ? 1 : 0;
    }
    return 0;
}

void adcEnableNotification(adcBASE_t *adc, uint32 group)
{
    /* Notifications not implemented in emulation */
    (void)adc;
    (void)group;
}

void adcDisableNotification(adcBASE_t *adc, uint32 group)
{
    /* Notifications not implemented in emulation */
    (void)adc;
    (void)group;
}

void adcCalibration(adcBASE_t *adc)
{
    /* Calibration not needed in emulation */
    (void)adc;
}

uint32 adcMidPointCalibration(adcBASE_t *adc)
{
    /* Calibration not needed in emulation */
    (void)adc;
    return 0;
}

void adcSetEVTPin(adcBASE_t *adc, uint32 value)
{
    /* Event pin not implemented in emulation */
    (void)adc;
    (void)value;
}

uint32 adcGetEVTPin(adcBASE_t *adc)
{
    /* Event pin not implemented in emulation */
    (void)adc;
    return 0;
}

void adcNotification(adcBASE_t *adc, uint32 group)
{
    /* Notification callback - not used in emulation */
    (void)adc;
    (void)group;
}

