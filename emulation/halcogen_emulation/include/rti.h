/*
 * rti.h - Wrapper header for RTI timer driver
 */

#ifndef __RTI_H__
#define __RTI_H__

#ifdef SIMULATING
    #include "../../drivers/rti_emulation.h"
#else
    #include "vcu-fw/VCU/halcogen_vcu/include/rti.h"
#endif

#endif /* __RTI_H__ */

