#ifndef _USART_H_
#define _USART_H_

#define USART_BAUD 9600

#define __usart__char2int(c) (c - 48)
#define __usart__int2char(c) (c + 48)

#if defined (__AVR_ATmega32__)
#	define USART(u) Usart u; ISR(USART_RXC_vect){ u.read(UDR); }
#elif defined (__AVR_ATmega128__)
#	define USART0(u) Usart u = Usart(0); ISR(USART0_RX_vect){ int c; c = UDR0; u.read(c); }
#	define USART1(u) Usart u = Usart(1); ISR(USART1_RX_vect){ int c; c = UDR1; u.read(c); }
#else
#	error "Device not supported"
#endif

struct UsartBufferItem {
	char character;
	UsartBufferItem* next;
};

class UsartBuffer {
public:
	UsartBuffer();
	void push(char c);
	void pop();
	void clear();
	bool empty();
	char * front();
	int size();
	unsigned char read();
	
private:
	int _counter;
	UsartBufferItem *_head, *_tail;
};


class Usart {
public:
	Usart(char n);
	void read(char c);
	unsigned char get();
	bool empty();
	void sendByte(unsigned char byte);	
	void sendNumber(long number);
	
	Usart & operator<<(const unsigned char c);
	Usart & operator<<(const char c);
	Usart & operator<<(char* string);
	Usart & operator<<(const int number);
	Usart & operator<<(const long number);
	
	Usart & operator>>(unsigned char &c);
	Usart & operator>>(int &c);
	
// private:
	UsartBuffer buf;
	UsartBuffer buf_out;
	char _n;
};

#endif
