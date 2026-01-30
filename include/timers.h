#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>
#include <stdbool.h>

extern volatile bool time_over;
extern volatile uint16_t timer_ticks;

/**
 * Timer functions
 */
void set_carrier(bool state);
void setup_38khz_hardware();
void setup_timer(uint16_t time_us);

#endif // TIMERS_H