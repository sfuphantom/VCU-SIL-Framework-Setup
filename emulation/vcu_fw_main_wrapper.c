/*
 * vcu_fw_main_wrapper.c
 * 
 * Wrapper to rename vcu-fw's main() function to vcu_fw_main()
 * This allows us to have a POSIX-compatible main() in main_emulation.c
 */

/* Include hardware stubs BEFORE including vcu-fw code */
/* This ensures _enable_IRQ, _disable_IRQ, etc. are available */
#include "drivers/hardware_stubs.h"

/* Rename main to vcu_fw_main before including vcu-fw's main.c */
#define main vcu_fw_main

/* Include vcu-fw's main.c - this will define vcu_fw_main() instead of main() */
/* The include path -I$(PHANTOM_DIR) makes "main.c" resolve to vcu-fw/VCU/Phantom/main.c */
#include "main.c"

#undef main

