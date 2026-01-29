#ifndef VIEW_H
#define VIEW_H

#include <stdint.h>
#include <stdbool.h>

void blink(volatile uint8_t* data_register, uint8_t pin, uint8_t state);
void send_bit(uint8_t bit);
void send_lead();
void send_message(uint32_t message);
void set_carrier(bool state);
void setup_38khz_hardware();
void setup_timer(uint16_t time_us);

#endif // VIEW_H