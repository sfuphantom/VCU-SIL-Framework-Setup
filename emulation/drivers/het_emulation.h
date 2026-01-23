/*
 * het_emulation.h
 * 
 * Emulation driver for HET (High-End Timer / PWM)
 * Logs PWM duty cycle changes to terminal
 */

#ifndef HET_EMULATION_H
#define HET_EMULATION_H

#include "reg_het.h"  // Include register definitions from vcu-fw
#include <stdint.h>

#ifdef SIMULATING
    /* Define types we need - avoid circular dependency with wrapper */
    typedef struct {
        uint32 duty;
        uint32 period;
    } hetSIGNAL_t;
    
    /* Define pwm macros directly - they're simple constants from het.h */
    /* This avoids circular dependency with the wrapper */
    #ifndef pwm0
    #define pwm0 0U
    #endif
    #ifndef pwm1
    #define pwm1 1U
    #endif
    #ifndef pwm2
    #define pwm2 2U
    #endif
    #ifndef pwm3
    #define pwm3 3U
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations matching vcu-fw's het.h interface */
void hetInit(void);
void hetSetSignal(hetRAMBASE_t *hetRAM, uint32 pwm, hetSIGNAL_t signal);
void pwmSetDuty(hetRAMBASE_t *hetRAM, uint32 pwm, uint32 duty);
void pwmSetSignal(hetRAMBASE_t *hetRAM, uint32 pwm, hetSIGNAL_t signal);
void pwmStart(hetRAMBASE_t *hetRAM, uint32 pwm);
void pwmStop(hetRAMBASE_t *hetRAM, uint32 pwm);

#ifdef __cplusplus
}
#endif

#endif /* HET_EMULATION_H */

