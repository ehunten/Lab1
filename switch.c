/*
 * File:   switch.c
 * Author: Evelyn Hunten
 *
 * Created 2/11/16
 */
#include <xc.h>
#include "switch.h"

#define ENABLE 1
#define OFF 0
#define DEFAULT 7

void initSW2(){
    //Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISAbits.TRISA7 = ENABLE;      //Configure switch as input
    CNCONAbits.ON = ENABLE;         //Enable interrupt
    CNENAbits.CNIEA7 = ENABLE;      //Enable change notifications
    CNPUAbits.CNPUA7 = ENABLE;      //Enable pull-up resistor
    IFS1bits.CNAIF = OFF;           //Put down the flag
    IPC8bits.CNIP = DEFAULT;        //Configure interrupt priority
    IEC1bits.CNAIE = ENABLE;        //Enable interrupt for A pins
        
}
