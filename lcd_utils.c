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
    LCDcommand(DispOn);     //D<2> ON; C<1> OFF; B<0> OFF;
    LCDcommand(ClearDisp);  //Disp Clear
    LCDcommand(IncNoShif);  //I/D = 1, S=0
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

void CG_char(char a, char line, char row){
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
    int cmd;
    if (y == 1)
    {
        y = 0x80;
        cmd = y + x;
    } else if (y==2)
    {
        y = 0xC0;
        cmd = y + x;    
    }   
    LCDcommand(cmd);
   
    return;
}

void MoveLCD(char dir, char inc){
    LCDcommand(IncShif);
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
    LCDcommand(IncNoShif);
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

int rand_key(char k_pos){
    int ene_line = rand() % 2 + 1;
    CG_char(5,ene_line,k_pos);
    return ene_line;
}

void LCDString(char *msg){
	while((*msg)!=0){		
	  LCDchar(*msg);
	  msg++;
    }
}
