/*
* File:   timer.c
* Author: Evelyn Hunten
*
* Created 2/11/16
*/

#include <xc.h>
#include "timer.h"

#define PRESC1 0
#define PRESC8 1
#define CLEAR 0
#define ENABLE 1
#define DEFAULT 7
#define PRVAL 9


void initTimer1(){
    //Initialize timer 1
    IFS0bits.T1IF = CLEAR;          // Put the flag down
    TMR1 = CLEAR;                   // clear TMR1
    PR1 = 12499;                      // Initialize PR1 - should be 5milliseconds
    T1CONbits.TCKPS = PRESC8;     // Initialize pre-scalar
    T1CONbits.TCS = CLEAR;          // Set the oscillator
    IEC0bits.T1IE = ENABLE;         // Enable the interrupt
    IPC1bits.T1IP = DEFAULT;        // Configure the Interrupt Priority
    T1CONbits.ON = 0;          // Turn the timer on
}

void initTimer2(){
    IFS0bits.T2IF = CLEAR;          // Put the flag down
    TMR2 = CLEAR;                   //Clear TMR2
    PR2 = PRVAL;                    //Set PRvalue
    T2CONbits.TCKPS = PRESC1;       //Set prescalar
    T2CONbits.TCS = CLEAR;          //Set Oscillator
    IEC0bits.T2IE = ENABLE;         //enable interrupt
    IPC1bits.T1IP = DEFAULT;        //interrupt priority
    T2CONbits.ON = ENABLE;          //turn timer on
}
//Uses timer 1
void delayUs(unsigned int delay){
    //Create a delay using timer 2 for "delay" microseconds.
      TMR2 = 0;
      PR2 = delay*PRVAL;
      IFS0bits.T2IF = 0;
      T2CONbits.ON = 1;
      
      while (IFS0bits.T2IF == CLEAR);
      T2CONbits.ON = CLEAR;
      IFS0bits.T2IF = 0;
      
     
}


