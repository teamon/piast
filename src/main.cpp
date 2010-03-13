#include "piast.h"
#include "usart.h"
#include "lcd.h"

#define LCD_RS	0 	//define MCU pin connected to LCD RS
#define LCD_E	1	//define MCU pin connected to LCD E

#define LCD_D4	2	//define MCU pin connected to LCD D3
#define LCD_D5	3	//define MCU pin connected to LCD D4
#define LCD_D6	4	//define MCU pin connected to LCD D5
#define LCD_D7	5	//define MCU pin connected to LCD D6

#define LCD_DP PORTD	//define MCU port connected to LCD data pins
#define LCD_CP PORTD	//define MCU port connected to LCD control pins
#define LCD_DDR DDRD	//define MCU direction register for port connected to LCD data pins
#define LCD_CDR DDRD	//define MCU direction register for port connected to LCD control pins


USART0(usb);

int main() {
	for(;;){
		while(!usb.empty()){
			unsigned char c;
			usb >> c;
			usb << c;
		}
	}
}
