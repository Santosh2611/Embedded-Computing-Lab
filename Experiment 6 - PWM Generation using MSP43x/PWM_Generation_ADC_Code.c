#include "msp.h"

// Main Function:-
int main(void)
{
	int result;
	
	P2->SEL0 |= 0x20; // Configure functionality of P2.5 as simple GPIO pin 
	P2->SEL1 &= ~0x20;
	P2->DIR |= 0x20; // Configure direction of P2.5 as output for timer
	
	P4->SEL1 |= 0x80; // Configure functionality of P4.7 as simple GPIO pin
	P4->SEL0 |= 0x80; // Configure direction of P4.7 as input for ADC
	
	ADC14->CTL0 = 0x00000010; // Power ON should be disabled during configuration 
	ADC14->CTL0 |= 0x04080300; // Sample-and-hold pulse-mode select, sysclk, 32 sample clocks, software trigger
	ADC14->CTL1 = 0x00000020; // Set resolution as 12-bit (14 clock cycle conversion time)

	// Convert for memory register 10:-
	ADC14->CTL1 |= 0x000a0000; // Repeat single channel, sequence sample is active
	ADC14->CTL0 |= 2; // Enable ADC after configuration
	
	// Infinite Loop (An embedded program does not stop):-
	while(1)
	{
		while(!ADC14->IFGR0); // Wait for ADC conversion to complete
		result = ADC14->MEM[10]; // Read ADC data register
		
		// Configure timer A0.2 as PWM pin:-
		TIMER_A1->CCR[0] = 1000-1; // PWM Period 
		result = result >> 8;
		TIMER_A1->CCR[2] = result; // PWM Duty Cycle   
		TIMER_A1->CCTL[2] = 0x40; // Compare mode; Toggle/reset output mode; Interrupt disabled; No interrupt pending

		
		/* Timer did not overflow; Disable interrupt; Clear TimerA; Up/down mode;
			 Input divider - Divide by 1; Clock source select - SMCLK (internal clock) */
		TIMER_A1->CTL = 0x0234;
	}
}
