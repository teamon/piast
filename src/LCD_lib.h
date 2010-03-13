#ifndef LCD_lib
#define LCD_lib

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

