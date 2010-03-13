/*
Copyright (c) 2010 Tymon Tobolski
 
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
 
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


/** 
 * USART Library.
**/


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
	
private:
	UsartBuffer buf; /**< Input buffer */
	char _n;
};

#endif
