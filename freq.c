/* 
 * Program test changing the clock frequency to the MSP430G2553 Launchpad
 * Author: Joao Dantas
 * Date: Mar 2016
 * 
 * Packages needed: msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
 * Usage:
 * 	make comp 
 *	make debug
 *  (mspdebug) prog freq.elf
 *  (mspdebug) run
 *
 *	The switch button changes the clock frequency.
 *
 */

#include "msp430g2553.h"

#define SWITCH              BIT3
#define SWITCH_PRESSED      0x00

#define RED                 BIT0

int main(void) {
    /* Disabling watchdog */
    WDTCTL = WDTPW + WDTHOLD;

    /* Setting up Switch */
    P1DIR &= ~SWITCH;				// Set the switch pin to input
    P1REN |= SWITCH;				// Use an internal resistor
    P1OUT |= SWITCH;				// The internal resistor is pullup

    /* Setting up Launchpad LEDs */
    P1DIR |= RED;					// Launchpad LEDs for output
    P1OUT &= ~RED;					// Red LED off at startup

    unsigned int MOD = 0;
    unsigned int TIMER = 100000;

	while (1) {
		if ((P1IN & SWITCH) == SWITCH_PRESSED) {
		/* Hang until the switch is released. */
		    while ((P1IN & SWITCH) == SWITCH_PRESSED);

	    	MOD++;
	    	if (MOD > 3) 
	    		MOD = 0;

	    	switch(MOD) {
	    		case 0:
		    		BCSCTL1 = CALBC1_1MHZ;
		    		DCOCTL = CALDCO_1MHZ;
		    		break;
		    	case 1:
		    		BCSCTL1 = CALBC1_8MHZ;
		    		DCOCTL = CALDCO_8MHZ;
		    		break;
		    	case 2:
		    		BCSCTL1 = CALBC1_12MHZ;
		    		DCOCTL = CALDCO_12MHZ;
		    		break;
		    	case 3:
		    		BCSCTL1 = CALBC1_16MHZ;
		    		DCOCTL = CALDCO_16MHZ;
		    		break;
		    	default:
		    		BCSCTL1 = CALBC1_1MHZ;
		    		DCOCTL = CALDCO_1MHZ;
	    	}
	    }
	    P1OUT ^= RED;
		for(unsigned volatile int i = 0; i < TIMER; i++);
    }

    return 0;
}
