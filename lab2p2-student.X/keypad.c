#include <xc.h>
#include "keypad.h"
#include "timer.h"

#define input 1
#define output 0
#define pin1 LATBbits.LATB4
#define pin2 PORTDbits.RD6
#define pin3 LATBbits.LATB2 
#define pin4 PORTDbits.RD12
#define pin5 LATBbits.LATB0
#define pin6 PORTFbits.RF1
#define pin7 PORTGbits.RG0  
#define press 0
#define release 1
#define scanning 1
#define notscan 0

/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    ODCBbits.ODCB0 = 1;
    ODCBbits.ODCB2 = 1;
    ODCBbits.ODCB4 = 1;
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB4 = 0;
    TRISDbits.TRISD6 = input;
    TRISDbits.TRISD12 = input;
    TRISFbits.TRISF1 = input;
    TRISGbits.TRISG0 = input;
    TRISBbits.TRISB0 = output;
    TRISBbits.TRISB2 = output;
    TRISBbits.TRISB4 = output;
    
    pin1 = notscan;
    pin3 = notscan;
    pin5 = notscan;
    pin2 = release;
    pin4 = release;
    pin6 = release;
    pin7 = release;
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
int scanKeypad(void){
    
    int key = -1;
    
    pin1 = scanning;
    pin3 = notscan;
    pin5 = notscan;
    if(pin2 == press) key = 1;
    if(pin4 == press) key = 10; //10 for *
    if(pin6 == press) key = 7;
    if(pin7 == press) key = 4;
    delayUs(500);

    if (key == -1){
    pin1 = notscan;
    pin3 = scanning;
    pin5 = notscan;
    if(pin2 == press) key = 2;
    if(pin4 == press) key = 0; 
    if(pin6 == press) key = 8;
    if(pin7 == press) key = 5;
    delayUs(500);
    }
    
    if (key == -1){
    pin1 = notscan;
    pin3 = notscan;
    pin5 = scanning;
    if(pin2 == press) key = 3;
    if(pin4 == press) key = 11; //11 for #
    if(pin6 == press) key = 9;
    if(pin7 == press) key = 6;
    }
    
    return key;
}

void enableEnterruptKeypad(){
    CNCONDbits.ON = 1;//ENABLE INTERRUPT
    CNENDbits.CNIED6 = 1;//enable interrupt of pin2
    CNENDbits.CNIED12 = 1;//enable interrupt of pin4
    IEC1bits.CNDIE = 1;//enable allover interrupt    
    IFS1bits.CNDIF = 0;//put flag down
    
    CNCONFbits.ON = 1;//ENABLE INTERRUPT
    CNENFbits.CNIEF1 = 1;//enable interrupt of pin6
    IEC1bits.CNFIE = 1;//enable allover interrupt
    IFS1bits.CNFIF = 0;//put flag down
    
    CNCONGbits.ON = 1;//ENABLE INTERRUPT
    CNENGbits.CNIEG0 = 1;//enable interrupt of pin7
    IEC1bits.CNGIE = 1;//enable allover interrupt
    IFS1bits.CNGIF = 0;//put flag down
    IPC8bits.CNIP = 7;
}

void disableKeyInterrupt(){
    
    CNCONDbits.ON = 0;//ENABLE INTERRUPT
    CNENDbits.CNIED6 = 0;//enable interrupt of pin2
    CNENDbits.CNIED12 = 0;//enable interrupt of pin4
    IEC1bits.CNDIE = 0;//enable allover interrupt    
    IFS1bits.CNDIF = 0;//put flag down
    
    CNCONFbits.ON = 0;//ENABLE INTERRUPT
    CNENFbits.CNIEF1 = 0;//enable interrupt of pin6
    IEC1bits.CNFIE = 0;//enable allover interrupt
    IFS1bits.CNFIF = 0;//put flag down
    
    CNCONGbits.ON = 0;//ENABLE INTERRUPT
    CNENGbits.CNIEG0 = 0;//disable interrupt of pin7
    IEC1bits.CNGIE = 0;//enable allover interrupt
    IFS1bits.CNGIF = 0;//put flag down
    IPC8bits.CNIP = 7;
    
}