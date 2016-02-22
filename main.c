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
#include "lcd.h"
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"

#define RED 1
#define GRN 0
#define ENABLE 1
#define OFF 0

typedef enum stateTypeEnum{
    run, db1, db2, db3, db4, wait1, wait2, stop, reset
} stateType;

volatile stateType state = run;

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();                   //This function is necessary to use interrupts.
    initLEDs();
    initTimer2();
    initSW();
    initSW2();
    initTimer1();
    initLCD();
    clearLCD();
    
    int i = 0;
    
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        switch (state) {
            case run: turnOnLED(GRN);
            //display LCD stuff
            clearLCD();
            printStringLCD("Running: ");
            //getTimeString();
                break;
            case stop: turnOnLED(RED);
            clearLCD();
            printStringLCD("Stopped: ");
            //display LCD stuff
                break;
            case db1: delayUs(500);
                      state = wait1;
                break;
            case db2: delayUs(500);
                      state = stop;
                break;
            case db3: delayUs(500);
                      state = wait2;
                break; 
            case db4: delayUs(500);
                      state = run;
                break;
            case wait1:
                break;
            case wait2:
                break;                 
            case reset:
                TMR1 = 0;              //Reset TMR2
                break;
            default: clearLCD();
                break;
        }
        
    }
    
    return 0;
}

//Button Interrupt
void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button


    IFS1bits.CNAIF = OFF;           //Put down the flag
    IFS1bits.CNDIF = OFF;           // Put down the flag
    PORTA;
    PORTD;
    
        //ON BOARD SWITCH - RESET
        if (PORTDbits.RD6 == 0) {
            if (state == stop) {
                state = reset;
            }
        }
    //EXTERNAL SWITCH - RUN/STOP

        else if (PORTAbits.RA7 == 0) {
            switch (state) {
                case run: state = db1;
                break;
                case stop: state = db3;
                break;
            }

        }
        else if (PORTAbits.RA7 == 1) {

            switch (state) {
                case wait1: state = db2;
                    break;
                case wait2: state = db4;
                    break;
            }
        }
    

}


//Timer interrupt
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt () {
    //This interrupt is for the timing of the stopwatch
    IFS0bits.T1IF = OFF;
    
}