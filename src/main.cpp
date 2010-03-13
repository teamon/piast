#include "piast.h"
#include "usart.h"
#include "LCD_lib.h"

uint8_t  name[] = "PIAST";
uint8_t  website[] = "yayetee.com";

uint8_t right_arrow[] PROGMEM= 
{
0b00000000,
0b00001000,
0b00001100,
0b00001110,
0b00001111,
0b00001110,
0b00001100,
0b00001000
};


volatile int value[3];
volatile int axis=0;
char x[4];
char y[4];
char z[4];


SIGNAL (SIG_ADC)
{	
	value[axis]=(ADCL|(ADCH<<8))*10 / 102; //read 10-bit value from two 8 bit registers (right adjustment)
	if (++axis > 2) axis = 0;
	ADMUX = (0xC0 | axis);
	ADCSRA|=_BV(ADSC); //Write ADSC to one, in order to start next conversion
}


void ADCinit(void)
{
  ADCSRA=_BV(ADEN) | _BV(ADSC) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS0);; //ADCenable, Interrupt Enable, ADCstarConversion,  
  ADMUX=0x00; //Vref external, right adjustment, start from adc0
  DDRF=0x00;
  //do not forget to enable interrupts using sei()
}


int main() {
	LCDinit();
	LCDcursorOFF();
	ADCinit();
	sei();
	
	LCDdefinechar(right_arrow,0);


	
	LCDGotoXY(0,1);
	LCDsendChar(0);
	LCDstring(website,11);
	while(1)
	{
		int k=0;
		
		
		value[0]=(value[0]-50)*2;
		
		itoa(value[0], x, 10);
		LCDGotoXY(0,0);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDGotoXY(0,0);
		while(x[k]!='\0')
		{
			LCDsendChar(x[k]);
			k++;
		}
		LCDsendChar('%');
		
		value[1]=(value[1]-50)*2;
		itoa(value[1], y, 10);
		LCDGotoXY(5,0);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDGotoXY(5,0);
		k=0;
		
		while(y[k]!='\0')
		{
			LCDsendChar(y[k]);
			k++;
		}
		LCDsendChar('%');
		
		
		value[2]=(value[2]-50)*2;
		itoa(value[2], z, 10);
		LCDGotoXY(11,0);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDsendChar(128);
		LCDGotoXY(11,0);
		k=0;
		\
		while(z[k]!='\0')
		{
			LCDsendChar(z[k]);
			k++;
		}
		LCDsendChar('%');
		
	}
}
