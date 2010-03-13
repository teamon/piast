DEVICE      = atmega128
CLOCK       = 8000000
PROGRAMMER  = -c stk500v2 -P avrdoper
AVRDUDE     = avrdude $(PROGRAMMER) -p $(DEVICE)
CCAVR       = avr-g++ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

OBJECTS     = main.o usart.o LCD_lib.o
AVR_OBJECTS = $(patsubst %,out/%,$(OBJECTS))

all: main.hex

out/%.o : src/%.cpp
	$(CCAVR) -c $< -o $@

out/main.elf: $(AVR_OBJECTS)
	$(CCAVR) -o out/main.elf $(AVR_OBJECTS)
# 
main.hex: out/main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex out/main.elf main.hex

flash: main.hex
	$(AVRDUDE) -U flash:w:main.hex:i

size:
	avr-size out/main.elf

mkdirs:
	mkdir -p out

clean:
	rm -f main main.hex
	rm -rf out/*

