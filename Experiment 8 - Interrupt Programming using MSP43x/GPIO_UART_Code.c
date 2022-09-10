#include "msp.h"
#include <string.h>

void UART0_init(void);
void delayMs(int n);
char ch, str[5], case1[3] = "aaa", case2[5] = "bbbbb";
int i = 0;

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

    while(1) {
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
	while (ch != '\n')
  {
		ch = EUSCI_A0->RXBUF;  /* read the receive char and set the LEDs */
													/* interrupt flag is cleared by reading RXBUF */
    str[i] = ch;
    i++;
  }
	
	if (strcmp (str, case1) == 0) {
		/* toggle green LED (P2.1) two times */
		for (i = 0; i < 2; i++)
		{
			P2->OUT |= 0x02;
      delayMs(500);
      P2->OUT &= ~0x02;
      delayMs(500);
    }
	}
		
	else if (strcmp (str, case2) == 0) {
			/* toggle red LED (P2.0) three times */
			for (i = 0; i < 3; i++)
			{
        P2->OUT |= 0x01;
        delayMs(500);
        P2->OUT &= ~0x01;
        delayMs(500);
			}
		}
	
	else {
		/* toggle the red LED (P2.0) and green LED (P2.1) continuously */
		P2->OUT |= 0x01;
    delayMs(500);
    P2->OUT &= ~0x01;
    delayMs(500);
			
		P2->OUT |= 0x02;
    delayMs(500);
    P2->OUT &= ~0x02;
    delayMs(500);
	}
} 

/* delay n milliseconds (3 MHz CPU clock) */
void delayMs(int n) {
    int i, j;

    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);   /* do nothing for 1 ms */
} 
