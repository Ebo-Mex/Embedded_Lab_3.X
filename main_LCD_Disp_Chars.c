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

char pos = 0, icon = 0, line = 1;

void main(void) {
    OSCCON=0x72;
    
    //Turn OFF ADC
    ADCON1bits.PCFG0 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;
    
    TRISA =  INPUT;
    TRISD =  OUTPUT;
    TRISE =  OUTPUT;
    
    iniLCD();
    GenChar(0,lock); //Save character in CGRAM
    GenChar(1,lock1); //Save character in CGRAM
    __delay_ms(100);
    CG_char(1,line,pos);
    __delay_ms(100);
    
    while(1){
        if(UP == 1 & line == 2){
            line--;
        }
        if(DOWN == 1 & line == 1){
            line++;
        }
        if(RIGHT == 1 & pos < 15){
            pos++;
        }
        if(LEFT == 1 & pos > 0){
            pos--;
        }
        switch (icon){
            case 0 :
                icon = 1;
                break;
            case 1 : 
                icon = 0;
                break;
            default:
                break;
        }
        
        LCDcommand(ClearDisp);
        CG_char(icon,line,pos);
        __delay_ms(200);
    }
}
