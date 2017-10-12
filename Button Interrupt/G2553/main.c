/**
 * Kevin Miskovich
 * Lab 3 Part 1: Button Interrupt
 * G2553
 */
#include <msp430.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
	P1SEL = 0;                  //select I/O mode
	P1DIR |= BIT0;              //set Port 1.0 output [LED]
	P1DIR &= (~BIT3);           //set Port 1.3 input [pushbutton]
	
	P1REN |= BIT3;              //enable resistor
	P1OUT |= BIT3;              //enable pull up resistor

	P1IE |= BIT3;               //enable interrupt on Port 1.3
	P1IES |= BIT3;              //set as falling edge
	P1IFG &= ~(BIT3);           //clear interrupt flag for Port 1.3

	_BIS_SR(LPM4_bits + GIE);   //enter low power mode and enable global interrupt
}
    //Port 1 ISR
    #pragma vector=PORT1_VECTOR
    __interrupt void Port_1(void)
    {
        P1OUT ^= 0x01;          //trigger the LED
        P1IFG &= ~(BIT3);       //clear interrupt flag for Port 1.3
    }
