#ifndef NEC_H
#define NEC_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Important notations
 */
#define ON 1
#define OFF 0

/**
 * Debug functions
 */
void blink(volatile uint8_t* data_register, uint8_t pin, uint8_t state);

/**
 * Sender functions
 */
void send_bit(uint8_t bit);
void send_lead();
void send_stop();
void send_message(uint32_t message);

/**
 * Receiver functions
 */
bool receive_message(uint32_t *message);
void timestamp_to_message(uint32_t *message);
bool check_message(uint32_t message);

#endif // NEC_H