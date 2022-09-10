#include "msp.h"

// LCD Interfacing - 8 bit Mode:-
#define RS 0x20 // Mask P3.5
#define RW 0x40 // Mask P3.6
#define EN 0x80 // Mask P3.7

void LCD_init(void); // Function to Configure LCD
void LCD_data(unsigned char data); // Display Character Using Data Write Function
void LCD_command(unsigned char command); // Display Character Using Command Write Function
void delayMs(int n); // Delay milliseconds when system clock is at 3 MHz for Rev C MCU

// Main Function:-
int main(void)
{
	LCD_init(); // Call function to initialize LCD
	
	// Infinite Loop (An embedded program does not stop):-
	while(1)
	{
		LCD_command(1); // Clear diplay (also clear DDRAM content)
		delayMs(500);		
		LCD_command(0x80); // Set DDRAM address or cursor position on display
		
		// Print "HELLO" on the LCD module:-
		LCD_data('H'); LCD_data('E'); LCD_data('L'); 
		LCD_data('L');	LCD_data('O');
		delayMs(500);
	}		
}

// Function to Configure LCD:-
void LCD_init(void)
{
	// Set P4 LCD Data (D0 to D7) and P3.5,6,7 as output for RS, RW, EN respectively:-
	P3->DIR |= RS|RW|EN;
	P4->DIR = 0xFF;	
	delayMs(30);
	
	LCD_command(0x30); // Function Set: 8-bit, 1 Line, 5X7 Dots
	delayMs(10);
	LCD_command(0x30); // Function Set: 8-bit, 1 Line, 5X7 Dots
	delayMs(1);
	LCD_command(0x30); // Function Set: 8-bit, 1 Line, 5X7 Dots
	
	LCD_command(0x38); // Function Set: 8-bit, 2 Lines, 5X7 Dots
	LCD_command(0x06); // Set the Entry Mode - Cursor Increment (Right Side), Display Shift OFF
	LCD_command(0x01); // Clear diplay (also clear DDRAM content)
	LCD_command(0x02); // Initialize Cursor to Home Position
	LCD_command(0x0C); // Display ON, Cursor OFF, Blink OFF 
}

// Display Character Using Data Write Function:-
void LCD_data(unsigned char data)
{
	P3->OUT |= RS; // RS = 1
	P3->OUT &= -RW; // R/W = 0
	P4->OUT |= data; // Move data to P4
	
	// Give LCD Enable Signal:-
	P3->OUT |= EN; // Pulse E HIGH
	delayMs(5);
	P3->OUT &= -EN; // Clear E
	delayMs(4);	// Wait for controller to do the display
}

// Display Character Using Command Write Function:-
void LCD_command(unsigned char command)
{
	P3->OUT |= -(RS | RW); // RS = 0, R/W = 0
	P4->OUT |= command; // Move command to P4 - Put command on the data bus
	
	// Give LCD Enable Signal:-
	P3->OUT |= EN; // Pulse E HIGH
	delayMs(5); 
	P3->OUT &= -EN; // Clear E
	delayMs(4);	// Wait for controller to do the display
}

// Delay milliseconds when the system clock is at 3 MHz for Rev C MCU:-
void delayMs(int n)
{
	int i, j;
  for (j = 0; j < n; j++)
		for (i = 750; i > 0; i--); // Delay of 1 ms
}
