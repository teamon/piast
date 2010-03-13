#include "piast.h"
#include "usart.h"

#include "common.h"
#include "tlcd.h"

USART0(usb);
USART1(zigbit);

int main() {
	sei();
	
	tlcd_init();
	tlcd_cls();
	
	// tlcd_goto(1,1);
	// tlcd_write_string("Servo control");
	// tlcd_goto(1,2);

	for(;;){
		// if(!usb.empty()){
		// 	unsigned char c;
		// 	usb >> c;
		// 	usb << c;
		// }
		
		
	}
}
