#ifndef VIEW_H
#define VIEW_H

#include <stdint.h>

void blink(volatile uint8_t* data_register, uint8_t pin);
void send_bit(volatile uint8_t* data_register, uint8_t pin, uint8_t bit);
void send_lead(volatile uint8_t* data_register, uint8_t pin);
void send_message(volatile uint8_t* data_register, uint8_t pin, uint32_t message);

#endif // VIEW_H