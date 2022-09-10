#include "msp.h"
void UART0_init(void); // Function for UART Transmission
unsigned char c;

// Main Function:
int main (void)
{
	UART0_init (); // Call UART Transmission Function
	
	P2->SEL1 &= ~2; // Configure functionality of P2.1 as simple GPIO port
	P2->SEL0 &= ~2;
	P2->DIR |= 2; // Configure direction of P2.1 as LED output
	
	// Infinite Loop (An embedded program does not stop):
	while (1)
	{
		while (!(EUSCI_A0-> IFG & 0x01)) { } // Wait until transmitter buffer is empty
		c = EUSCI_A0 -> RXBUF; // Receive a character
		
		if (c == 'A' || c == 'a')
		{
			P2->OUT |= 2; // Turn ON P2.1 Green LED
		}
		else if (c == 'B' || c == 'b')
		{
			P2->OUT &= ~2; // Turn OFF P2.1 Green LED
		}
	}
}

// Function for UART Transmission:
void UART0_init(void)
{
	EUSCI_A0 -> CTLW0 |= 1; // Put in reset mode to configue UART 
	EUSCI_A0 -> MCTLW = 0; // Disable oversampling
	EUSCI_A0 -> CTLW0 = 0x0081; // 00 - 1 stop bit, No Parity, 8-bit data, Asynchronous Mode, First LSB Then MSB, SMCLK
															// 81 -  Enabled EUSCI_A0 logic held in reset state
	EUSCI_A0 -> BRW = 26; // 3000000/115200 = 26
	P1 -> SEL0 |= 0x0C; // Configure functionality of P1.2, P1.3 as UART Pins 
	P1 -> SEL1 &=~ 0x0C;
	EUSCI_A0 -> CTLW0 &= ~1; // Take UART out of reset mode
}
