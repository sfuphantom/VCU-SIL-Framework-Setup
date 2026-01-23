/*
 * hardware_stubs.h
 * 
 * Stubs for hardware-specific functions that don't exist in emulation
 */

#ifndef HARDWARE_STUBS_H
#define HARDWARE_STUBS_H

#ifdef SIMULATING

/* IRQ enable/disable - no-op in emulation */
#define _enable_IRQ()   do { } while(0)
#define _disable_IRQ()  do { } while(0)
#define __enable_irq()  do { } while(0)
#define __disable_irq() do { } while(0)

/* System initialization - minimal in emulation */
static inline void systemInit(void) { }
static inline void periphInit(void) { }

#endif /* SIMULATING */

#endif /* HARDWARE_STUBS_H */

