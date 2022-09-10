#include "msp.h"
void UART0_init(void); // Function for UART Transmission
void delayMs (int n); // Delay Function

unsigned char c;
unsigned char message[] = "Ready\n";
int i;

// Main Function:
int main (void)
{
	UART0_init (); // Call UART Transmission Function
	
	for(i = 0; i < 7; i++)
	{
		while (!(EUSCI_A0-> IFG & 0x02)) { } // Wait until transmitter buffer is empty
		EUSCI_A0 -> TXBUF = message[i]; // Send a character
	}
	
	// Infinite Loop (An embedded program does not stop):
	while (1)
	{
		while (!(EUSCI_A0-> IFG & 0x02)) { } // Wait until transmitter buffer is empty
		c = EUSCI_A0 -> RXBUF; // Receive a character
		
		while (!(EUSCI_A0-> IFG & 0x02)) { } // Wait until transmitter buffer is empty		
		EUSCI_A0 -> TXBUF = c; // Display the character		
	}
}

// Function for UART Transmission:
void UART0_init(void)
{
	EUSCI_A0 -> CTLW0 |= 1; // Put in reset mode to configue UART 
	EUSCI_A0 -> MCTLW = 0; // Disable oversampling
	EUSCI_A0 -> CTLW0 = 0x0081; // 00 - 1 stop bit, No Parity, 8-bits data, Asynchronous Mode, First LSB Then MSB, SMCLK
															// 81 -  Enabled EUSCI_A0 logic is held in reset state
	EUSCI_A0 -> BRW = 26; // 3000000/115200 = 26
	P1 -> SEL0 |= 0x0C; // Configure functionality of P1.2, P1.3 as UART Pins 
	P1 -> SEL1 &=~ 0x0C;
	EUSCI_A0 -> CTLW0 &= ~1; // Take UART out of reset mode
}

// Delay milliseconds when system clock is at 3 MHz for Rev C MCU:
void delayMs(int n)
{
	int i, j;
  for (j = 0; j < n; j++)
		for (i = 750; i > 0; i--); // Delay of 1 ms
}	
