#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Important notations
*/
#define RECEIVER true
#define SENDER false
#define HIGH true
#define LOW false

extern volatile bool timer0_function;

extern volatile uint16_t time_stamps[66];
extern volatile uint16_t time_stamp;
extern volatile uint16_t receiver_ticks;
extern volatile uint8_t bit_counter;
extern volatile bool irr_state;
extern volatile bool irr_finished;

/**
 * Interrupt functions
 */
void setup_receiver();

#endif // BUTTONS_H