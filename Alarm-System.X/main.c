/* 
 * File:   main.c
 * Author: 
 * Title: 
 * Created on 
 */

#include <stdio.h>
#include <xc.h>
#include <stdlib.h>
#include <p32xxxx.h>
/* include user header file here*/
#include "uart.h"
#include "lcd.h"
#include "ADC.h"
#include "config.h"
/* Pragma definition */
//for system clock and for pbclk
#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      
/* this set the SYSCLK (80 MHz) and the PBCLK (40 MHz)*/
// Device Config Bits in  DEVCFG1:	
#pragma config FNOSC =	FRCPLL
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	XT
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_2
// Device Config Bits in  DEVCFG2:	
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1
/*init global variables here*/
/*
 * 
 */
char flagRX; // global  - it has to be init in main.c
char strg[80]; // global - it has to be init in main.c
int j;
char pwd[] = {0,0,0,0};

int initializeRGBToRed();
unsigned int initializedRGB = 0;
void printInsertPassword();


void main()
{
/*init local variables here*/
TRISD = 0x0000;
TRISA &= 0xff00;
TRISBbits.TRISB14 = 0; //buzzer configured as output
ANSELBbits.ANSB14 = 0; //buzzer disabled analog
PORTBbits.RB14 = 0;
TRISFbits.TRISF4 = 1; //RF0 (BTNC) configured as input

tris_ADC_AN2 = 1;
ansel_ADC_AN2 = 1;

setupLCD();

    while(1) //forever loop
    {
        if(initializedRGB == 0)
            initializedRGB = initializeRGBToRed();
        
        if(PORTFbits.RF0)
            printInsertPassword();
    }
}

int initializeRGBToRed(){
    LATDbits.LATD12 = 0x0000;
    LATDbits.LATD3 = 0x0000;
    LATDbits.LATD2 = 1;
    
    return 1;
}

void attivato(){
    initializeRGBToRed();
    while(1) {
        ADC_Init();
        LATBbits.LATB14 ^= 1; //attiva suono
        //delay
        LATBbits.LATB14 ^= 0; //disattiva suono
        //aggiungi ai logs
    }
    //se btnc premuto -> btn init , se la pwd == input -> menu
}



