/*****************************************************************************
    Using MSP430 for door alarm timer

    Description: If door (SW) not closed the LED is blinking every 2 sec, the alarm buzzer will XOR every 10 minutes.

    Version: 1.3
    Author: DmitryK
    Modifications: When the battery voltage less than 3.0 V and door is opened the alarm buzzer will be immediately enabled.

                  MSP430G2230
               -----------------  3.7 Li-ion battery
              |                 |  |
              |   ADC10 -> Vcc  |--- ..
              |                 |     \\
              |            P1.6 |-----|<1---| LED
              |                 |
              |            P1.5 |-----|o|---| Buzzer
              |                 |
              |                 |
              |            P1.2 |----_ \_----
              |                 |     SW   _|_
              |                 |           _  GND
               -----------------
                     SO-8

CCS       v6.1.1.00022
Grace     v3.10.0.82
DriverLib v2.60.0.02
Compler   TIv16.3.0.STS

******************************************************************************/

#include <msp430.h>
#include <ti/mcu/msp430/Grace.h>

void ADC10_Init(void);
unsigned int open_counter=0, ADC_Conversion_Result;

int main(void) {
    Grace_init();                                // Activate Grace-generated configuration
    TACCTL0 = CM_0 | CCIS_0 | OUTMOD_0 | CCIE;   // Timer_A2 Interrupt config
    open_counter=0;
    __bis_SR_register(LPM0_bits);                // Entering low power mode 0
    return (0);
}


// Timer_A2 Interrupt Service Routine
#pragma vector=TIMERA0_VECTOR
__interrupt void TIMERA0_ISR_HOOK(void) {
    extern unsigned int open_counter, ADC_Conversion_Result;
    ADC10_Init();
    __delay_cycles(30000);                       // Delay 30ms with DCO 1MHz
    ADC10CTL0 |= ADC10SC;                        // ADC Start Conversion - Software trigger

    P1REN |= BIT2;
    __delay_cycles(100000);                      // Delay 100ms
    if (P1IN & BIT2) {                           // Blink the Led BIT6 with period 2s if the door was open
        open_counter++;                          // Toggle alarm beeper BIT5 with period 2s
        if (open_counter>300) {                  // if the door was open more than 10min
            P1OUT ^= BIT5;
        }
    P1OUT ^= BIT6;
    } else {
        P1OUT &= ~BIT6;                          // Off Led & Alarm
        P1OUT &= ~BIT5;
        open_counter = 0;
    }
    P1REN &= ~BIT2;
    ADC10CTL0 &= ~ENC;                           // Disable ADC
    ADC10CTL0 &= ~(ADC10ON + REFON);
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR_HOOK(void) {
    extern unsigned int open_counter;
    ADC_Conversion_Result = ADC10MEM;            // Read ADC conversion result from ADC10MEM
    if (ADC_Conversion_Result<0x0266) open_counter = 400;
}

void ADC10_Init(void)
{
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
    ADC10CTL0 = ADC10IE | ADC10ON | REFON | REF2_5V | ADC10SHT_0 | SREF_1;

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

}
