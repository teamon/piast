#include "piast.h"
#include "buffer.h"

#include "lcd.h"


uint8_t  name[] = "PIAST";
uint8_t  website[] = "www.yayetee.com";

uint8_t backslash[] PROGMEM= 
{
0b00000000,
0b00010101,
0b00001110,
0b00010101,
0b00001110,
0b00010101,
0b00000000,
0b00000000
};

void delay_200ms(void)
{
	_delay_ms(200);
}


int main() {
	init();
	
	uint8_t x;
	uint8_t y;
	uint8_t j;

	LCDinit();
	LCDcursorOFF();
	LCDdefinechar(backslash,0);

	LCDGotoXY(0,1);
	// LCDsendChar(0x00);
	LCDstring(website,15);
	// LCDsendChar(0x00);
	
	while(1)
	{

		for(x=0;x<11;x++){
			LCDGotoXY(0,0);
			for(j=0;j<x;j++){
				LCDsendChar(space);
			}
			LCDGotoXY(x,0);
			LCDstring(name,5);
			LCDsendChar(space);
			delay_200ms();
		}

		for(y=9;y>0;y--){
			LCDGotoXY(y,0);
			LCDstring(name,5);
			for(j=y+6;j<16;j++){
				LCDsendChar(space);
			}
			delay_200ms();
		}	
	}

}
