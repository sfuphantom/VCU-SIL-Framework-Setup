/*
 * register_stubs.h
 * 
 * Stub definitions for hardware registers used in emulation
 * These are dummy structures that satisfy the register pointer types
 * but don't actually access hardware
 */

#ifndef REGISTER_STUBS_H
#define REGISTER_STUBS_H

#ifdef SIMULATING

#include <stdint.h>

/* Forward declarations of register structure types */
/* These are normally defined in reg_*.h files from vcu-fw */
typedef volatile struct {
    uint32_t GCR0;
    uint32_t GCR1;
    uint32_t SETINT;
    uint32_t SETINTLVL;
    uint32_t FORMAT;
    uint32_t BRS;
    uint32_t PIO0;
    uint32_t PIO1;
    uint32_t PIO6;
    uint32_t PIO7;
    uint32_t PIO8;
    uint32_t FLG;
    uint32_t BUF;
    uint32_t EMU;
    uint32_t IODATA;
    uint32_t RXSTATE;
    uint32_t TXSTATE;
} sciBASE_t;

typedef volatile struct {
    uint32_t GCR0;
    uint32_t GCR1;
    uint32_t SETINT;
    uint32_t SETINTLVL;
    uint32_t FORMAT;
    uint32_t BRS;
    uint32_t PIO0;
    uint32_t PIO1;
    uint32_t PIO6;
    uint32_t PIO7;
    uint32_t PIO8;
    uint32_t FLG;
    uint32_t BUF;
    uint32_t EMU;
    uint32_t IODATA;
    uint32_t RXSTATE;
    uint32_t TXSTATE;
} scilinBASE_t;

typedef volatile struct {
    uint32_t DIR;
    uint32_t DIN;
    uint32_t DOUT;
    uint32_t DSET;
    uint32_t DCLR;
    uint32_t PDR;
    uint32_t PULDIS;
    uint32_t PSL;
} gioPORT_t;

typedef volatile struct {
    uint32_t GCR0;
    uint32_t ENACLR;
    uint32_t LVLCLR;
} gioBASE_t;

typedef volatile struct {
    uint32_t RSTCR;
    uint32_t OPMODECR;
    uint32_t CLOCKCR;
    uint32_t CALCR;
    uint32_t GxMODECR[3];
    uint32_t EVSRC;
    uint32_t G1SRC;
    uint32_t G2SRC;
    uint32_t GxINTENA[3];
    uint32_t GxINTFLG[3];
    uint32_t GxINTCR[3];
    uint32_t EVDMACR;
    uint32_t G1DMACR;
    uint32_t G2DMACR;
    uint32_t BNDCR;
    uint32_t BNDEND;
    uint32_t EVSAMP;
    uint32_t G1SAMP;
    uint32_t G2SAMP;
    uint32_t EVSR;
    uint32_t G1SR;
    uint32_t G2SR;
    uint32_t GxSEL[3];
    uint32_t CALR;
    uint32_t SMSTATE;
    uint32_t LASTCONV;
    struct {
        uint32_t BUF0;
        uint32_t BUF1;
    } GxRESULT[3];
} adcBASE_t;

/* Dummy register instances - these are just memory locations, not real hardware */
static sciBASE_t dummy_sci_reg = {0};
static scilinBASE_t dummy_scilin_reg = {0};
static gioPORT_t dummy_gio_porta = {0};
static gioPORT_t dummy_gio_portb = {0};
static gioBASE_t dummy_gio_reg = {0};
static adcBASE_t dummy_adc_reg1 = {0};
static adcBASE_t dummy_adc_reg2 = {0};

/* Register pointer definitions - point to dummy structures */
#define sciREG (&dummy_sci_reg)
#define scilinREG (&dummy_scilin_reg)
#define gioPORTA (&dummy_gio_porta)
#define gioPORTB (&dummy_gio_portb)
#define gioREG (&dummy_gio_reg)
#define adcREG1 (&dummy_adc_reg1)
#define adcREG2 (&dummy_adc_reg2)

/* HET/PWM register stubs */
typedef volatile struct {
    uint32_t Program;
    uint32_t Control;
    uint32_t Data;
    uint32_t rsvd;
} hetINSTRUCTION_t;

typedef volatile struct {
    hetINSTRUCTION_t Instruction[160];
} hetRAMBASE_t;

typedef volatile struct {
    uint32_t GCR;
    uint32_t PFR;
    uint32_t ADDR;
    uint32_t OFF1;
    uint32_t OFF2;
    uint32_t INTENAS;
    uint32_t INTENAC;
    uint32_t EXC1;
    uint32_t EXC2;
    uint32_t PRY;
    uint32_t FLG;
    uint32_t AND;
    uint32_t rsvd1;
    uint32_t HRSH;
    uint32_t XOR;
    uint32_t REQENS;
    uint32_t REQENC;
    uint32_t REQDS;
    uint32_t rsvd2;
    uint32_t DIR;
    uint32_t DIN;
    uint32_t DOUT;
    uint32_t DSET;
    uint32_t DCLR;
    uint32_t PDR;
    uint32_t PULDIS;
    uint32_t PSL;
    uint32_t rsvd3;
    uint32_t rsvd4;
    uint32_t PCR;
    uint32_t PAR;
    uint32_t PPR;
    uint32_t SFPRLD;
    uint32_t SFENA;
    uint32_t rsvd5;
    uint32_t LBPSEL;
    uint32_t LBPDIR;
    uint32_t PINDIS;
} hetBASE_t;

static hetRAMBASE_t dummy_het_ram1 = {0};
static hetRAMBASE_t dummy_het_ram2 = {0};
static hetBASE_t dummy_het_reg1 = {0};
static hetBASE_t dummy_het_reg2 = {0};

#define hetRAM1 (&dummy_het_ram1)
#define hetRAM2 (&dummy_het_ram2)
#define hetREG1 (&dummy_het_reg1)
#define hetREG2 (&dummy_het_reg2)
#define hetPORT1 hetREG1  /* HET port 1 is same as HET register 1 */
#define hetPORT2 hetREG2  /* HET port 2 is same as HET register 2 */

/* PWM signal types (simplified) */
typedef struct {
    uint32_t duty;
    uint32_t period;
} hetSIGNAL_t;

/* PWM channel definitions */
#define pwm0 0
#define pwm1 1
#define pwm2 2
#define pwm3 3

/* SPI register stubs */
typedef volatile struct {
    uint32_t dummy[128];
} mibspiBASE_t;

static mibspiBASE_t dummy_mibspi_reg1 = {0};
#define mibspiREG1 (&dummy_mibspi_reg1)

#endif /* SIMULATING */

#endif /* REGISTER_STUBS_H */

