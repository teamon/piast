#ifndef LCD_lib
#define LCD_lib

#define LCD_RS	0 	//define MCU pin connected to LCD RS
#define LCD_E	1	//define MCU pin connected to LCD E

#define LCD_D4	2	//define MCU pin connected to LCD D3
#define LCD_D5	3	//define MCU pin connected to LCD D4
#define LCD_D6	4	//define MCU pin connected to LCD D5
#define LCD_D7	5	//define MCU pin connected to LCD D6

#define LDP PORTA	//define MCU port connected to LCD data pins
#define LCP PORTA	//define MCU port connected to LCD control pins
#define LDDR DDRA	//define MCU direction register for port connected to LCD data pins
#define LCDR DDRA	//define MCU direction register for port connected to LCD control pins

#define A	65
#define B	66
#define C	67
#define D	68
#define E	69
#define F	70
#define G	71
#define H	72
#define I	73
#define J	74
#define K	75
#define L	76
#define M	77
#define N	78
#define O	79
#define P	80
#define Q	81
#define R	82
#define S	83
#define T	84
#define U	85
#define V	86
#define W	87
#define X	88
#define Y	89
#define Z	90

#define space 32


#include <inttypes.h>

void LCDsendChar(uint8_t);		                        //forms data ready to send to 74HC164
void LCDsendCommand(uint8_t);	                        //forms data ready to send to 74HC164
void LCDinit(void);			                            //Initializes LCD
void LCDclr(void);				                        //Clears LCD
void LCDhome(void);			                            //LCD cursor home
void LCDstring(uint8_t*, uint8_t);	                    //Outputs string to LCD
void LCDGotoXY(uint8_t, uint8_t);	                    //Cursor to X Y position
void CopyStringtoLCD(const uint8_t*, uint8_t, uint8_t); //copies flash string to LCD at x,y
void LCDdefinechar(const uint8_t *,uint8_t);            //write char to LCD CGRAM 
void LCDshiftRight(uint8_t);	                        //shift by n characters Right
void LCDshiftLeft(uint8_t);	                            //shift by n characters Left
void LCDcursorOn(void);		                            //Underline cursor ON
void LCDcursorOnBlink(void);	                        //Underline blinking cursor ON
void LCDcursorOFF(void);		                        //Cursor OFF
void LCDblank(void);		 	                        //LCD blank but not cleared
void LCDvisible(void);			                        //LCD visible
void LCDcursorLeft(uint8_t);	                        //Shift cursor left by n
void LCDcursorRight(uint8_t);	                        //shif cursor right by n

#endif

