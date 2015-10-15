// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "config.h"
#include "interrupt.h"

#define pin1 LATBbits.LATB4
#define pin2 PORTDbits.RD6
#define pin3 LATBbits.LATB2
#define pin4 PORTDbits.RD12
#define pin5 LATBbits.LATB0
#define pin6 PORTFbits.RF1
#define pin7 PORTGbits.RG0

typedef enum stateTypeEnum {
    Wait, Scan, Print
} stateType;
volatile stateType state;
volatile int key = -1;

int main(void) {
    initKeypad();
    initTimer2();
    initLCD();
    enableInterrupts();
    state = Wait;

    while (1) {
        switch (state) {
            case Wait:
                delayUs(5);
                break;

            case Scan:
                delayUs(5);
                key = scanKeypad();
                state = Print;
                break;

            case Print:
                delayUs(5);
                if(key == 0) printCharLCD('0');
                else if(key == 1) printCharLCD('1');
                else if(key == 2) printCharLCD('2');
                else if(key == 3) printCharLCD('3');
                else if(key == 4) printCharLCD('4');
                else if(key == 5) printCharLCD('5');
                else if(key == 6) printCharLCD('6');
                else if(key == 7) printCharLCD('7');
                else if(key == 8) printCharLCD('8');
                else if(key == 9) printCharLCD('9');
                else if(key == 10) printCharLCD('*');
                else if(key == 11) printCharLCD('#');
                state = Wait;
                break;

        }
    }

    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    int dummy1 = pin2;
    int dummy2 = pin4;
    int dummy3 = pin6;
    int dummy4 = pin7;
    IFS1bits.CNBIF = 0;
    IFS1bits.CNGIF = 0;
    IFS1bits.CNDIF = 0;
    IFS1bits.CNGIF = 0;
    if(state == Wait){
        state = Scan;
    }
}