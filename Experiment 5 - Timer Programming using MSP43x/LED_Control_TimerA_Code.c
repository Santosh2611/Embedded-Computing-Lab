#include "msp.h"
 
// Main Function:
int main(void)
{
	P2->SEL0 &= ~2; // Configure functionality of P2.1 as simple GPIO pins 
	P2->SEL1 &= ~2;
	P2->DIR |= 2; // Configure direction of P2.1 as output for GREEN-LED

	/*
		Timer overflowed; Interrupt disabled; Not clear; Up mode; 
		Interrupt divider; Select clock source as SMCLK
	*/
  TIMER_A1->CTL = 0x02D1;
	
  TIMER_A1->EX0 = 7; // Divider 2 = TAIDEX + 1 = 7 + 1 = 8
	TIMER_A1->CCR[0] = 47685 - 1; // For generating 1 Hz or 1 sec delay; Assume 2^ID = 8, TAIDEX = 7; SMCLK = 30,00,000
  
	// Infinite Loop (An embedded program does not stop):
	while(1) 
	{
		while((TIMER_A1->CCTL[0] & 1) == 0); // Wait until the CCIFG flag is set
		TIMER_A1->CCTL[0] &= ~1; // Clear interrupt flag
		P2->OUT ^= 2; // Trigger the GREEN-LED		
  }
}
