/*
 * gio.h - Wrapper header for GPIO driver
 */

#ifndef __GIO_H__
#define __GIO_H__

#ifdef SIMULATING
    #include "../../drivers/gio_emulation.h"
#else
    #include "vcu-fw/VCU/halcogen_vcu/include/gio.h"
#endif

#endif /* __GIO_H__ */

