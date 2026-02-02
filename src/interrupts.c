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
    else{
        if (sender_ticks > 0) sender_ticks--;
        else {
            time_over = true;
            TIMSK0 &= ~(1 << OCIE0A);
        }
    }
}

/**
 * IR LED PART
 */
volatile uint16_t sender_ticks;
volatile bool time_over;

void set_carrier(bool state){
    if (state) {
        TCNT1 = 0;
        TCCR1A |= (1 << COM1A0);
    } else {
        TCCR1A &= ~(1 << COM1A0);
        PORTB &= ~(1 << PB1);
    }
}

void setup_timer(uint16_t time_us){
    cli();

    // Variables setup
    time_over = false;
    sender_ticks = time_us / 10;

    // Timer0 Setup
    TCNT0 = 0;
    TCCR0A = (1 << WGM01);   
    TCCR0B = (1 << CS01);
    OCR0A  = 19;
    TIMSK0 |= (1 << OCIE0A);

    sei();
}

void setup_sender(){
    // Timer1 Setup
    DDRB |= (1 << PB1);
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS10);
    OCR1A = 210;
}

/**
 * IRR PART
 */
volatile uint16_t time_stamps[67];
volatile uint16_t time_stamp;
volatile uint16_t receiver_ticks;
volatile uint8_t bit_counter; // 0-66
volatile bool irr_finished;

ISR(INT0_vect) {
    time_stamp = receiver_ticks * 10;
    time_stamps[bit_counter++] = time_stamp;
    if (bit_counter == 67) irr_finished = true;
    receiver_ticks = 0;
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