/*
 * main_emulation.c
 * 
 * Entry point for emulation build
 * Wraps vcu-fw's main() function to provide proper POSIX main signature
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/* Include hardware stubs - these need to be available globally for vcu-fw code */
#include "drivers/hardware_stubs.h"
#include "drivers/register_stubs.h"

/* Make hardware stubs available globally by including them before any vcu-fw headers */
/* This ensures _enable_IRQ, _disable_IRQ, etc. are defined when vcu-fw code uses them */

/* Signal handler for clean shutdown */
static void signal_handler(int sig)
{
    (void)sig;
    printf("\n[EMULATION] Shutting down...\n");
    exit(0);
}

/* Forward declaration - vcu-fw's main renamed to vcu_fw_main */
extern void vcu_fw_main(void);

/* Our POSIX-compatible main */
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
    /* Set up signal handlers */
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    /* Call vcu-fw's main function (renamed to vcu_fw_main) */
    /* Note: vcu_fw_main() never returns (calls vTaskStartScheduler()) */
    vcu_fw_main();
    
    /* Should never reach here, but just in case */
    return 0;
}
