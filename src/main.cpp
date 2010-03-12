#include "piast.h"
#include "usart.h"

USART0(usb);
USART1(zigbit);


int main() {
	sei();

	for(;;){
		while(!usb.empty()){
			usb << usb.get();
		}
	}
}
