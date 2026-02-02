#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "interrupts.h"

/**
 * TIMER0 PART - FOR BOTH
 */
volatile bool timer0_function;

ISR(TIMER0_COMPA_vect) {
    if (timer0_function == RECEIVER) receiver_ticks++;
}

/**
 * IR LED PART
 */

/**
 * IRR PART
 */
volatile uint16_t time_stamps[67];
volatile uint16_t time_stamp;
volatile uint16_t receiver_ticks;
volatile uint8_t bit_counter; // 0-66
volatile bool irr_state;
volatile bool irr_finished;

ISR(INT0_vect) {
    time_stamp = receiver_ticks * 10;
    time_stamps[bit_counter++] = time_stamp;
    if (bit_counter == 67) irr_finished = true;
    receiver_ticks = 0;
}

void timestamp_to_message(uint32_t *message){
    *message = 0;
    uint8_t bit_pos = 0;
    for (int i = 4; i < 67; i+=2)
    {
        time_stamp = time_stamps[i];
        if ((BIT1_MIN < time_stamp) && (time_stamp < BIT1_MAX)) *message |= ((uint32_t)1 << bit_pos);
        bit_pos++;
    }
    
}

void setup_receiver(){
    cli();

    // Variables setup
    timer0_function = RECEIVER;
    for (int i = 0; i < 67; i++) {
        time_stamps[i] = 0;
    }
    time_stamp = 0;
    receiver_ticks = 0;
    bit_counter = 0;
    irr_finished = false;

    // Timer0 Setup
    TCNT0  = 0;
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS01);
    OCR0A  = 19;
    TIMSK0 |= (1 << OCIE0A);

    // Setup IR Pin
    DDRD &= ~(1 << DDD2);
    EICRA |= (1 << ISC00);
    EIMSK |= (1 << INT0);

    sei();
}