#include <msp430.h> 


#define LED1    BIT0    // Defines LED at P1.0
#define LED2    BIT6    // Defines LED at P1.6
#define BUTTON BIT3     // Defines BUTTON at P1.3

int main(void)
{
        WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

        P1DIR |= LED;               //Set Port 1.0 as an output
        P1OUT &= ~LED;              //Set the initial value of port 1.0 as "0"

        P1DIR &= ~Btn;              //Set Port 1.3 as an input
        P1REN |= Btn;               //Turn on the pull-up resistor for port 1.3
        P1OUT |= Btn;               //Set the initial value of port 1.3 as "1"

        P1IE |=  BIT3;                            // P1.3 interrupt enabled
        P1IES |= BIT3;                            //falling edge
        P1REN |= BIT3;                            // Enable resistor on SW2 (P1.3)
        P1OUT |= BIT3;                            //Pull up resistor on P1.3
        P1IFG &= ~BIT3;                           // P1.3 Interrupt Flag cleared
	return 0;
}
