#include "msp.h"
void delayMs(int n); // Delay Function
unsigned char i;

// Main Function:
int main(void)
{
	P1->SEL1 &= ~2; // Configure functionality of P1.1 as simple GPIO Port
	P1->SEL0 &= ~2;	
	P1->DIR &= ~2; // Configure direction of P1.1 as input pin
	
	P1->REN |= 2; // P1.1 pull resistor enabled
	P1->OUT |=2; // Pull up/down is selected by Px->OUT	register
	
	P2->SEL1 &= ~7; // Configure functionality of P2.0, P2.1, P2.2 (RED, GREEN and BLUE LEDs) as simple GPIO Port
	P2->SEL0 &= ~7;
	P2->DIR |= 7; // Configure direction of P2.0, P2.1, P2.2 as output pin
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		if (!(P1->IN & 2)) // Use switch 1 to control the LEDs
		{
			for(i = 0; i <= 7; i++)
			{
				P2->OUT |= i; // If pressed, switch ON the LED connected to the corresponding port
				delayMs(500); // Delay of 500 ms
			}
		}			
	}
}

// Delay milliseconds when system clock is at 3 MHz for Rev C MCU:
void delayMs(int n)
{
	int i, j;
  for (j = 0; j < n; j++)
		for (i = 750; i > 0; i--); // Delay of 1 ms
}	
