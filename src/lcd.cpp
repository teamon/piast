#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "lcd.h"


//Initializes LCD
void LCDinit(void)
{
	_delay_ms(15);
	LDP=0x00;
	LCP=0x00;
	LDDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCDR|=1<<LCD_E|1<<LCD_RS;
    //--------- Write 0x03 -----------
	LDP|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(5);
	//--------- Write 0x03 -----------
	LDP|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//--------- Write 0x03 ------------
	LDP|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//--------- Enable Four Bit Mode ----------
	LDP&=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //Write 0x2
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
   //---------- Set Interface Length ----------
	LDP|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //Write 0x2 - 4 bits
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP|=1<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x8 - 2 lines, 5x7
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
   //---------- Turn off the Display ----------
	LDP&=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x0 
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP|=1<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x8 
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
   //------------ Clear the Display -----------
	LDP&=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x0 
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP|=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|1<<LCD_D4; //Write 0x1
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
   //-------- Set Cursor Move Direction --------
	LDP&=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x0 
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP|=0<<LCD_D7|1<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //Write 0x6 - Increment the Cursor
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
   //---------- Enable Display/Cursor ----------
	LDP&=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x0 
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4; //Write 0xF - Display on, cursor on, blink on 
	LCP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
}			

//Sends Char to LCD
void LCDsendChar(uint8_t ch)		
{	 
	//4 MSB bits
	LDP=((ch>>2)&0b00111100);
	LCP|=1<<LCD_RS|1<<LCD_E;
	_delay_ms(1);
	LCP&=0<<LCD_E|0<<LCD_RS;	
	_delay_ms(1);
    //4 LSB bits
	LDP=((ch<<2)&0b00111100);
	LCP|=1<<LCD_RS|1<<LCD_E;
	_delay_ms(1);
	LCP&=0<<LCD_E|0<<LCD_RS;	
	_delay_ms(1);
}

//Sends Command to LCD
void LCDsendCommand(uint8_t cmd)	
{
	//4 MSB bits
	LDP=((cmd>>2)&0b00111100);
	LCP|=1<<LCD_E;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//4 LSB bits
	LDP=((cmd<<2)&0b00111100);
	LCP|=1<<LCD_E;		
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);			
}

//Clears LCD
void LCDclr(void)				
{
	LCDsendCommand(0x01);
}

//LCD cursor home
void LCDhome(void)			
{
	LCDsendCommand(0x02);
}

//Outputs string to LCD
void LCDstring(uint8_t* data, uint8_t nBytes)	
{
register uint8_t i;

	// check to make sure we have a good pointer
	if (!data) return;

	// print data
	for(i=0; i<nBytes; i++)
	{
		LCDsendChar(data[i]);
	}

}

//Cursor to X Y position
void LCDGotoXY(uint8_t x, uint8_t y)	
{
#define LCD_DDRAM               7	//set DD RAM address

#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
	case 0:  DDRAMAddr = LCD_LINE0_DDRAMADDR + x; break;
	case 1:  DDRAMAddr = LCD_LINE1_DDRAMADDR + x; break;
	case 2:  DDRAMAddr = LCD_LINE2_DDRAMADDR + x; break;
	case 3:  DDRAMAddr = LCD_LINE3_DDRAMADDR + x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR + x;
	}
	// set data address
	LCDsendCommand(1<<LCD_DDRAM | DDRAMAddr);	
} 

//Scrol n of characters Right
void LCDshiftLeft(uint8_t n)	
{
uint8_t i;

	for (i=0;i<n;i++)
	{
		LCDsendCommand(0x1E);
	}
}

//Scrol n of characters Left
void LCDshiftRight(uint8_t n)	
{
uint8_t i;

	for (i=0;i<n;i++)
	{
		LCDsendCommand(0x18);
	}
}

//displays LCD cursor
void LCDcursorOn(void) 
{
	LCDsendCommand(0x0E);
}

//displays LCD blinking cursor
void LCDcursorOnBlink(void)	
{
	LCDsendCommand(0x0F);
}

//Turns OFF cursor
void LCDcursorOFF(void)	
{
	LCDsendCommand(0x0C);
}

//Blanks LCD
void LCDblank(void)		
{
	LCDsendCommand(0x08);
}

//Shows LCD
void LCDvisible(void)		
{
	LCDsendCommand(0x0C);
}

//Moves cursor by n poisitions left
void LCDcursorLeft(uint8_t n)	
{
uint8_t i;

	for (i=0;i<n;i++)
	{
		LCDsendCommand(0x10);
	}
}

//Moves cursor by n poisitions left
void LCDcursorRight(uint8_t n)	
{
uint8_t i;

	for (i=0;i<n;i++)
	{
		LCDsendCommand(0x14);
	}
}

//Copies string from flash memory to LCD at x y position
void CopyStringtoLCD(const uint8_t *FlashLoc, uint8_t x, uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		LCDsendChar((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
}

//defines char symbol in CGRAM
void LCDdefinechar(const uint8_t *pc, uint8_t code)
{
	uint8_t a;
	uint16_t i;
	a=(code<<3)|0x40;
	for (i=0; i<8; i++){
		LCDsendCommand(a++);
		LCDsendChar((uint8_t)pgm_read_byte(&pc[i]));
		}
}

