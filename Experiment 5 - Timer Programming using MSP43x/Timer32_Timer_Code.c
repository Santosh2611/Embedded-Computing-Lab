#include "msp.h"
 
// Main Function:
int main(void)
{
	P2->SEL0 &= ~2; // Configure functionality of P2.1 as simple GPIO pins 
	P2->SEL1 &= ~2;
	P2->DIR |= 2; // Configure direction of P2.1 as output for GREEN-LED
 
	TIMER32_1->LOAD = 3000000-1; // Reload register value for generating 1 Hz or 1 sec delay; MCLK = 30,00,000; Prescaler unit = 1
	
	/* Enables timer to begin counting down; Periodic mode; 
		 Disable timer interrupt enable; Set prescale bits to 00;
		 Clock is divided by 1; Select 32-bit counter operation;
		 Wrapping Mode (Timer 1 Timer Control Register)	*/
	TIMER32_1->CONTROL = 0xC2;
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		while((TIMER32_1->RIS & 1) == 0); // Wait until timer is completed (Timer 1 Raw Interrupt Status Register)
		TIMER32_1->INTCLR = 0; // Any write to the T32INTCLR1 register clears the interrupt output from the counter.
		P2->OUT ^= 2; // Trigger the GREEN-LED
	}
}
