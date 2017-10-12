# Kevin Miskovich

## Button Interrupt 
The codes in this project are written in C and are used to blink an LED with a 50% duty cycle on each of the boards listed below. The code sets up an interrupt to trigger when the button is pressed in order to toggle the LED. 
This is much more efficient than polling, since polling is constantly checking when to toggle, whereas interrupts wake the program in order to execute the function.

# The Following Boards Are Implemented:
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## Dependencies
This library only depends on the MSP430.h header file for TI MSP430 processors. This file is included in each of the C files. No other header files are required.

### The only peripherals being used are LED outputs and button inputs on each board:
* G2443: P1.0 [LED1] and P1.3 [S2]
* F5529: P1.0 [LED1] and P1.1 [S2]
* FR5594: P1.0 [LED1] and P5.5 [S2]
* FR2311: P1.0 [LED1] and P1.1 [S1]
* FR6989: P1.0 [LED1] and P1.1 [S1]

### Differences Between Boards
Most of the code is exactly the same for each processor, with the exception of the MSP430FRx microcontrollers, in which case you must turn off high impedance mode. Other than that, the only differences are pins, which are differentiated above.

## Usage
The button interrupt codes work when the LED is pressed. Pressing the button triggers the interrupt, which will toggle the LED then clear the interrupt flag.
