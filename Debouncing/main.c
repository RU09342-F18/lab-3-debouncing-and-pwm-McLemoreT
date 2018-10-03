#include <msp430.h> 


#define LED1    BIT0    // Defines LED at P1.0
#define LED2    BIT6    // Defines LED at P1.6
#define BUTTON  BIT3    // Defines BUTTON at P1.3

int main(void)
{
        WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

        P1DIR |= LED1;               //Set Port 1.0 as an output
        P1OUT &= ~LED1;              //Set the initial value of port 1.0 as "0"

        P1DIR &= ~BUTTON;              //Set Port 1.3 as an input
        P1REN |= BUTTON;               //Turn on the pull-up resistor for port 1.3
        P1OUT |= BUTTON;               //Set the initial value of port 1.3 as "1"

        P1IE |=  BUTON;                            // P1.3 interrupt enabled
        P1IES |= BUTTON;                            //falling edge
        P1REN |= BUTTON;                            // Enable resistor on SW2 (P1.3)
        P1OUT |= BUTTON;                            //Pull up resistor on P1.3
        P1IFG &= ~BUTTON;                           // P1.3 Interrupt Flag cleared
	return 0;
}
