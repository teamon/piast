#include "piast.h"
#include "usart.h"
#include "lcd.h"
#include <avr/eeprom.h> 

// data structures

struct Joystick {
    volatile int x, y, z;
};

struct MenuItem {
    const char* desc;
    void (*func)();
};

// menu functions
void menu_contrast();
void menu_brightness();

// global variables

LCD lcd;
Joystick joy;

int contrast = config_read(CONTRAST);
int brightness = config_read(BRIGHTNESS);

unsigned int menu_pos = 0;
MenuItem menu[] = {
    {"   CONTRAST   ", menu_contrast},
    {"  BRIGHTNESS  ", menu_brightness}
};

volatile int axis = 0;

void show_menu_pos() {
    lcd.gotoxy(0, 1);
    if (menu_pos > 0) lcd << (char) 1;
    else lcd << " ";

    lcd << menu[menu_pos].desc;

    if (menu_pos < sizeof (menu) / sizeof (menu[0]) - 1) lcd << (char) 2;
    else lcd << " ";
}



char website[] = "yayetee.com";

uint8_t heart[] PROGMEM = {
    0b00000000,
    0b00001010,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00001110,
    0b00000100,
    0b00000000
};

uint8_t right_arrow[] PROGMEM = {
    0b00000000,
    0b00001000,
    0b00001100,
    0b00001110,
    0b00001111,
    0b00001110,
    0b00001100,
    0b00001000
};

uint8_t left_arrow[] PROGMEM = {
    0b00000000,
    0b00000010,
    0b00000110,
    0b00001110,
    0b00011110,
    0b00001110,
    0b00000110,
    0b00000010
};

SIGNAL(SIG_ADC) {
    int val = (ADCL | (ADCH << 8))*10 / 102; //read 10-bit value from two 8 bit registers (right adjustment)
    val = (val - 50)*2;

    switch (axis) {
        case 0:
            joy.y = val;
            break;
        case 1:
            joy.x = val;
            break;
        case 2:
            joy.z = val;
            break;
    }

    if (++axis > 2) axis = 0;
    ADMUX = (0xC0 | axis);
    ADCSRA |= _BV(ADSC); //Write ADSC to one, in order to start next conversion
}

ISR(TIMER1_OVF_vect) {
    OCR1B = contrast;
    OCR1A = brightness;
}

void ADCinit(void) {
    ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS0);
    ; //ADCenable, Interrupt Enable, ADCstarConversion,
    ADMUX = 0x00; //Vref external, right adjustment, start from adc0
    DDRF = 0x00;
    //do not forget to enable interrupts using sei()
}

void PWMinit() {
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
    TCCR1B |= _BV(CS10); // preskaler clk/8
    OCR1A = 0;
    OCR1B = 0;
    DDRB |= _BV(PB5) | _BV(PB6);
    TIMSK |= _BV(TOIE1);

}

void KEYSinit() {
    DDRC = _BV(PC0) | _BV(PC1);
}

void home() {
    while (1) {
        lcd.gotoxy(0, 0);
        lcd << "     ";
        lcd.gotoxy(0, 0);
        lcd << joy.x << '%';

        lcd.gotoxy(5, 0);
        lcd << "     ";
        lcd.gotoxy(5, 0);
        lcd << joy.y << '%';

        lcd.gotoxy(11, 0);
        lcd << "     ";
        lcd.gotoxy(11, 0);
        lcd << joy.z << '%';

        if (key_pressed(0) || key_pressed(1)) {
            lcd.clear();
            break;
        }
    }
}

int main() {
    lcd.cursorOff();

    // hadcore init
    ADCinit();
    PWMinit();
    KEYSinit();
    sei();

    lcd.define(heart, 0);
    lcd.define(left_arrow, 1);
    lcd.define(right_arrow, 2);

    // if eeprom is cleared
    if (contrast == -1) {
        contrast = 500;
        config_save(CONTRAST, contrast);
    }
    if (brightness == -1) {
        brightness = 500;
        config_save(BRIGHTNESS, brightness);
    }

    // welcome message
    lcd.gotoxy(0, 0);
    lcd << "     WITAM!    ";
    _delay_ms(1000);
    lcd.clear();


    home();
    while (1) {
        show_menu_pos();
        _delay_ms(10); // must be (wtf?)


        // if moving right
        while (joy.x > 20) {
            if (menu_pos < sizeof (menu) / sizeof (menu[0]) - 1) {
                menu_pos++;
                show_menu_pos();
                _delay_ms(100);
            }
        }

        // if moving left
        while (joy.x < -20) {
            if (menu_pos > 0) {
                menu_pos--;
                show_menu_pos();
                _delay_ms(100);
            }
        }

        if (key_pressed(1)){
            lcd.clear();
            home();
        }

        if (key_pressed(0)) {
            menu[menu_pos].func();
        }
    }
}


// menu functions

void menu_contrast() {
    lcd.clear();
    lcd.gotoxy(0, 0);

    lcd << "CONTRAST:";
    for (;;) {
        lcd.gotoxy(10, 0);
        lcd << (1023 - contrast) << "  ";

        if (joy.z > 20 || joy.z < -20) contrast -= joy.z / 20;
        if (contrast < 0) contrast = 0;
        else if (contrast > 1023) contrast = 1020;

        if (key_pressed(0)) {
            config_save(CONTRAST, contrast);
            lcd.clear();
            lcd.gotoxy(5, 1);
            lcd << "SAVED!";
            _delay_ms(500);
            lcd.clear();
            return;
        }

        if (key_pressed(1)) {
            contrast = config_read(CONTRAST);
            lcd.clear();
            lcd.gotoxy(3, 1);
            lcd << "CANCELED!";
            _delay_ms(500);
            lcd.clear();
            return;
        }
    }
}

void menu_brightness() {
    lcd.clear();
    lcd.gotoxy(0, 0);
    lcd << "BRIGHTNESS:";
    for (;;) {
        lcd.gotoxy(12, 0);
        lcd << brightness << "   ";

        if (joy.z > 20 || joy.z < -20) brightness += joy.z / 20;
        if (brightness < 0) brightness = 0;
        else if (brightness > 1023) brightness = 1020;

        if (key_pressed(0)) {
            config_save(BRIGHTNESS, brightness);
            lcd.clear();
            lcd.gotoxy(5, 1);
            lcd << "SAVED!";
            _delay_ms(500);
            lcd.clear();
            return;
        }

        if (key_pressed(1)) {
            brightness = config_read(BRIGHTNESS);
            lcd.clear();
            lcd.gotoxy(3, 1);
            lcd << "CANCELED";
            _delay_ms(500);
            lcd.clear();
            return;
        }
    }
}
