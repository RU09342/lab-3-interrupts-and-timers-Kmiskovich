/*
 * Kevin Miskovich
 * Lab 3 Part 3
 * F5994
 */
#include <msp430.h>
unsigned int f;
int start;
int end;
int flag = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                     // Stop Watchdog Timer

    P1DIR |= BIT0;                                // Set P1.0 as output
    P2OUT |= BIT1;                                // Set P2.1 as output
    P2REN |= BIT1;                                // enable register
    P2IE |= BIT1;                                 // interrupt enable
    P2IES |= BIT1;                                // falling edge
    P2OUT |= BIT1;                                // turn on Bit 1 of Port 2
    P2IFG &= ~BIT1;                               // turn off interrupt flags

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings

    // TimerA setup
    TA0CCTL0 = CCIE;                              // TACCR0 interrupt enabled
    TA0CCR0 = 205;                                // 20Hz
    f = 205;                                      // increment value for CCR0
    TA0CTL = TASSEL_1 + MC_2 + ID_3;              // ACLK, continuous mode, 4096 Hz

    __bis_SR_register(GIE);

    while(1)
    {
        if(flag)
        {
            flag = 0;
            if(end <= start)                            // overflow accommodation
            {
                TA0CCR0 = 65535 - start + end + TA0R;   // update cap compare reg value
                f = 65535 - start + end;                // update the increment value
            }
            else
            {
                TA0CCR0 = end-start+TA0R;
                f = end - start;
            }
        }
    }
}

//button interrupt
#pragma vector = PORT2_VECTOR
__interrupt void Port2(void)
{
    if(P2IES & BIT1)
    {
        start = TA0R;                 //time that the button was pressed
    }
    else
    {
        end = TA0R;                   //time that the button was released
        flag = 1;                     //turn off flag
    }
    P2IES ^= BIT1;                    //check for edge

    P2IFG &= ~BIT1;                   //clear P2 flag
}
// Timer A0 ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void)

{
        P1OUT ^= BIT0;
        TA0CCR0 += f;                  //increment CCR0 by f
}
