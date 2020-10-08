/*
 * File:   main_LCD_Disp_Chars.c
 * Author: ebo-9 & mari
 * 
 * Created on 4 de octubre de 2020, 09:10 PM
 */

#include <stdio.h>
#include <pic18f4550.h>
#include <xc.h>
#include "globalDefinitions.h"
#include "config_files.h"
#include "lcd_cmds.h"
#include "lcd_utils.h"

#define _XTAL_FREQ 8000000

unsigned char lock[8] = {
    0b01110, 
    0b10001, 
    0b10001, 
    0b11111, 
    0b11011, 
    0b11011, 
    0b11111, 
    0b00000};
unsigned char lock1[8] = {
    0b01110, 
    0b10000, 
    0b10000, 
    0b11111, 
    0b11011, 
    0b11011, 
    0b11111, 
    0b00000};
char pos = 0;
char line = 1;

void main(void) {
    OSCCON=0x72; 
    IPEN = _OFF;
    GIE = _OFF;
    
    //Turn OFF ADC
    ADCON1bits.PCFG0 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;
    
    TRISA =  INPUT;
    TRISB =  OUTPUT;
    TRISC =  OUTPUT;
    TRISD =  OUTPUT;
    TRISE =  OUTPUT;
    
    __delay_ms(100);
    iniLCD();
    LCDcommand(DispOn);
    GenChar(0,lock);
    GenChar(1,lock1);
    __delay_ms(100);
    CG_char(1,line,pos);  
    while(1){
        if(UP == 1)
        {
            if (line == 2)
            {
                line--;
                LCDcommand(ClearDisp);
                CG_char(1,line,pos);  
            }
        } else if(DOWN == 1)
        {
            if (line == 1)
            {
                line++;
                LCDcommand(ClearDisp);
                CG_char(1,line,pos);  
            }    
        } else if(RIGHT == 1)
        {
            if (pos < 15)
            {
                pos++;
                LCDcommand(ClearDisp);
                CG_char(1,line,pos);
                __delay_ms(250);
            }
        } else if(LEFT == 1)
        {
            if (pos > 0)
            {
                pos--;
                LCDcommand(ClearDisp);
                CG_char(1,line,pos);
                __delay_ms(200);
            }
        }
    }
}
