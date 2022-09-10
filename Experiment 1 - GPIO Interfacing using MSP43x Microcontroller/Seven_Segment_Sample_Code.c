#include "msp.h"

void delayMs(int n);

// Main Function:
int main(void)
{
	const unsigned char digitPattern[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // Hexadecimal Values

	P4->SEL1 &= ~0xFF; // Configure P4 as Simple I/O
	P4->SEL0 &= ~0xFF;
	P4->DIR |= 0xFF; // P4 set as output pins
	
	P5->SEL1 &= ~2; // Configure P5.0, P5.1 as Simple I/O
	P5->SEL0 &= ~2;
	P5->DIR |= 2; // P5.0, P5.1 set as output pins
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		P4->OUT = digitPattern[7]; // Display Tens Digit
		P5->OUT |= 2; // Select Tens Digit
		delayMs(5000);
	}
}

// Delay milliseconds when system clock is at 3 MHz for Rev C MCU:
void delayMs(int n)
{
	int i, j;
  for (j = 0; j < n; j++)
		for (i = 750; i > 0; i--); // Delay of 1 ms
}
