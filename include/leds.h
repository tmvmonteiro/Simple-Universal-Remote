#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Important notations
 */
#define ON 1
#define OFF 0

/**
 * LED functions
 */
void blink(volatile uint8_t* data_register, uint8_t pin, uint8_t state);
void send_bit(uint8_t bit);
void send_lead();
void send_message(uint32_t message);

#endif // LEDS_H