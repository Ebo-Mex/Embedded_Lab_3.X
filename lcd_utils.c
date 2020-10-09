#include "lcd_utils.h"

//Funciones LCD

void iniLCD(){
    __delay_ms(20);         //1. Esperar mas de 15ms
    LCDcommand(Set8);       //2. Comando set 8 bits
    __delay_ms(5);          //3. Esperar mas de 4.1ms
    LCDcommand(Set8);       //4. Comando set 8 bits
    __delay_ms(1);          //5. Esperar mas de 100us
    LCDcommand(Set8);       //6. Comando set 8 bits
    LCDcommand(Set8_2lin);  //N = 1 (2 lines), F=0 (5x8)
    LCDcommand(DispOn);   //D<2> ON; C<1> OFF; B<0> OFF;
    LCDcommand(ClearDisp);  //Disp Clear
    LCDcommand(IncShif);  //I/D = 1, S=0
    return;
}

void LCDcommand(char a){
    PORTEbits.RE0 = 0; //RE0 --> RS=0
    PORTD = a;
    PORTEbits.RE1 = 1; //RE1 --> E=1
    __delay_ms(1);
    PORTEbits.RE1 = 0; //RE1 --> E=0
    __delay_ms(1);
    return;
}

void LCDchar(char a){
    PORTD = a; //Valor ASCII
    PORTEbits.RE0 = 1;
    PORTEbits.RE1 = 1; //RE1 --> E=1
    __delay_us(40);
    PORTEbits.RE1 = 0; //RE1 --> E=0
}

void CG_char(char a, int line, int row){
    int cmd;
    if (line == 1)
    {
        line = 0x80;
        cmd = line + row;
    } else if (line==2)
    {
        line = 0xC0;
        cmd = line + row;    
    }   
    LCDcommand(cmd);    /*Display characters from c0(2nd row) location */
    LCDchar(a);
}

void MoveCursor(char x, char y){
    char a;
    if(y <= 1 && x <= 39){
        if(y ==0){
            a = x;
        }
        else{
            a = x + 64;
        }
        a = a | SetDDRAM;
    }
    PORTEbits.RE0 = 0; //RE0 --> RS=0
    PORTD = a;
    PORTEbits.RE1 = 1; //RE1 --> E=1
    __delay_ms(2);
    PORTEbits.RE1 = 0; //RE1 --> E=0
    return;
}

void MoveLCD(char dir, char inc){
    if(dir==0){
        for(int i = 0; i < inc; i++){
        LCDcommand(DispSfL);
        __delay_ms(200);
        }
    }
    else{
        for(int i = 0; i < inc; i++){
            LCDcommand(DispSfR);
            __delay_ms(200);
        }
    }
}

void GenChar(unsigned char loc,unsigned char *msg){
    unsigned char i;
    if(loc<8)
    {
        LCDcommand(SetCGRAM + (loc*8));  /* Command 0x40 and onwards forces the device to point CGRAM address */
        for(i=0;i<8;i++)  /* Write 8 byte for generation of 1 character */
            LCDchar(msg[i]);
    }   
}
