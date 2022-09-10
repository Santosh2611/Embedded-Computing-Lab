/* 
	p2_1.c Toggling green LED in C using header file register definitions.
	This program toggles green LED for 0.5 second ON and 0.5 second OFF.
	The green LED is connected to P2.1.
	The LEDs are high active (a '1' turns ON the LED).

	Tested with Keil 5.30 and MSP432 Device Family Pack V2.2.0 on 
	XMS432P401R Rev C.
*/

#include "msp.h"

void delayMs(int n); // Delay Function

// Main Function:
int main(void)
{
	P2->SEL1 &= ~2; // Configure P2.1 as Simple I/O
  P2->SEL0 &= ~2;
  P2->DIR |= 2; // P2.1 set as output pin

  // Infinite Loop (An embedded program does not stop):
	while (1)
	{
		P2->OUT |= 2; // Turn ON P2.1 Green LED
    delayMs(500); // Delay for 500 ms
    P2->OUT &= ~2; // Turn OFF P2.1 Green LED
    delayMs(500); // Delay for 500 ms
  }
}

// Delay milliseconds when system clock is at 3 MHz for Rev C MCU:
void delayMs(int n)
{
	int i, j;
  for (j = 0; j < n; j++)
		for (i = 750; i > 0; i--); // Delay of 1 ms
}
