/***********************************************************************
Content: Library for Hitachi 44780 based 1 or 2 line Text LCD displays.
Created: 28.05.2003
Last modified: 17.02.2004
Copyrights: Free to use, free to change, free to delete :-)
Compiler: ImageCraft AVR
Written by: Knut Baardsen @ Baardsen Software, Norway
Updates: http://www.baso.no
------------------------------------------------------------------------
This software is provided "as is"; Without warranties either express or
implied, including any warranty regarding merchantability, fitness for 
a particular purpose or noninfringement. 
In no event shall Baardsen Software or its suppliers be liable for any 
special,indirect,incidential or concequential damages resulting from 
the use or inability to use this software.
***********************************************************************/



/***********************************************************************
Includes
***********************************************************************/
#include "common.h"
#include "tlcd.h"
#include "util/delay.h"

/***********************************************************************
Clears all text.
***********************************************************************/

void tlcd_cls(void)
{
  tlcd_write_byte(CTRL,0x01);
  _delay_ms(20); 
}


/***********************************************************************
Goto specified column and line. 1,1 is the upper left corner.
***********************************************************************/
void tlcd_goto(uint8_t column, uint8_t line)
{
  uint8_t addr;
  column--;
  if (line == 2) addr = 0xC0 + column;
  if (line != 2) addr = 0x80 + column;
  tlcd_write_byte(CTRL, addr);
}


/***********************************************************************
Write strings to the display. Set position with tlcd_goto first.
Text will wrap if to long to show on one line.
***********************************************************************/
void tlcd_write_string(char *ptr)
{
  while (*ptr) tlcd_write_byte(DATA,*ptr++);
}


/***********************************************************************
Write const strings to the display. Set position with tlcd_goto first.
Text will wrap if to long to show on one line.
***********************************************************************/
void tlcd_write_const_string(const char *ptr)
{
  while (*ptr != 0x00) tlcd_write_byte(DATA,*ptr++);
}


/***********************************************************************
Write a control or data byte to the display. Control: 1=Ctrl, 0=Data
If data (control=0) set position with lcd_goto first.
Since the LCD is driven in 4-bit modus, we write the MSB nibble first
and the the LSB nibble.
***********************************************************************/
void tlcd_write_byte(uint8_t control, uint8_t data)
{
  if (control == 1) LCDPORT |= RS;  else LCDPORT &= ~RS;
  if ((data & 0x80) == 0x80) LCDPORT |= DB7; else LCDPORT &= ~DB7;
  if ((data & 0x40) == 0x40) LCDPORT |= DB6; else LCDPORT &= ~DB6;
  if ((data & 0x20) == 0x20) LCDPORT |= DB5; else LCDPORT &= ~DB5;
  if ((data & 0x10) == 0x10) LCDPORT |= DB4; else LCDPORT &= ~DB4;
  LCDPORT |= ENABLE;
  LCDPORT &= ~ENABLE;
  // if (control == 1) LCDPORT |= RS; else LCDPORT &= ~RS;
  if ((data & 0x08) == 0x08) LCDPORT |= DB7; else LCDPORT &= ~DB7;	
  if ((data & 0x04) == 0x04) LCDPORT |= DB6; else LCDPORT &= ~DB6;
  if ((data & 0x02) == 0x02) LCDPORT |= DB5; else LCDPORT &= ~DB5;
  if ((data & 0x01) == 0x01) LCDPORT |= DB4; else LCDPORT &= ~DB4;
  LCDPORT |= ENABLE;
  LCDPORT &= ~ENABLE;
  _delay_ms(5); //waitms(2);
}


/***********************************************************************
Set up selected port and initialize the LCD controller in 4-bit modus.  
***********************************************************************/
void tlcd_init(void)
{
  LCDPORT = 0x00;
  LCDDDR = 0b00111111; 
  _delay_ms(350);
  LCDPORT = (DB6 + DB7); 
  LCDPORT |= ENABLE;
  LCDPORT &= ~ENABLE;
  _delay_ms(20);
  LCDPORT |= ENABLE;
  LCDPORT &= ~ENABLE;
  _delay_ms(20);
  LCDPORT |= ENABLE;
  LCDPORT &= ~ENABLE;
  _delay_ms(20);
  LCDPORT = DB6;                 
  LCDPORT |= ENABLE;
  LCDPORT &= ~ENABLE;
  _delay_ms(20);
  tlcd_write_byte(CTRL,0x28);
  tlcd_write_byte(CTRL,0x0c);
  tlcd_write_byte(CTRL,0x01);
  _delay_ms(20);
  tlcd_write_byte(CTRL,0x06);
  _delay_ms(20);
}


/***********************************************************************
End of code listing
***********************************************************************/
