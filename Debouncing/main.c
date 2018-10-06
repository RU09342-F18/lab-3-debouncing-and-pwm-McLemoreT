#include <msp430.h>


#define LED1    BIT0    // Defines LED at P1.0
#define LED2    BIT6    // Defines LED at P1.6
#define BUTTON  BIT3    // Defines BUTTON at P1.3
int IsTrue = 0;
//we want 200 ns of delay
void DeviceSetup();
void DoThing();
int main(void)
{
    DeviceSetup();
    TA0CTL = TASSEL_2 + ID_0 + MC_0;           // SMCLOCK, no division, clock stopped
    TA0CCR0 = 1600;                     //Time A0 will count up to 1600
    TA0CCTL0 = 0x0010;                  // Enables Capture/compare register for interrupt of timer A0
    __enable_interrupt();               //Enable interrupts
    __bis_SR_register(LPM0 + GIE);      // Low Power Mode w/ general interrupts enabled
}

void DeviceSetup(){//Set the device up for working
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= LED1;               //Set Port 1.0 as an output
    P1OUT &= ~LED1;              //Set the initial value of port 1.0 as "0"

    P1DIR &= ~BUTTON;              //Set Port 1.3 as an input
    P1REN |= BUTTON;               //Turn on the pull-up resistor for port 1.3
    P1OUT |= BUTTON;               //Set the initial value of port 1.3 as "1"

    P1IE |=  BUTTON;                            // P1.3 interrupt enabled
    P1IES |= BUTTON;                            //falling edge
    P1REN |= BUTTON;                            // Enable resistor on SW2 (P1.3)
    P1OUT |= BUTTON;                            //Pull up resistor on P1.3
    P1IFG &= ~BUTTON;                           // P1.3 Interrupt Flag cleared
}

void DoThing(){
    P1OUT ^= LED1;                      // Toggle LED
}
#pragma vector=PORT1_VECTOR //Button Interrupt
__interrupt void Port_1(void)

{
    P1OUT ^= LED2;
if(IsTrue == 0){
IsTrue = 1;         //set public variable to true
TA0CTL = MC_1;      //start the timer
DoThing();
}
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer (void)
{
    //P1OUT ^= LED2;
    if(IsTrue == 1){
    IsTrue = 0;
    TA0CTL = MC_0;                      // Stop timer
    P1IFG = 0x0000;                     // Clear timer interrupt flag
    P1IE &= ~BUTTON;                     //reset Button interrupt

    }else{
    //    P1IFG = 0x0000;                     // Clear timer interrupt flag
    }
}
