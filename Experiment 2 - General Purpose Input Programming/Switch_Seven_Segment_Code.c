#include "msp.h"
void delayMs(int n); // Delay Function
unsigned char i;

// Main Function:
int main(void)
{
	const unsigned char digitPattern[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 
	0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71}; // Define the hexadecimal values
	
	P1->SEL1 &= ~2; // Configure functionality of P1.1 as simple GPIO Port
	P1->SEL0 &= ~2;	
	P1->DIR &= ~2; // Configure direction of P1.1 as input pin
	
	P1->REN |= 2; // P1.1 pull resistor enabled
	P1->OUT |=2; // Pull up/down is selected by Px->OUT	register
	
	P4->SEL1 &= ~0xFF; // Configure functionality of P4 as simple GPIO Port
	P4->SEL0 &= ~0xFF;
	P4->DIR |= 0xFF; // Configure direction of Port 4 as output pins

	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		if (!(P1->IN & 2)) // Use switch 1 to control the external peripheral
		{
			for(i = 0; i < 17; i++)
			{
				P4->OUT |= digitPattern[i]; // Display Tens Digit
				P5->OUT |= 2; // Select Tens Digit
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
