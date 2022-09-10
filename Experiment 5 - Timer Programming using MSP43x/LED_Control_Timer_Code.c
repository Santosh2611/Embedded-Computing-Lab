#include "msp.h"
int temp = 0; // Variable for iteration, to turn LED ON and OFF consecutively.

// Main Function:
int main(void)
{
	P2->SEL0 &= ~2; // Configure functionality of P2.1 as simple GPIO pins 
	P2->SEL1 &= ~2;
	P2->DIR |= 2; // Configure direction of P2.1 as output for GREEN-LED
	
	SysTick->LOAD = 90000-1; // Reload register value for generating 30 milliseconds delay; MCLK = 30,00,000 Hz
	SysTick->VAL = 0; // Clear STCurrent Value Register
	SysTick->CTRL = 5; // Enables SysTick to begin counting down; Interrupt generation is disabled; System clock MCLK
	P2->OUT |= 2; // Turn ON P2.1 Green LED
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		// The SysTick has counted down to zero:-
		if(SysTick->CTRL & 0x10000) // If COUNTFLAG is set
			
			// Generate 40 milliseconds delay:-
			if (temp % 2 == 0) 
			{
				SysTick->LOAD = 120000-1;
				SysTick->VAL = 0;
				SysTick->CTRL = 5;
				P2->OUT &= ~2; // Turn OFF P2.1 GREEN-LED	
			}
			
			// Generate 30 milliseconds delay:-	
			else
			{
				SysTick->LOAD = 90000-1;
				SysTick->VAL = 0;
				SysTick->CTRL = 5;
				P2->OUT |= 2; // Turn ON P2.1 GREEN-LED
			}
			
		temp++;
	}
}
