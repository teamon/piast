#ifndef _USART_H_
#define _USART_H_

#define USART_BAUD 9600

#define __usart__char2int(c) (c - 48)
#define __usart__int2char(c) (c + 48)


#if defined (__AVR_ATmega32__)
#	define USART(u) Usart u; ISR(USART_RXC_vect){ u.read(UDR); }
#elif defined (__AVR_ATmega128__)
#	define USART0(u) Usart u = Usart(0); ISR(USART0_RX_vect){ u.read(UDR0); }
#	define USART1(u) Usart u = Usart(1); ISR(USART1_RX_vect){ u.read(UDR1); }
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
	
	Usart & operator<<(unsigned char c);
	Usart & operator<<(char* string);
	Usart & operator<<(int number);
	Usart & operator<<(long number);
	
private:
	UsartBuffer buf;
	char _n;
};

#endif
