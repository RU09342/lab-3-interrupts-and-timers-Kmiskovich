# Kevin Miskovich

## Button Based Delay
The codes in this project are written in C and are used to blink an LED on each of the boards listed below. Two interrupts had to be implemented: the timer interrupt (Timer A for all but FR2311, which Timer B was used).
The variables defined at the head of the code are for storing the start and end times of a given button press. 
The loop is implemented in order to check if flag is true, in which case it would record the time value and upon release, the flag is turned off.
When the ISR is reached, the LED is toggled and the capture compare register increments by value of f.

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
The FR2311 required the use of the Timer B module apart from the rest which ran off of the Timer A module.

## Usage
The Button Based Delay codes work as described above. By using the button, you are able to implement a delay based on the initial and final times.
