#include <msp430.h> 
#include <stdint.h>
/*
 * Simple introduction to input and interrupts.
 *
 * In this sample you will learn about GPIO input tracking. There are two ways to look at the input of a pin. The first, which
 * you are more familiar with is polling. polling requires you to call a function from time to time to check the state of a pin.
 * while polling is simple, it is processor intensive and you can miss events if you don't poll at a high enough frequency (more on this later)
 * you will see in this example that we set up the two buttons on the launch pad for input. one of the pins (pin 1.1) is set up to be used by interrupts,
 * and the other pin (pin 2.1) is set up to be used by polling. You must read the family user's guide section on interrupts and some general
 * knowledge on interrupts to understand how this example works. you will notice the function sillyLEDShow(); and port1ISR are never called from main,
 * however when you press button 1.1 sillyLEDShow(); will be executed from port1ISR. You will also notice that if you press button 2.1 the slow led show
 * will run. when the slow led show is running press pin 1.1 in, what happens?
 */

// initializes pin 1.1 for interrupts
void setPin1_1UpForInterrupts()
{
    // ensure the direction is set to input of the button
    P1DIR &= ~(BIT1);

    // enable the pull up resistor, this causes the button circuit to idle at logic high
    // when the button is pressed the circuit will be forced to logic low
    P1REN |= BIT1;
    P1OUT |= BIT1;

    // trigger interrupt source on falling edge of signal
    P1IES |= BIT1;

    // enable interrupts on pin 1.1
    P1IE |= BIT1;
}

// returns the state of the button on pin 2.1.
// returns 0 if the pin is logic low (ie button is pressed)
// returns 1 if the pin is high (ie button is not pressed)
uint8_t pollInput()
{
    return (uint8_t)(P2IN & BIT1);
}

// blinks both the LEDS at the same time
void sillyLEDShow()
{
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT7;

    __delay_cycles(100000);
    P1OUT |= BIT0;
    P4OUT |= BIT7;

    __delay_cycles(100000);
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT7;
}

void slowLinearLightShow()
{
    unsigned long i = 0;
    unsigned long j = 0;

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

void fastLinearLightShow()
{
    unsigned long i = 0;
    unsigned long j = 0;

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
}

void exponentialLightShow()
{
    unsigned long i = 0;
    unsigned long j = 0;

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
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer. From what I've read, this line of code is needed at the beginning of most MSP430 projects.
                                // Doing this turns off the watchdog timer, which can reset the device after a certain period of time.
                                // It seems like that could be handy to prevent periodic bugs for microcontrollers in appliances that don't need to store on-board data.
                                // Watchdog timers are good for a fail safe mechanism that garuntees your MCU cannot get stuck in a loop forever. However WDT resets are a symptom
                                // of a dangerous bug in your code. If the MCU is resetting because you get trapped in a loop then your code is faulty.

    // Set the GPIO registers for the pin to output mode.
	P1DIR |= BIT0; //setting the direction of P1.0 to output mode(1). It looks like P1.0 stands for pin 1, port 0(BIT0 is 0x00)
	P4DIR |= BIT7; //Similarly, we set the direction of P4.7 to output mode(1). Again P4.7 stands for pin 4, port 7(BIT7 is 0x80)

	// Drive the output of each pin low, by clearing the pin out register bits.
	P1OUT &= ~BIT0; //since BIT0 sets the 0th port to one, taking the ones complement sets it to zero(turns off red led)
	P4OUT &= ~BIT7; //similarly, BIT7 sets the 7th port to one, so takig the ones complement sets it to zero(turns off green led)

    // ensure the direction is set to input of the button
    P2DIR &= ~(BIT1);

    // enable the pull up resistor, this causes the button circuit to idle at logic high
    // when the button is pressed the circuit will be forced to logic low.
    P2REN |= BIT1;

    // now drive the output so we can actually idle high
    P2OUT |= BIT1;

    // setup pin1.1 for interrupts and enable the global interrupt flag
	setPin1_1UpForInterrupts();
	_enable_interrupts();

	while (1)
	{
	    if (!pollInput())
	        slowLinearLightShow();
	}
}

// interrupt service routine assigned to pin 1.1 - runs the silly LED show when the button is pressed
#pragma vector=PORT1_VECTOR
__interrupt void port1ISR (void)
{
    // run the LED show (note in general using delays in interrupts is bad practice - more on this later as well)
    sillyLEDShow();

    // clear the interrupt flag
    P1IFG &= ~BIT1;
}
