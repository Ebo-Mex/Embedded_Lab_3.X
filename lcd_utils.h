/* 
 * File:   lcd_utils.h
 * Author: ebo-9
 *
 * Created on 4 de octubre de 2020, 09:19 PM
 */

#ifndef LCD_UTILS_H
#define LCD_UTILS_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "lcd_cmds.h"

#define _XTAL_FREQ 8000000

void iniLCD(void);
void LCDcommand(char a);
void LCDchar(char a);
void CG_char(char a, char line, char row);
void MoveCursor(char x, char y);
void MoveLCD(char dir, char inc);
void GenChar(unsigned char loc,unsigned char *msg);

#endif /* LCD_UTILS_H */