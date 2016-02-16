// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         2/11/16
// Authors:      Evelyn Hunten
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"

#define RED 1
#define GRN 0
#define ENABLE 1
#define OFF 0

typedef enum stateTypeEnum{
    run, db1, db2, db3, db4, wait1, wait2, stop
} stateType;

volatile stateType state = run;

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initLEDs();
    initSW2();
    initTimer2();
    
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        switch (state) {
            case run: turnOnLED(GRN);
                break;
            case stop: turnOnLED(RED);
                break;
            case db1: delayUs(5);
                      state = wait1;
                break;
            case db2: delayUs(5);
                      state = stop;
                break;
            case db3: delayUs(5);
                      state = wait2;
                break; 
            case db4: delayUs(5);
                break;
            case wait1:
                break;
            case wait2:
                break; 
        }
        
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button


    IFS1bits.CNAIF = OFF;           //Put down the flag

    if (PORTAbits.RA7 == 0) {
        initTimer1();
        switch (state) {
            case run: state = db1;
            break;
            case stop: state = db3;
            break;
        }
            
    }
    else if (PORTAbits.RA7 == 1) {
        //stopTimer();
        IEC0bits.T1IE = 0;
        T1CONbits.ON = 0;
        
        switch (state) {
            case wait1: state = db2;
                break;
            case db2: state = wait2;
                break;
            case wait2: state = db4;
        }
    }
    
}


//Timer interrupt
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt () {
    
    IFS0bits.T1IF = OFF;
    
}