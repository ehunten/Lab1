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
    run, db1, db2, db3, db4, db5, db6, wait1, wait2, wait3, stop, stop_buffer, reset, timer
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
    
    int count = 0;
//    int i = 0;
//    char str[] = "default";
    
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        switch (state) {
            case run: turnOnLED(GRN);
                //display LCD stuff
                clearLCD();
                printStringLCD("Running: ");
                state = timer;
            //getTimeString();
                break;
            case stop: turnOnLED(RED);
            clearLCD();
            printStringLCD("Stopped: ");//display LCD stuff
            moveCursorLCD();
            timerDisplayLCD(count);
            state = stop_buffer;
                break;
            case stop_buffer:
                break;
            case timer:
                count += 1;
                moveCursorLCD();
                timerDisplayLCD(count);
                //printStringLCD("MM:SS:FF");
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
//            case db5:
//                delayUs(500);
//                state = wait3;
//                break;
//            case db6:
//                delayUs(500);
//                state = reset;
//                break;    
            case wait1:
                break;
            case wait2:
                break; 
            case wait3:
                break;
            case reset:
                TMR1 = 0;
                count = 0;
                timerDisplayLCD(count);
                printStringLCD("Reset");
                state = stop;
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


             //Put down the flag (external switch)
              // Put down the flag
    PORTA;
    PORTD;
    
        //ON BOARD SWITCH - RESET
        if(IFS1bits.CNDIF == 1) {
            IFS1bits.CNDIF = OFF; 
            if (PORTDbits.RD6 == 0) {
                if (state == stop_buffer) {
                    state = wait3;
                }
            }
            else if (PORTDbits.RD6 == 1){
            if (state == wait3) {
                state = reset;
            }
        }
        }
       
    //EXTERNAL SWITCH - RUN/STOP

        else if(IFS1bits.CNAIF == 1) {
            IFS1bits.CNAIF = OFF;      
            if (PORTAbits.RA7 == 0) {
                switch (state) {
                    case timer: state = db1;
                    break;
                    case stop_buffer: state = db3;
                    break;
                }
            }
            else if (PORTAbits.RA7 == 1) {
                switch (state) {
                    case wait1: state = db2;
                    //case timer: state = db2;  
                    break;
                    case wait2: state = db4;
                    //case stop_buffer: state = db4;   
                    break;
                    }
                }   
        }

}


//Timer interrupt
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt () {
    //This interrupt is for the timing of the stopwatch
    IFS0bits.T1IF = OFF;
    //count += 1;
}