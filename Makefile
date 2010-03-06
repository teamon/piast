all: main
main:
	avr-g++ -Wall -Os -DF_CPU=8000000 -mmcu=atmega128 -o out/main.o -c src/main.cpp
	avr-g++ -Wall -Os -DF_CPU=8000000 -mmcu=atmega128 -o out/buffer.o -c src/buffer.cpp
	avr-g++ -Wall -Os -DF_CPU=8000000 -mmcu=atmega128 -o out/main.elf out/main.o out/buffer.o
	avrdude -c stk500v2 -P avrdoper -p atmega128 -U flash:w:main.hex:i
clean:
	rm -rf out/buffer.o
	rm -rf out/main.o
	rm -rf out/main.elf
clobber:
	rm -rf out/buffer.o
	rm -rf out/main.o
	rm -rf out/main.elf
