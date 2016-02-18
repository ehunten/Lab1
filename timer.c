/*
* File:   timer.c
* Author: Evelyn Hunten
*
* Created 2/11/16
*/

#include <xc.h>
#include "timer.h"

#define PRESC256 1
#define CLEAR 0
#define ENABLE 1
#define DEFAULT 7
#define PRVAL 1249


void initTimer1(){
    //Initialize timer 1
    IFS0bits.T1IF = CLEAR;          // Put the flag down
    TMR1 = CLEAR;                   // clear TMR1
    PR1 = 195;                      // Initialize PR1 - should be 5milliseconds
    T1CONbits.TCKPS = PRESC256;     // Initialize pre-scalar
    T1CONbits.TCS = CLEAR;          // Set the oscillator
    IEC0bits.T1IE = ENABLE;         // Enable the interrupt
    IPC1bits.T1IP = DEFAULT;        // Configure the Interrupt Priority
    T1CONbits.ON = ENABLE;          // Turn the timer on
}

void initTimer2(){
    TMR2 = 0;
    T2CONbits.TCKPS = 0;
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
}
//Uses timer 1
void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    //delays 1 ms * delay
    //TODO CHANGE TO MICROSECONDS
      TMR1 = 0;
      PR1 = delay*PRVAL;
      IFS0bits.T1IF = 0;
      T1CONbits.ON = 1;
      
      while (IFS0bits.T1IF == CLEAR) {
        T1CONbits.ON = CLEAR;
      }
     
}
