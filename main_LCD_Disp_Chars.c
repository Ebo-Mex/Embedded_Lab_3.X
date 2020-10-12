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

void lock_sprite_switch(void);
void game_over_seq(void);
void level_up(void);
void move_lock(void);
void out_of_screen(void);
void move_stage(void);

unsigned char lock_F[8] = {
    0b01110, 
    0b10001, 
    0b10001, 
    0b11111, 
    0b11011, 
    0b11011, 
    0b11111, 
    0b00000};
unsigned char lock_R[8] = {
    0b01110,
    0b01010,
    0b01010,
    0b01110,
    0b01100,
    0b01100,
    0b01110,
    0b00000};
unsigned char lock_B[8] = {
    0b01110,
    0b10001,
    0b10001,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000};
unsigned char lock_L[8] = {
    0b01110,
    0b01010,
    0b01010,
    0b01110,
    0b00110,
    0b00110,
    0b01110,
    0b00000};
unsigned char key[8] = {
    0b00110,
    0b00100,
    0b00110,
    0b00100,
    0b01110,
    0b01010,
    0b01110,
    0b00000};
unsigned char lock_end[8] = {
    0b01110, 
    0b10000, 
    0b10000, 
    0b11111, 
    0b11011, 
    0b11011, 
    0b11111, 
    0b00000};
unsigned char lock_broken[8] = {
  0b01110,
  0b00001,
  0b10001,
  0b11101,
  0b11011,
  0b11010,
  0b01111,
  0b00000};
unsigned char smiley[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b10001,
    0b01110,
    0b00000,
    0b00000};

char pos = 1, icon = 0, line = 1, shift = 0;
char key_ = 14, key_pointer = 0, level = 4;
char key_pos[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
char key_line[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

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
    
    GenChar(0,lock_F);
    GenChar(1,lock_R);
    GenChar(2,lock_B);
    GenChar(3,lock_L);
    GenChar(4,lock_end);
    GenChar(5,key);
    GenChar(6,lock_broken);
    GenChar(7,smiley);
    __delay_ms(100);
    
    while(1){
        move_lock();
        lock_sprite_switch();

        CG_char(icon,line,pos); //Show icon in new position
        __delay_ms(200);
        shift++;

        for(int i = 0; i < 8; i++){
            if(key_pos[i] == pos & key_line[i] == line){
                game_over_seq();
                return;
            }
        }
        
        if(key_ > (pos+14)){
            out_of_screen();
            return;
        }
        
        if((shift % level) == 0){
            move_stage();
        }

        if (pos == 39){
            level_up();
        }
    }
}

void move_lock(void){
    if(UP == 1 & line == 2){
        MoveCursor(pos, 2);
        LCDchar(' ');
        line--;
    }
    if(DOWN == 1 & line == 1){
        MoveCursor(pos, 1);
        LCDchar(' ');                  
        line++;
    }
    if(RIGHT == 1 & pos < (key_ - 1)){
        MoveCursor(pos, line);
        LCDchar(' ');  
        pos++;
    }
    if(LEFT == 1 & pos > 1){
        MoveCursor(pos, line);
        LCDchar(' ');  
        pos--;
    }
}

void move_stage(void){
    MoveLCD(0,1);
    key_++;
    if((key_ % 2) == 0){
        if(key_pointer == 8){
            key_pointer = 0;
        }
        key_line[key_pointer] = rand_key(key_);
        key_pos[key_pointer] = key_;
        key_pointer++;
    }
}

void lock_sprite_switch(void){
    switch (icon){
        case 0 :
            icon = 1;
            break;
        case 1 : 
            icon = 2;
            break;
        case 2 : 
            icon = 3;
            break;
        case 3 : 
            icon = 0;
            break;
        default:
            break;
    }
}

void level_up(void){
    LCDcommand(ClearDisp);
    __delay_ms(100);
    MoveCursor(4, 1);
    LCDString("Level Up");
    CG_char(7,2,8);
    __delay_ms(2500);
    pos = pos - key_ + 14;
    key_pointer = 0;
    int key_pos[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    int key_line[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    shift = 0;
    key_ = 14;
    level--; //Level up
    if (level==1){
        level = 2; //Limit game at level 2
    }
    LCDcommand(ClearDisp);
}

void game_over_seq(void){
    LCDcommand(ClearDisp);
    __delay_ms(100);
    MoveCursor(4, 1);
    LCDString("GAME OVER");
    __delay_ms(500);
    CG_char(0,2,6);
    __delay_ms(500);
    CG_char(1,2,7);
    __delay_ms(500);
    CG_char(2,2,8);
    __delay_ms(500);
    CG_char(3,2,9);
    __delay_ms(500);
    CG_char(4,2,10);
    __delay_ms(2000);
}

void out_of_screen(void){
    LCDcommand(ClearDisp);
    __delay_ms(100);
    MoveCursor(4, 1);
    LCDString("GAME OVER");
    __delay_ms(500);
    CG_char(6,2,8);
    __delay_ms(3000);
}
