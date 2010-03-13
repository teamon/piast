#include <avr/io.h>
#include <stdlib.h>
#include "usart.h"

UsartBuffer::UsartBuffer(){
	_head = _tail = NULL;
	_counter = 0;
}

void UsartBuffer::clear(){
	while(_head != NULL) pop();
}

bool UsartBuffer::empty(){
	return (_head == NULL);
}

void UsartBuffer::push(char c){
	UsartBufferItem *curr = (UsartBufferItem*) malloc(sizeof(UsartBufferItem));
	if(_head == NULL) _head = curr;
	else _tail->next = curr;
	curr->character = c;
	curr->next = NULL;
	_tail = curr;
	_counter++;
}

void UsartBuffer::pop(){
	if(_head){
		UsartBufferItem *tmp = _head->next;
		free(_head);
		_head = tmp;
		_counter--;
	}
}

char * UsartBuffer::front(){
	return (_head ? &(_head->character) : NULL);
}

int UsartBuffer::size(){
	return _counter;
}

unsigned char UsartBuffer::read(){
	unsigned char n = *front();
	pop();
	return n;
}

Usart::Usart(char n){
	_n = n;
	int ubrr = (int)(F_CPU/USART_BAUD/16) - 1;
	ubrr = 51;

	// init: speed settings + interrupts
#if defined (__AVR_ATmega32__)

	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;
	UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << USBS) | (1 << UCSZ1) | (3 << UCSZ0);

#elif defined (__AVR_ATmega128__)

	if(_n==0){
		UBRR0H = (unsigned char) (ubrr >> 8);
		UBRR0L = (unsigned char) ubrr;
		UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
		UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (3 << UCSZ00);
	} else if(_n==1){
		UBRR1H = (unsigned char) (ubrr >> 8);
		UBRR1L = (unsigned char) ubrr;
		UCSR1B = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
		UCSR1C = (1 << USBS0) | (1 << UCSZ11) | (3 << UCSZ10);
	}

#endif
}

void Usart::read(char c){
	buf.push(c);
}

unsigned char Usart::get(){
	return buf.read();
}

bool Usart::empty(){
	return buf.empty();
}

void Usart::sendByte(unsigned char byte){
#if defined (__AVR_ATmega32__)

	while (!(UCSRA & (1<<UDRE)));
	UDR = byte;

#elif defined (__AVR_ATmega128__)

	if(_n==0){
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = byte;
	} else if(_n==1){
		while (!(UCSR1A & (1<<UDRE1)));
		UDR1 = byte;
	}

#endif
}

void Usart::sendNumber(long number){
	// negative numbers
	if(number < 0) {
		sendByte('-');
		number = -number;
	}
	
	long a = 1000000000;
	long b = 999999999;
	char k;
	
	for(int i=0; i<10; i++){
		k = (number / a) % 10;
		if(number > b || i == 9) sendByte(__usart__int2char(k));
		a /= 10;
		b /= 10;
	}
}

Usart & Usart::operator<<(const unsigned char byte){
	sendByte(byte);
	return *this;
}

Usart & Usart::operator<<(const char byte){
	sendByte(byte);
	return *this;
}

Usart & Usart::operator<<(char* string){
	while (*string != '\0') sendByte(*(string++));
	return *this;
}

Usart & Usart::operator<<(const long number){
	sendNumber(number);
	return *this;
}

Usart & Usart::operator<<(const int number){
	sendNumber(number);
	return *this;
}

Usart & Usart::operator>>(unsigned char &c){
	c = get();
	return *this;
}

Usart & Usart::operator>>(int &c){
	unsigned char first = get();
	int n = 0;
	int sign = 1;

	if(first == '-') sign = -1;
	else if(first >= '0' && first <= '9') n = __usart__char2int(first);

	for(;;){
		while(buf.empty());
		unsigned char c = buf.read();
		if(c == '\n') break;
		n *= 10;
		n += __usart__char2int(c);
	}

	c = n*sign;
	return *this;
}



