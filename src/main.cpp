#include "piast.h"
#include "buffer.h"

#define BAUD 9600

// Buffer buf0, buf1;

Buffer buf;

ISR(USART_RXC_vect){
	char in;
	in = UDR;
	
	buf.push(in);
}

// ISR(USART0_RX_vect){
// 	char in;
// 	in = UDR0;
// 	
// 	buf0.push(in);
// }

// ISR(USART1_RX_vect){
// 	char in;
// 	in = UDR1;
// 	
// 	buf1.push(in);
// }

void send_byte(unsigned char byte) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = byte;
}

// void send_byte0(unsigned char byte) {
// 	while (!(UCSR0A & (1<<UDRE0)));
// 	UDR0 = byte;
// }

// void send_byte1(unsigned char byte) {
// 	while (!(UCSR1A & (1<<UDRE1)));
// 	UDR1 = byte;
// }

void init(){
	// int ubrr = (F_CPU/(BAUD * 16)) - 1;
	int ubrr = 51;
	
	// speed settings (atmega32)
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;

	// speed settings (atmega128)
	// UBRR0H = (unsigned char) (ubrr >> 8);
	// UBRR1H = (unsigned char) (ubrr >> 8);
	// UBRR0L = (unsigned char) ubrr;
	// UBRR1L = (unsigned char) ubrr;
	
	// RXC interrupt, receiver and transmiter (atmega32)
	UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << USBS) | (1 << UCSZ1) | (3 << UCSZ0);
	
	// RXC interrupt, receiver and transmiter (atmega128)
	// UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
	// UCSR1B = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
	
	// UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (3 << UCSZ00);
	// UCSR1C = (1 << USBS0) | (1 << UCSZ11) | (3 << UCSZ10);
}


int main() {
	init();
	
	sei();

	for(;;){
		while(!buf.empty()){
			send_byte(buf.read());
		}
		
		// while(!buf0.empty()){
		// 	send_byte1(buf0.read());
		// }
		// 
		// while(!buf1.empty()){
		// 	send_byte0(buf1.read());
		// }
	}
}
