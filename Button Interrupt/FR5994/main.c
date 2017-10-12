/**
 * Kevin Miskovich
 * Lab 3 Part 1: Button Interrupt
 * FR5994
 */
#include <msp430.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
 	PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-z mode
	P1SEL = 0;                  //select I/O mode Port 1
	P1DIR |= BIT0;              //set Port 1.0 output [LED1]
	P5DIR &= (~BIT5);           //set Port 5.5 input [s2]
	
	P5REN |= BIT5;              //enable resistor
	P5OUT |= BIT5;              //enable pull up resistor

	P5IE |= BIT5;               //enable interrupt on Port 5.5
	P5IES |= BIT5;              //set as falling edge
	P5IFG &= ~(BIT5);           //clear interrupt flag for Port 5.5

	_BIS_SR(LPM4_bits + GIE);   //enter low power mode and enable global interrupt
}
    //Port 5 ISR
    #pragma vector=PORT5_VECTOR
    __interrupt void Port_5(void)
    {
        P1OUT ^= 0x01;          //trigger the LED
        P5IFG &= ~(BIT5);       //clear interrupt flag for Port 5.5
