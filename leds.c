/*
* File:   leds.c
* Author: Evelyn Hunten
*
* Created 2/11/16
*/

#include <xc.h>
#include "leds.h"


#define LEDON 1
#define LEDOFF 0
#define ENABLE 0
#define OUT 0
#define GRN 0
#define RED 1


void initLEDs(){
    //Initialize the appropriate pins to work with the LEDs
    TRISGbits.TRISG12 = OUT;        //initialize LED1 - TRD1
    TRISGbits.TRISG14 = OUT;        //initialize LED2 - TRD2
    
    ODCGbits.ODCG12 = ENABLE;       //Enable open drain collector
    ODCGbits.ODCG14 = ENABLE;       //Same
    
    LATGbits.LATG12 = LEDOFF;       //turn LED on FIXME: turn it off 
    LATGbits.LATG14 = LEDOFF;       //Same
    
}

void turnOnLED(int LED) {
    
    if (LED == GRN) {
        LATGbits.LATG12 = LEDON;        //Turn on green LED
        LATGbits.LATG14 = LEDOFF;
    }
    else if (LED == RED) {
        LATGbits.LATG14 = LEDON;        //Turn on red LED
        LATGbits.LATG12 = LEDOFF; 
    }
}