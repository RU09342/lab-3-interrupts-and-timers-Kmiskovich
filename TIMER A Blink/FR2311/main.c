/*
 * Kevin Miskovich
 * Lab 3 Part 2
 * FR2311
 */
#include<msp430.h>

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;                // Disable Watchdog Timer
    PM5CTL0 &= ~LOCKLPM5;		     //For FRx Boards

    P1SEL =0;                                //Enable I/O mode for 1
    P2SEL =0;				     //Enable I/O for 2
    P1DIR |= BIT0;                           //Set Pin 1.0 [LED1] to output                              
    P2DIR |= BIT0;                           //Set Pin 2.0 [LED2] to output

    //Timer0_A0 Start
    TA0CCTL0 = CCIE;                         // CCR0 interrupt enabled
    TA0CCR0 = 25000;                         //Timer0 Frequency
    TA0CTL = TASSEL_1 + MC_1;                //TASSEL1 for ACLK, MC1 for up mode

    //Timer1_A0 Start
    TA1CCTL0 = CCIE;                         //TACCR0 Interrupt enabled
    TA1CCR0 = 50000;                         //Timer1 Frequency
    TA1CTL = TASSEL_1 + MC_1;

    __enable_interrupt();                    // Enables General Interrupt
    _BIS_SR(LPM4_bits + GIE);                //enter low power mode and enable global interrupt
}
//Timer0 A0 ISR
#pragma vector=TIMER0_A0_VECTOR               //Interrupt routine
__interrupt void Timer0_A0_ISR (void)
{
    P1OUT ^= BIT0;                            //Toggle LED on Timer0
}
//Timer1 A0 ISR
#pragma vector = Timer1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void)
{
    P2OUT ^= BIT0;                            //Toggle LED on Timer1
}
