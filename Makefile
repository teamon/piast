all: main
main:
	avr-g++ -Wall -Os -DF_CPU=8000000 -mmcu=atmega128 -o out/main.o -c src/main.cpp
	avr-g++ -Wall -Os -DF_CPU=8000000 -mmcu=atmega128 -o out/buffer.o -c src/buffer.cpp
	avr-g++ -Wall -Os -DF_CPU=8000000 -mmcu=atmega128 -o out/LCD_lib.o -c src/LCD_lib.c
	
	avr-g++ -Wall -Os -DF_CPU=8000000 -mmcu=atmega128 -o out/main.elf out/main.o out/buffer.o out/LCD_lib.o
#	avrdude -c stk500v2 -P avrdoper -p atmega128 -U flash:w:main.hex:i
clean:
	rm -rf out/buffer.o
	rm -rf out/main.o
	rm -rf out/main.elf
	rm -rf out/LCD_lib.o
clobber:
	rm -rf out/buffer.o
	rm -rf out/main.o
	rm -rf out/main.elf
	rm -rf out/LCD_lib.o
