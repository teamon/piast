#ifndef PIAST_H_
#define PIAST_H_

/**
 * @file piast.h
 * @defgroup piast Piast1
 * 
 * @brief  Multifuncional wireless device controler
 * 
 * @version 0.1
 * @author Tymon Tobolski http://teamon.eu
**/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

/**
 * @def config_read
 * Read config from eeprom.
 * @ingroup piast
**/
#define config_read(addr) (int)eeprom_read_word((uint16_t*)addr)

/**
 * @def config_save
 * Save config to eeprom.
 * @ingroup piast
**/
#define config_save(addr, value) eeprom_write_word((uint16_t*)addr, (uint16_t)value)

/**
 * @def KEY_DOWN
 * Check if key is pressed.
 * @ingroup piast
**/
#define KEY_DOWN(n) (PINC & _BV(n))


#define BRIGHTNESS 0
#define CONTRAST 2


// headers

// util.cpp
bool key_pressed(int n);

#endif
