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
Port and Pin configuration 
***********************************************************************/
// LCD pins
#define DB7       5    //Bite 1 ...    
#define DB6       4
#define DB5       3
#define DB4       2
#define ENABLE    1
#define RS        0
// Switch pins (Optional if needed in application)
#define SW1		  0x40  
#define SW2		  0x80
// Port
#define LCDDDR    DDRA
#define LCDPORT   PORTA     //Port of LCD
#define LCDPIN    PINB      //Port od SW1 and 2
// General defines
#define DATA      0x01
#define CTRL      0x00


/***********************************************************************
Prototypes
------------------------------------------------------------------------
Set up selected port and initialize the LCD controller in 4-bit modus.  
***********************************************************************/
void tlcd_init(void);

/***********************************************************************
Clears all text.
***********************************************************************/
void tlcd_cls(void);

/***********************************************************************
Goto specified column and line. 1,1 is the upper left corner.
***********************************************************************/
void tlcd_goto(uint8_t column, uint8_t line);

/***********************************************************************
Write strings to the display. Set position with tlcd_goto first.
Text will wrap if to long to show on one line.
***********************************************************************/
void tlcd_write_string(char *ptr);

/***********************************************************************
Write const strings to the display. Set position with tlcd_goto first.
Text will wrap if to long to show on one line.
***********************************************************************/
void tlcd_write_const_string(const char *ptr);

/***********************************************************************
Most for internal use only
***********************************************************************/
void tlcd_write_byte(BYTE control, BYTE data);




/***********************************************************************
End of code listing
***********************************************************************/
