/*
 * Kevin Miskovich
 * Lab 3 Part 3
 * FR2311
 */
#include <msp430.h>
unsigned int f;
int start;
int end;
int flag = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop Watchdog Timer
    PM5CTL0 &= ~LOCKLPM5;                         // For FRx boards- high-z removal

    P1DIR |= BIT0;                                // Set P1.0 as output
    P1OUT |= BIT1;                                // Set P2.1 as output
    P1REN |= BIT1;                                // enable register
    P1IE |= BIT1;                                 // interrupt enable
    P1IES |= BIT1;                                // falling edge
    P1OUT |= BIT1;                                // turn on Bit 1 of Port 2
    P1IFG &= ~BIT1;                               // turn off interrupt flags

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings

    // TimerB setup
    TB0CCTL0 = CCIE;                              // TBCCR0 interrupt enabled
    TB0CCR0 = 205;                                // 20Hz
    f = 205;                                      // increment value for CCR0
    TB0CTL = TBSSEL_1 + MC_2 + ID_3;              // ACLK, continuous mode, 4096 Hz

    __bis_SR_register(GIE);

    while(1)
    {
        if(flag)
        {
            flag = 0;
            if(end <= start)                            // overflow accommodation
            {
                TB0CCR0 = 65535 - start + end + TB0R;   // update cap compare reg value
                f = 65535 - start + end;                // update the increment value
            }
            else
            {
                TB0CCR0 = end-start+TB0R;
                f = end - start;
            }
        }
    }
}

//button interrupt
#pragma vector = PORT1_VECTOR
__interrupt void Port1(void)
{
    if(P1IES & BIT1)
    {
        start = TB0R;                 //time that the button was pressed
    }
    else
    {
        end = TB0R;                   //time that the button was released
        flag = 1;                     //turn off flag
    }
    P1IES ^= BIT1;                    //check for edge

    P1IFG &= ~BIT1;                   //clear P2 flag
}
// Timer A0 ISR
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void)

{
        P1OUT ^= BIT0;
        TB0CCR0 += f;                  //increment CCR0 by f
}
