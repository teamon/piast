#include "piast.h"
#include "usart.h"

USART32(usb);

int main() {
	while(1){
		if(!usb.empty()){
			unsigned char c;
			usb >> c;
			usb << c;
		}
	}
}
