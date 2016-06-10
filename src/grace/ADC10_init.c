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
 *      /opt/ti/grace_3_10_00_82/packages/ti/mcu/msp430/csl/adc/ADC10_init.xdt
 */

#include <msp430.h>
#include "_Grace.h"

/* USER CODE START (section: ADC10_init_c_prologue) */
/* User defined includes, defines, global variables and functions */
/* USER CODE END (section: ADC10_init_c_prologue) */

/*
 *  ======== ADC10_graceInit ========
 *  Initialize MSP430 10-bit Analog to Digital Converter
 */
void ADC10_graceInit(void)
{
    /* USER CODE START (section: ADC10_graceInit_prologue) */
    /* User initialization code */
    /* USER CODE END (section: ADC10_graceInit_prologue) */

    /* disable ADC10 during initialization */
    ADC10CTL0 &= ~ENC;

    /* 
     * Control Register 0
     * 
     * ~ADC10SC -- No conversion
     * ~ENC -- Disable ADC
     * ~ADC10IFG -- Clear ADC interrupt flag
     * ~ADC10IE -- Disable ADC interrupt
     * ADC10ON -- Switch On ADC10
     * REFON -- Enable ADC reference generator
     * REF2_5V -- Set reference voltage generator = 2.5V
     * ~MSC -- Disable multiple sample and conversion
     * ~REFBURST -- Reference buffer on continuously
     * ~REFOUT -- Reference output off
     * ~ADC10SR -- Reference buffer supports up to ~200 ksps
     * ADC10SHT_0 -- 4 x ADC10CLKs
     * SREF_1 -- VR+ = VREF+ and VR- = VSS
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    ADC10CTL0 = ADC10ON | REFON | REF2_5V | ADC10SHT_0 | SREF_1;

    /* 
     * Control Register 1
     * 
     * ~ADC10BUSY -- No operation is active
     * CONSEQ_0 -- Single channel single conversion
     * ADC10SSEL_0 -- ADC10OSC
     * ADC10DIV_0 -- Divide by 1
     * ~ISSH -- Input signal not inverted
     * ~ADC10DF -- ADC10 Data Format as binary
     * SHS_0 -- ADC10SC
     * INCH_11 -- ADC convert VCC
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    ADC10CTL1 = CONSEQ_0 | ADC10SSEL_0 | ADC10DIV_0 | SHS_0 | INCH_11;


    /* Software delay for REFON to settle */
    __delay_cycles(30000);

    /* enable ADC10 */
    ADC10CTL0 |= ENC;

    /* USER CODE START (section: ADC10_graceInit_epilogue) */
    /* User code */
    /* USER CODE END (section: ADC10_graceInit_epilogue) */
}
