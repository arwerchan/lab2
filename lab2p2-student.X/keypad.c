#include <xc.h>
#include "keypad.h"
#include "timer.h"

#define input 1
#define output 0
#define pin1 PORTBbits.RB4
#define pin2 LATDbits.LATD6
#define pin3 PORTBbits.RB2
#define pin4 LATDbits.LATD12
#define pin5 PORTBbits.RB0
#define pin6 LATFbits.LATF1
#define pin7 LATbits.LATG0
#define press 0
#define release 1
#define scanning 1
#define notscan 0

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    ANSELBbits.ANSB11 = 0;//set to digital
    ANSELBbits.ANSB13 = 0;//set pin3 to digital
    ANSELBbits.ANSB14 = 0;
    TRISDbits.TRISD6 = input;
    TRISDbits.TRISD12 = input;
    TRISFbits.TRISF1 = input;
    TRISGbits.TRISG0 = input;
    pin1 = release;
    pin3 = release;
    pin5 = release;
    pin2 = notscan;
    pin4 = notscan;
    pin6 = notscan;
    pin7 = notscan;
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    char key = -1;
    
    pin2 = scanning;
    pin4 = notscan;
    pin6 = notscan;
    pin7 = notscan;
    if(pin1 == press) key = 2;
    if(pin3 == press) key = 1;
    if(pin5 == press) key = 3;
    
    pin2 = notscan;
    pin4 = scanning;
    pin6 = notscan;
    pin7 = notscan;
    if(pin1 == press) key = 0;
    if(pin3 == press) key = 10;//10 is "*"
    if(pin5 == press) key = 11;//11 is "#"
    
    pin2 = notscan;
    pin4 = notscan;
    pin6 = scanning;
    pin7 = notscan;
    if(pin1 == press) key = 8;
    if(pin3 == press) key = 7;
    if(pin5 == press) key = 9;
    
    pin2 = notscan;
    pin4 = notscan;
    pin6 = notscan;
    pin7 = scanning;
    if(pin1 == press) key = 5;
    if(pin3 == press) key = 4;
    if(pin5 == press) key = 6;
    
    return key;
}