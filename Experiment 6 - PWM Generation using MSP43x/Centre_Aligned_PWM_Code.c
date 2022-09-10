#include "msp.h"

// Main Function:
int main(void)
{
	// P2.7/PM_TA0.4:-
	P2->SEL0 |= 0x80; // Configure functionality of P2.7 as simple GPIO pin
	P2->SEL1 &= ~0x80;
	P2->DIR |= 0x80; // Configure direction of P2.7 as output for timer
	
	// Configure timer A0.4 as PWM pin:-
	TIMER_A0->CCR[0] = 400-1; // PWM Period
	TIMER_A0->CCR[4] = 250; // PWM Duty Cycle
	TIMER_A0->CCTL[4] = 0x40; // Compare mode; Toggle/reset output mode; Interrupt disabled; No interrupt pending
	
	/* Timer did not overflow; Disable interrupt; Clear TimerA; Up/down mode;
		 Input divider - Divide by 1; Clock source select - SMCLK (internal clock) */
	TIMER_A0->CTL = 0x0234; 
	
	// Infinite Loop (An embedded program does not stop):
	while(1){}
}
