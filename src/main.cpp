#include "piast.h"
#include "usart.h"

USART0(usb);
USART1(zigbit);

int main() {
	sei();

	for(;;){
		if(!usb.empty()){
			unsigned char c;
			usb >> c;
			usb << c;
		}
	}
}
