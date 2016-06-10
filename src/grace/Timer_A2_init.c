/*
 *  This file is automatically generated and does not require a license
 *
 *  ==== WARNING: CHANGES TO THIS GENERATED FILE WILL BE OVERWRITTEN ====
 *
 *  To make changes to the generated code, use the space between existing
 *      "USER CODE START (section: <name>)"
 *  and
 *      "USER CODE END (section: <name>)"
 *  comments, where <name> is a single word identifying the section.
 *  Only these sections will be preserved.
 *
 *  Do not move these sections within this file or change the START and
 *  END comments in any way.
 *  ==== ALL OTHER CHANGES WILL BE OVERWRITTEN WHEN IT IS REGENERATED ====
 *
 *  This file was generated from
 *      /opt/ti/grace_3_10_00_82/packages/ti/mcu/msp430/csl/timer/ITimerx_A_init.xdt
 */

#include <msp430.h>
#include "_Grace.h"

/* USER CODE START (section: Timer_A2_init_c_prologue) */
/* User defined includes, defines, global variables and functions */
/* USER CODE END (section: Timer_A2_init_c_prologue) */

/*
 *  ======== Timer_A2_graceInit ========
 *  Initialize MSP430 Timer_A2 timer
 */
void Timer_A2_graceInit(void)
{
    /* USER CODE START (section: Timer_A2_graceInit_prologue) */
    /* User initialization code */
    /* USER CODE END (section: Timer_A2_graceInit_prologue) */
    
    /* TACCR0, Timer_A Capture/Compare Register 0 */
    TACCR0 = 15624;

    /* 
     * TACTL, Timer_A2 Control Register
     * 
     * TASSEL_2 -- SMCLK
     * ID_3 -- Divider - /8
     * MC_3 -- Up/Down Mode
     */
    TACTL = TASSEL_2 | ID_3 | MC_3;

    /* USER CODE START (section: Timer_A2_graceInit_epilogue) */
    /* User code */
    /* USER CODE END (section: Timer_A2_graceInit_epilogue) */
}
