/**
 * Kevin Miskovich
 * Lab 3 Part 1: Button Interrupt
 * FR2311
 */
#include <msp430.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
 	PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-z mode
	P1SEL = 0;                  //select I/O mode Port 1
	P1DIR |= BIT0;              //set Port 1.0 output [LED]
	P1DIR &= (~BIT1);           //set Port 1.1 input [pushbutton]
	
	P1REN |= BIT1;              //enable resistor
	P1OUT |= BIT1;              //enable pull up resistor

	P1IE |= BIT1;               //enable interrupt on Port 1.1
	P1IES |= BIT1;              //set as falling edge
	P1IFG &= ~(BIT1);           //clear interrupt flag for Port 1.1

	_BIS_SR(LPM4_bits + GIE);   //enter low power mode and enable global interrupt
}
    //Port 1 ISR
    #pragma vector=PORT1_VECTOR
    __interrupt void Port_1(void)
    {
        P1OUT ^= 0x01;          //trigger the LED
        P1IFG &= ~(BIT1);       //clear interrupt flag for Port 1.1
    }
