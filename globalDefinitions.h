/* 
 * File:   globalDefinition.h
 * Author: maric
 *
 * Created on 17 de agosto de 2018, 04:18 PM
 */

#ifndef GLOBALDEFINITIONS_H
#define	GLOBALDEFINITIONS_H

#define LED_TRIS TRISAbits.RA0
#define LED LATAbits.LA0 //Cada vez que escribe LED se refiere a este pin del puerto A
#define _ON 1 //_ON ahora significa 1
#define _OFF 0 //_OFF ahora significa 0
#define INPUT 1;
#define OUTPUT 0;
#define _XTAL_FREQ 8000000
#define UP    PORTAbits.RA0
#define DOWN  PORTAbits.RA1
#define RIGHT PORTAbits.RA2
#define LEFT  PORTAbits.RA3

#endif	/* GLOBALDEFINITIONS_H */
