#include "msp.h"
void UART0_init(void); // Function for UART Transmission
void delayMs (int n); // Delay Function

// Main Function:
int main (void)
{
	UART0_init (); // Call UART Transmission Function
	
	// Infinite Loop (An embedded program does not stop):
	while (1)
	{
		while (!(EUSCI_A0 -> IFG & 0x02)) { } // Wait until transmitter buffer is empty
		EUSCI_A0 -> TXBUF = 'Y'; // Send a character
		while (!(EUSCI_A0 -> IFG & 0x02)) { } // Wait until transmitter buffer is empty
		EUSCI_A0 -> TXBUF = 'E'; // Send a character
		while (!(EUSCI_A0 -> IFG & 0x02)) { } // Wait until transmitter buffer is empty
		EUSCI_A0 -> TXBUF = 'S'; // Send a character
		delayMs(2); // Delay by 2 ms
	}
}

// Function for UART Transmission:
void UART0_init(void)
{
	EUSCI_A0 -> CTLW0 |= 1; // Put in reset mode to configure UART 
	EUSCI_A0 -> MCTLW = 0; // Disable oversampling
	EUSCI_A0 -> CTLW0 = 0x0081; // 00 - 1 stop bit for Txsion, NO Parity, 8-bits data, Asynchronous Mode, First LSB Then MSB, SMCLK
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
