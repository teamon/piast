all: main flash

main:
	avr-g++ -Wall -Os -DF_CPU=16000000 -mmcu=atmega128 -o out/main.o -c src/main.cpp
	avr-g++ -Wall -Os -DF_CPU=16000000 -mmcu=atmega128 -o out/buffer.o -c src/buffer.cpp
	avr-g++ -Wall -Os -DF_CPU=16000000 -mmcu=atmega128 -o out/lcd.o -c src/lcd.cpp

	avr-g++ -Wall -Os -DF_CPU=16000000 -mmcu=atmega128 -o out/main.elf out/main.o out/lcd.o out/buffer.o
	avr-objcopy -j .text -j .data -O ihex out/main.elf main.hex

flash:
	avrdude -c stk500v2 -P avrdoper -p atmega128 -U flash:w:main.hex:i

clean:
	rm -rf out/*

