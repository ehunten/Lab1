/*
* File:   timer.c
* Author: Evelyn Hunten
*
* Created 2/11/16
*/

#include <xc.h>
#include "timer.h"

#define PRESC256 3
#define CLEAR 0
#define ENABLE 1
#define DEFAULT 7
#define PRVAL 6249


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

//Uses timer 2
void delayUs(unsigned int delay){
    //
      TMR2 = CLEAR;
      PR2 = delay*PRVAL;
      IFS0bits.T2IF = CLEAR;
      T2CONbits.ON = ENABLE;
      
      while (IFS0bits.T2IF == CLEAR) {
        T2CONbits.ON = CLEAR;
      }
     
}