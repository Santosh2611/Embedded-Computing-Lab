#include "msp.h"

// Main Function:
int main (void)
{
	int result;
	
	P2->SEL0 &= ~7; // Configure functionality of P2.0, P2.1 and P2.2 as simple GPIO pins 
	P2->SEL1 &= ~7;
	P2->DIR |= 7; // Configure direction of P2.0, P2.1 and P2.2 as output for tri-color LEDs
	
	ADC14->CTL0 = 0x00000010; // Power ON should be disabled during configuration
	ADC14->CTL0 = 0x04080300; // Sample-and-hold pulse-mode select, sysclk, 32 sample clocks, software trigger
	ADC14->CTL1 = 0x00000020; // Set resolution as 12-bit (14 clock cycle conversion time)
	ADC14->MCTL[5] = 6; // A6 input, single-ended, vref = AVCC
	
	// Configure functionality of P4.7 for ADC pin A6 and direction as input:-
	P4->SEL1 |= 0x80; 
	P4->SEL0 |= 0x80;

	// Convert for memory register 5:-
	ADC14->CTL1 |= 0x00050000; // Repeat single channel, sequence sample is active
	ADC14->CTL0 |= 2; // Enable ADC after configuration
	
	// Infinite Loop (An embedded program does not stop):
	while (1)
	{
		ADC14->CTL0 |= 1; // Start the conversion now
		while (!ADC14->IFGR0); // Wait for ADC conversion to complete 
		result = ADC14->MEM[5]; // Read ADC data register
		P2->OUT = result >> 8; // Display bits 10:8 on tri-color LEDs	
	}
}
