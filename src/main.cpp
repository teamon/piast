#include "piast.h"
#include "buffer.h"

Buffer buf0, buf1;

ISR(USART0_RX_vect){
	char in;
	in = UDR0;
	
	buf0.push(in);
}

ISR(USART1_RX_vect){
	char in;
	in = UDR1;
	
	buf1.push(in);
}

void send_byte0(unsigned char byte) {
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = byte;
}

void send_byte1(unsigned char byte) {
	while (!(UCSR1A & (1<<UDRE1)));
	UDR1 = byte;
}

void init(){
	int ubrr = 51;

	// speed settings
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR1H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	UBRR1L = (unsigned char) ubrr;
	
	// RXC interrupt, receiver and transmiter
	UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
	UCSR1B = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
	
	UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (3 << UCSZ00);
	UCSR1C = (1 << USBS0) | (1 << UCSZ11) | (3 << UCSZ10);
}


int main() {
	init();
	
	sei();

	for(;;){
		while(!buf0.empty()){
			send_byte1(buf0.read());
		}
		
		while(!buf1.empty()){
			send_byte0(buf1.read());
		}
	}
}
