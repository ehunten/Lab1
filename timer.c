/*
* File:   timer.c
* Author: Evelyn Hunten
*
* Created 2/11/16
*/

#include <xc.h>
#include "timer.h"
#include "lcd.h"

#define PRESC1 0
#define PRESC256 1
#define CLEAR 0
#define ENABLE 1
#define DEFAULT 7
#define PRVAL 1249


void initTimer1(){
    //Initialize timer 1
    IFS0bits.T1IF = CLEAR;          // Put the flag down
    TMR1 = CLEAR;                   // clear TMR1
    PR1 = 390;                      // Initialize PR1 - should be 10milliseconds
    T1CONbits.TCKPS = PRESC256;     // Initialize pre-scalar
    T1CONbits.TCS = CLEAR;          // Set the oscillator
    IEC0bits.T1IE = ENABLE;         // Enable the interrupt
    IPC1bits.T1IP = DEFAULT;        // Configure the Interrupt Priority
    T1CONbits.ON = ENABLE;          // Turn the timer on
}

void initTimer2(){
    IFS0bits.T2IF = CLEAR;          // Put the flag down
    TMR2 = CLEAR;                   //Clear TMR2
    PR2 = 9;                        //Set PRvalue
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

void timerDisplayLCD(int t)
{
    int mTens = 0;
    int mOnes = 0;
    int sTens = 0;
    int sOnes = 0;
    int fTenths = 0;
    int fHunds = 0;
    char str[] = "default";
    
    mTens = t / 600000;
    mOnes = (t - mTens*600000)/60000;
    sTens = (t - mTens*600000 - mOnes*60000)/1000;
    sOnes = (t - mTens*600000 - mOnes*60000 - sTens*1000)/100;
    fTenths = (t - mTens*600000 - mOnes*60000 - sTens*1000 - sOnes*100)/10;
    fHunds = (t - mTens*600000 - mOnes*60000 - sTens*1000 - sOnes*100 - fTenths*10)/1;
       
    sprintf(str, "%d", mTens);
    printStringLCD(str);
    printf(str, "%d", mOnes);
    printStringLCD(str);
    printStringLCD(":");
    sprintf(str, "%d", sTens);
    printStringLCD(str);
    sprintf(str, "%d", sOnes);
    printStringLCD(str);
    printStringLCD(":");
    sprintf(str, "%d", fTenths);
    printStringLCD(str);
    sprintf(str, "%d", fHunds);
    printStringLCD(str);
    
    return;
}
