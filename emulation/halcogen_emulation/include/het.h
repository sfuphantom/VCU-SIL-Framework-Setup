/*
 * het.h - Wrapper header for HET/PWM driver
 */

#ifndef __HET_H__
#define __HET_H__

#ifdef SIMULATING
    #include "../../drivers/het_emulation.h"
#else
    #include "vcu-fw/VCU/halcogen_vcu/include/het.h"
#endif

#endif /* __HET_H__ */

