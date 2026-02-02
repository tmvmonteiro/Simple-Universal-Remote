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

/**
 * TIMER0 PART - FOR BOTH
 */
extern volatile bool timer0_function;

/**
 * IR LED PART
 */
extern volatile uint16_t sender_ticks;
extern volatile bool time_over;

void set_carrier(bool state);
void setup_timer(uint16_t time_us);
void setup_sender();

/**
 * IRR PART
 */
extern volatile uint16_t time_stamps[67];
extern volatile uint16_t time_stamp;
extern volatile uint16_t receiver_ticks;
extern volatile uint8_t bit_counter;
extern volatile bool irr_finished;

void setup_receiver();

/**
 * RESET PART
 */
void reset_interrupts_and_timers();

#endif // INTERRUPTS_H