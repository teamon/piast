#include "piast.h"
#include "usart.h"
#include "lcd.h"
#include <avr/eeprom.h> 


char  website[] = "yayetee.com";

LCD lcd; //lcd init

uint8_t heart[] PROGMEM= 
{
0b00000000,
0b00001010,
0b00011111,
0b00011111,
0b00011111,
0b00001110,
0b00000100,
0b00000000
};


volatile int value[3];
volatile int axis=0;
char x[4];
char y[4];
char z[4];
unsigned char contrast;
unsigned char brightness;

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
	lcd.cursorOff();
	ADCinit();
	sei();
	
	lcd.define(heart,0);
	
	
	config_save(BRIGHTNESS, 15);
	config_save(CONTRAST, 10);
	
	brightness= config_read(BRIGHTNESS);
	contrast = config_read(CONTRAST);

	

	
	lcd.gotoxy(1,1);
	lcd << (char) 0;
	lcd << (int) contrast;
	lcd << (char) 0;
	lcd << (int) brightness;
	while(1)
	{
		
		lcd.gotoxy(0,0);
		lcd << "     ";
		lcd.gotoxy(0,0);
		lcd << (value[0]-50)*2 << '%';
		
		lcd.gotoxy(5,0);
		lcd << "     ";
		lcd.gotoxy(5,0);
		lcd << (value[1]-50)*2 << '%';
		
		lcd.gotoxy(11,0);
		lcd << "     ";
		lcd.gotoxy(11,0);
		lcd << (value[2]-50)*2 << '%';
		
	}
}
