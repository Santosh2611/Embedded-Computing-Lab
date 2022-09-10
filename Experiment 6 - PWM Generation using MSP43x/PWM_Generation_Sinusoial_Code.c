#include "msp.h"
int flag = 0;

// Main Function:
int main(void)
{
	P2->SEL1 |= 0x80; // Configure functionality of P2.7 as simple GPIO pin
	P2->SEL0 &= ~0x80;
	P2->DIR |= 0x80; // Configure direction of P2.7 as output for timer
	
	// Configure timer A0.4 as PWM pin:-
	TIMER_A0->CCR[0] = 999-1; // PWM Period
	TIMER_A0->CCR[4] = 250; // PWM Duty Cycle
	TIMER_A0->CCTL[4] = 0xF0; // Compare mode; Reset/set output mode; Interrupt enabled; No interrupt pending
	
	/* Timer did not overflow; Disable interrupt; Clear TimerA; Up mode;
		 Input divider - Divide by 1; Clock source select - SMCLK (internal clock) */
	TIMER_A0->CTL = 0x0214;  
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		while(TIMER_A0->CCTL[4] & 0xF1);
		TIMER_A0->CCTL[4] = 0xF0;
		
		if (TIMER_A0-> CCR[4] == 1000)
		{
			flag = -1;
			TIMER_A0-> CCR[4] += flag*200;
		}
		
		else if (TIMER_A0-> CCR[4] == 0)
		{
			flag = 1;
			TIMER_A0-> CCR[4] += flag*200;
		}
		
		else 
			TIMER_A0-> CCR[4] += flag*200;
	}
}
