/* www.microDigitalEd.com
 * p6_1: Toggle red LED on P2.0 continuously. Upon pressing either
 * SW1 or SW2, the green LED of P2.1 should toggle for three times.
 * main program toggles red LED while waiting for interrupt from SW1 or SW2.
 * When green LED is blinking, the red LED ceases to blink.
 *
 * Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */

#include "msp.h"

void delayMs(int n);

int main(void) {
    __disable_irq();    /* global disable IRQs */

    /* configure P1.1, P1.4 for switch inputs */
    P1->SEL1 &= ~0x12;    /* configure P1.1, P1.4 as simple I/O */
    P1->SEL0 &= ~0x12;
    P1->DIR &= ~0x12;     /* P1.1, P1.4 set as input */
    P1->REN |= 0x12;      /* P1.1, P1.4 pull resistor enabled */
    P1->OUT |= 0x12;      /* Pull up/down is selected by P1->OUT */
    P1->IES |= 0x12;      /* make interrupt trigger on high-to-low transition */
    P1->IFG = 0;          /* clear pending interrupt flags */
    P1->IE |= 0x12;       /* enable interrupt from P1.1, P1.4 */

    /* configure P2.2-P2.0 for tri-color LEDs */
    P2->SEL1 &= ~7;       /* configure P2.2-P2.0 as simple I/O */
    P2->SEL0 &= ~7;

    P2->DIR |= 7;         /* P2.2-2.0 set as output */
    P2->OUT &= ~7;        /* turn all three LEDs off */

    NVIC_SetPriority(PORT1_IRQn, 3); /* set priority to 3 in NVIC */
    NVIC_EnableIRQ(PORT1_IRQn);      /* enable interrupt in NVIC */
    __enable_irq();                  /* global enable IRQs */

    /* toggle the red LED (P2.0) continuously */
    while(1) {
        P2->OUT |= 0x01;
        delayMs(500);
        P2->OUT &= ~0x01;
        delayMs(500);
    }
}

/* SW1 is connected to P1.1 pin, SW2 is connected to P1.4
 * Both of them trigger PORT1 interrupt */
void PORT1_IRQHandler(void) {
    int i;
    volatile int readback;
    /* toggle green LED (P2.1) three times */
    for (i = 0; i < 3; i++) {
        P2->OUT |= 0x02;
        delayMs(500);
        P2->OUT &= ~0x02;
        delayMs(500);
    }
    P1->IFG &= ~0x12; /* clear the interrupt flag before return */
}

/* delay n milliseconds (3 MHz CPU clock) */
void delayMs(int n) {
    int i, j;

    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);   /* do nothing for 1 ms */
} 
