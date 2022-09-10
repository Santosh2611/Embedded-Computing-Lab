/* www.microDigitalEd.com
 * p6_3.c UART0 Receive Interrupt Handling
 *
 * This program modifies p4_2.c to use interrupt to handle the UART0 receive.
 * It receives any key from terminal emulator (TeraTerm) of the host PC to the UART0
 * on MSP432 LaunchPad. The UART0 is connected to the XDS110 debug interface on the 
 * LaunchPad and it has a virtual connection to the host PC COM port.
 * 
 * Launch a terminal emulator (TeraTerm) on a PC and hit any key.
 * The tri-color LEDs are turned on or off according to the key received.
 *
 * By default the subsystem master clock is 3 MHz.
 * Setting EUSCI_A0->BRW=26 with oversampling disabled yields 115200 Baud.
 *
 * Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */
#include "msp.h"

void UART0_init(void);

int main(void) {
    __disable_irq();

    UART0_init();
    
    /* initialize P2.2-P2.0 for tri-color LEDs */
    P2->SEL1 &= ~7;           /* configure P2.2-P2.0 as simple I/O */
    P2->SEL0 &= ~7;
    P2->DIR |= 7;             /* P2.2-2.0 set as output */

    NVIC_SetPriority(EUSCIA0_IRQn, 4); /* set priority to 4 in NVIC */
    NVIC_EnableIRQ(EUSCIA0_IRQn);      /* enable interrupt in NVIC */
    __enable_irq();                    /* global enable IRQs */

    while (1) {
    }
}

void UART0_init(void) {
    EUSCI_A0->CTLW0 |= 1;     /* put in reset mode for config */
    EUSCI_A0->MCTLW = 0;      /* disable oversampling */
    EUSCI_A0->CTLW0 = 0x0081; /* 1 stop bit, no parity, SMCLK, 8-bit data */
    EUSCI_A0->BRW = 26;       /* 3000000 / 115200 = 26 */
    P1->SEL0 |= 0x0C;         /* P1.3, P1.2 for UART */
    P1->SEL1 &= ~0x0C;
    EUSCI_A0->CTLW0 &= ~1;    /* take UART out of reset mode */
    EUSCI_A0->IE |= 1;        /* enable receive interrupt */
}

void EUSCIA0_IRQHandler(void) {
    P2->OUT = EUSCI_A0->RXBUF;  /* read the receive char and set the LEDs */
                                /* interrupt flag is cleared by reading RXBUF */
} 
