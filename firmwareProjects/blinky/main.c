#include <msp430.h> 

/*
 * Simple introduction project that blinks both the LEDs on the dev kit.
 *
 * This project utilizes GPIO pins on the MSP430 to control two LEDs on the dev kit. We also utilize
 * a built in delay function which allows us to delay the processor to control the blinking pattern.
 *
 * You will need to read up about GPIO (General Purpose Input Output) pins, and their various uses.
 * I assume you understand the basics of LEDs (Light Emitting Diodes) however if you want to
 * learn more read up on those as well!
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // Set the GPIO registers for the pin to output mode.
	P1DIR |= BIT0;
	P4DIR |= BIT7;

	// Drive the output of each pin low, by clearing the pin out register bits.
	P1OUT &= ~BIT0;
	P4OUT &= ~BIT7;

	// Turn on one of the LEDs so we alternate them.
	P4OUT |= BIT7;

	while (1)
	{
	    __delay_cycles(20000);  // delay for 20,000 clock cycles. The duration in time is dependent on the clock frequency.

	    // Toggle the output register bits to change the state of the LED
	    P1OUT ^= BIT0;
	    P4OUT ^= BIT7;

	    __delay_cycles(20000);

        // Toggle the output register bits to change the state of the LED
        P1OUT ^= BIT0;
        P4OUT ^= BIT7;
	}
}