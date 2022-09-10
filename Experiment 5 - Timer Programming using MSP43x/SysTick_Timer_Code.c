#include "msp.h"

// Main Function:
int main(void)
{
	P2->SEL0 &= ~2; // Configure functionality of P2.1 as simple GPIO pins 
	P2->SEL1 &= ~2;
	P2->DIR |= 2; // Configure direction of P2.1 as output for GREEN-LED
 
	SysTick->LOAD = 3000000-1; // Reload register value for generating 1 Hz or 1 sec delay; MCLK = 30,00,000 Hz
	SysTick->VAL = 0; // Clear STCurrent Value Register
	SysTick->CTRL = 5; // Enables SysTick to begin counting down; Interrupt generation is disabled; System clock MCLK 
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		// The SysTick has counted down to zero:-
		if(SysTick->CTRL & 0x10000) // If COUNTFLAG is set
			P2->OUT ^= 2; // Trigger the GREEN-LED
	}
}
