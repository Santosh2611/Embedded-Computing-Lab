#include "msp.h"

// Main Function:
int main (void)
{
	int result;
	
	P2->SEL0 &= ~2; // Configure functionality of P2.1 as simple GPIO pins 
	P2->SEL1 &= ~2;
	P2->DIR |= 2; // Configure direction of P2.1 as output for GREEN-LED
	
	ADC14->CTL0 = 0x00000010; // Power ON should be disabled during configuration
	ADC14->CTL0 = 0x04080300; // Sample-and-hold pulse-mode select, sysclk, 32 sample clocks, software trigger
	ADC14->CTL1 = 0x00000000; // Set resolution as 8-bit (9 clock cycle conversion time)
	ADC14->MCTL[5] = 6; // A6 input, single-ended, Vref = AVCC
	
	// Configure functionality of P4.7 as ADC pin and it's direction as input:-
	P4->SEL1 |= 0x80; 
	P4->SEL0 |= 0x80;

	// Convert for memory register 5:-
	ADC14->CTL1 |= 0x00050000; // Repeat single channel, sequence sample is active
	ADC14->CTL0 |= 2; // Enable ADC after conversion
	
	// Infinite Loop (An embedded program does not stop):
	while (1)
	{
		ADC14->CTL0 |= 1; // Start the conversion now
		while (!ADC14->IFGR0); // Wait for ADC conversion to complete 
		result = ADC14->MEM[5]; // Read ADC data register
		P2->OUT = result >> 8; // Display bit for GREEN-LED
		
		/* 
		Temperature Range - 0 degrees (0x00) to 60 degrees (0x11)
		If temperature goes above 28 degrees, turn ON the LED; else OFF.
		60 degrees = 256 bits (2^8 bit-resolution)
		Therefore, 28 degrees = ??? = (256 * 28) / 60 = 119.4667 ~ 120 bits (2^8 bit-resolution)
		In hexadecimal representation, (120)10 = (78)16
		*/
		
		if (result >= 0x78) 
		{
			P2->OUT |= 2; // Turn ON P2.1 GREEN-LED
		
		}		
		else
		{
			P2->OUT &= ~2; // Turn OFF P2.1 GREEN-LED
			
		}
	}
}
