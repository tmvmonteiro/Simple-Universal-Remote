#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Important notations
*/
#define RECEIVER true
#define SENDER false

#define HIGH true
#define LOW false

#define BIT0_MIN 0
#define BIT0_MAX 1125
#define BIT1_MIN 1125
#define BIT1_MAX 2255

extern volatile bool timer0_function;

extern volatile uint16_t time_stamps[67];
extern volatile uint16_t time_stamp;
extern volatile uint16_t receiver_ticks;
extern volatile uint8_t bit_counter;
extern volatile bool irr_state;
extern volatile bool irr_finished;

/**
 * Interrupt functions
 */
void timestamp_to_message(uint32_t *message);
void setup_receiver();

#endif // INTERRUPTS_H