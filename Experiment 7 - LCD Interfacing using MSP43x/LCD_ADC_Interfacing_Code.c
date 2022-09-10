#include "msp.h"
#include <stdio.h>

// LCD Interfacing - 8 bit Mode:-
#define RS 0x20 // Mask P3.5
#define RW 0x40 // Mask P3.6
#define EN 0x80 // Mask P3.7

void LCD_init(void); // Function to Configure LCD
void LCD_data(unsigned char data); // Display Character Using Data Write Function
void LCD_command(unsigned char command); // Display Character Using Command Write Function
void LCD_string(char word[]); // Display String Using Data Write Function
void delayMs(int n); // Delay milliseconds when system clock is at 3 MHz for Rev C MCU

// Main Function:
int main(void)
{
	int result;	float new_result;	char output[4];
	
	LCD_init(); // Call function to inialize LCD
	
	ADC14->CTL0 = 0x00000010; // Power ON should be disabled during configuration
	ADC14->CTL0 = 0x04080300; // Sample-and-hold pulse-mode select, sysclk, 32 sample clocks, software trigger
	ADC14->CTL1 = 0x00000020; // Set resolution as 12-bit (14 clock cycle conversion time)
	ADC14->MCTL[5] = 6; // A6 input, single-ended, vref = AVCC
	
	// Configure functionality of P5.7 for ADC pin A6 and direction as input:-
	P5->SEL1 |= 0x80; 
	P5->SEL0 |= 0x80;

	// Convert for memory register 5:-
	ADC14->CTL1 |= 0x00050000; // Repeat single channel, sequence sample is active
	ADC14->CTL0 |= 2; // Enable ADC after configuration
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		ADC14->CTL0 |= 1; // Start the conversion now
		while (!ADC14->IFGR0); // Wait for ADC conversion to complete 
		result = ADC14->MEM[5]; // Read ADC data register
		
		new_result = (result/2^12) * 5; // Calculate the voltage value from the ADC value
		/*
			sprintf stands for �String print�. 
			Instead of printing on console, it store output on char buffer which are specified in sprintf.
			That is, returns a formatted string.
		*/
		sprintf(output , "%f" , new_result); 
		
 		LCD_command(1); // Clear diplay (also clear DDRAM content)
		delayMs(500);		
		LCD_command(0x80); // Set DDRAM address or cursor position on display (First Line)
		delayMs(500);
		LCD_string(output);
		delayMs(500);
		LCD_command(0xC0); // Set DDRAM address or cursor position on display (Second Line)
		delayMs(500);
		
		if ( result > 0 && result <= ( (2^12) * (1/3) ) )
		{
			LCD_data('L'); LCD_data('O'); LCD_data('W');
			delayMs(500);
		}
		
		else if (result > ( (2^12) * (1/3) ) && result <= ( (2^12) * (2/3) ))
		{
			LCD_data('M'); LCD_data('E'); LCD_data('D'); 
			LCD_data('I'); LCD_data('U');	LCD_data('M');
			delayMs(500);
		}
			
		else
		{
			LCD_data('H'); LCD_data('I'); LCD_data('G'); LCD_data('H');
			delayMs(500);
		}			
	}		
}

// Function to Configure LCD:-
void LCD_init(void)
{
	// Set P4 LCD Data (D0 to D7) and P3.5,6,7 as RS, RW and EN as output:-
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
	delayMs(4);
}

// Display String Using Data Write Function:-
void LCD_string(char word[])
{
	int i;
	for (i = 0; word[i] != '\0'; i++)
	{
			LCD_data(word[i]);
	}
}

// Delay milliseconds when system clock is at 3 MHz for Rev C MCU:
void delayMs(int n)
{
	int i, j;
  for (j = 0; j < n; j++)
		for (i = 750; i > 0; i--); // Delay of 1 ms
}
