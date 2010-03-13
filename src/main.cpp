#include "piast.h"
#include "usart.h"

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
