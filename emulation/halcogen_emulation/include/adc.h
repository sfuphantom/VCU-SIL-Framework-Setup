/*
 * adc.h - Wrapper header for ADC driver
 * 
 * Conditionally includes emulation or real hardware driver based on SIMULATING flag
 */

#ifndef __ADC_H__
#define __ADC_H__

#ifdef SIMULATING
    /* Use emulation driver */
    #include "../../drivers/adc_emulation.h"
#else
    /* Use real hardware driver from vcu-fw */
    #include "vcu-fw/VCU/halcogen_vcu/include/adc.h"
#endif

#endif /* __ADC_H__ */

