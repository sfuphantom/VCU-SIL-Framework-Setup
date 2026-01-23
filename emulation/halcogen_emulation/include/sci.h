/*
 * sci.h - Wrapper header for SCI/UART driver
 */

#ifndef __SCI_H__
#define __SCI_H__

#ifdef SIMULATING
    #include "../../drivers/sci_emulation.h"
#else
    #include "vcu-fw/VCU/halcogen_vcu/include/sci.h"
#endif

#endif /* __SCI_H__ */

