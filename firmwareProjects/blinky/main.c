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
unsigned long i = 0;
unsigned long j = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer. From what I've read, this line of code is needed at the beginning of most MSP430 projects.
                                // Doing this turns off the watchdog timer, which can reset the device after a certain period of time.
                                // It seems like that could be handy to prevent periodic bugs for microcontrollers in appliances that don't need to store on-board data.

    // Set the GPIO registers for the pin to output mode.
	P1DIR |= BIT0; //setting the direction of P1.0 to output mode(1). It looks like P1.0 stands for pin 1, port 0(BIT0 is 0x00)
	P4DIR |= BIT7; //Similarly, we set the direction of P4.7 to output mode(1). Again P4.7 stands for pin 4, port 7(BIT7 is 0x80)

	// Drive the output of each pin low, by clearing the pin out register bits.
	P1OUT &= ~BIT0; //since BIT0 sets the 0th port to one, taking the ones complement sets it to zero(turns off red led)
	P4OUT &= ~BIT7; //similarly, BIT7 sets the 7th port to one, so takig the ones complement sets it to zero(turns off green led)

	// Turn on one of the LEDs so we alternate them.
	P4OUT |= BIT7; //since BIT7 sets the 7th port to one, or-ing the green led port(port 0x80) of pin 4 with BIT7 sets that port to 1(turns on the green led)

	while (1)
	{
	    //Exponential Visualization
        for (i = 50000; i > 0; i /= 2)
        {
            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P1OUT ^= BIT0; //exclusive or-ing with BIT0 will toggle the bit at port 0x00 (this is the same for pin 4, port 0x80 but I don't want to go down the line copying and pasting haha)

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P4OUT ^= BIT7;

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P1OUT ^= BIT0;

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P4OUT ^= BIT7;
        }
        //fast linear visualization
        for (i = 50000; i > 0; i -= 5000)
        {
            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P1OUT ^= BIT0;

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P4OUT ^= BIT7;

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P1OUT ^= BIT0;

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P4OUT ^= BIT7;
        }
        //slow linear visualization
        for (i = 50000; i > 0; i -= 500)
        {
            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P1OUT ^= BIT0;

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P4OUT ^= BIT7;

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P1OUT ^= BIT0;

            for (j = i; j > 0; j--){__delay_cycles(2);}
            // Toggle the output register bits to change the state of the LED
            P4OUT ^= BIT7;
        }
	}
}
