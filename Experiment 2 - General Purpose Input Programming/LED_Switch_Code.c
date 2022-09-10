/*
	www.microDigitalEd.com
  p2_5.c Read a switch and write it to the LED.
 
	This program reads an external switch connected to P1.1 and 
	writes the value to the RED-LED on P2.0. When switch is pressed, 
	it connects P1.1 to ground and bit 1 of P1IN reads as '0'. 
	
	P1.1 pin pull-up is enabled so that it is high when the switch is 
	not pressed and bit 1 of P1IN reads as '1'. The LEDs are high 
	active (a '1' turns ON the LED).
 
  Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
  on XMS432P401R Rev C.
*/

#include "msp.h"

// Main Function:
int main(void)
{
	P1->SEL1 &= ~2; // Configure P1.1 as simple GPIO Port
  P1->SEL0 &= ~2;	
  P1->DIR &= ~2; // Configure direction of P1.1 as input pin
	
  P1->REN |= 2; // P1.1 pull resistor enabled
  P1->OUT |= 2; // Pull up/down is selected by Px->OUT register

  P2->SEL1 &= ~1; // Configure P2.0 as simple GPIO Port
  P2->SEL0 &= ~1;
  P2->DIR |= 1; // Configure direction of P2.0 as output pin

  // Infinite Loop (An embedded program does not stop):
	while (1)
	{
		if (P1->IN & 2) // Use switch 1 to control the RED-LED
			P2->OUT &= ~1; // If not pressed, switch OFF RED-LED connected to P2.0
    else
      P2->OUT |= 1; // Else, switch ON RED-LED connected to P2.0
  }
}
