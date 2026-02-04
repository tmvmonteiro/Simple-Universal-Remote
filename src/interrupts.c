#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "interrupts.h"
#include <stdio.h>
#include <string.h>

/**
 * TIMER0 PART - FOR BOTH
 */
volatile bool timer0_function;

/**
 * Timer0 Compare Match A Interrupt Service Routine
 * 
 * This ISR handles the time-keeping for both sending and receiving IR data.
 * If set to RECEIVER: It increments receiver_ticks to measure pulse durations.
 * If set to SENDER: It decrements sender_ticks until they reach zero, 
 * marking the end of a specific IR signal interval (high or low).
 */
ISR(TIMER0_COMPA_vect) {
    if (timer0_function == RECEIVER){
        receiver_ticks++;
    }
    else if (timer0_function == SENDER){
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

/**
 * IR Carrier Wave Control
 * 
 * This function toggles the 38kHz carrier wave generation on Timer1.
 * If state is true: Connects the timer to the OC1A pin to start the wave.
 * If state is false: Disconnects the timer and forces the pin LOW to 
 * ensure the IR LED is fully turned off.
 */
void set_carrier(bool state){
    if (state) {
        TCNT1 = 0;
        TCCR1A |= (1 << COM1A0);
    } else {
        TCCR1A &= ~(1 << COM1A0);
        PORTB &= ~(1 << PORTB1);
    }
}

/**
 * Timer Setup for Pulse Generation
 * 
 * Configures Timer0 to act as a countdown timer for IR pulse transmission.
 * It converts the requested microseconds (us) into 10us "ticks" and 
 * enables the output compare interrupt to track the elapsed duration.
 */
void setup_timer(uint16_t time_us){
    cli();

    // Variables setup
    timer0_function = SENDER;
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

/**
 * IR Sender Hardware Configuration
 * 
 * Prepares Timer1 to generate the physical 38kHz carrier signal on PORTB1.
 * It sets the Clear Timer on Compare (CTC) mode and defines the period
 * required to match the standard IR carrier frequency.
 */
void setup_sender(){
    // Timer1 Setup
    DDRB |= (1 << PORTB1);
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

/**
 * External Interrupt 0 (INT0) Service Routine
 * 
 * Triggered on every logic change (edge) from the IR receiver.
 * It records the time elapsed since the last edge (in microseconds) 
 * into the time_stamps array. Once 67 edges are recorded (the full 
 * NEC frame), it marks the capture as finished and disables the interrupt.
 */
ISR(INT0_vect) {
    if (!irr_finished){
        time_stamp = receiver_ticks * 10;
        time_stamps[bit_counter++] = time_stamp;
        if (bit_counter >= 67) {
            irr_finished = true;
            EIMSK &= ~(1 << INT0);
        }
    }
    receiver_ticks = 0;
}

/**
 * IR Receiver Initialization
 * 
 * Configures the system to listen for incoming NEC IR signals.
 * This clears the timestamp buffer, resets the bit counter, and 
 * initializes Timer0 to 10us tick mode. It also enables INT0 to 
 * trigger on any logical change of the IR input pin.
 */
void setup_receiver(){
    cli();

    // Variables setup
    timer0_function = RECEIVER;
    memset((void*)time_stamps, 0, sizeof(time_stamps));
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
    EIFR |= (1 << INTF0);
    EIMSK |= (1 << INT0);

    sei();
}

/**
 * RESET PART
 */

/**
 * Global Hardware and Variable Reset
 * 
 * Stops all IR-related activities by disabling Timer0, Timer1, and 
 * External Interrupts. It resets all internal counters and state 
 * flags to their default values, effectively returning the IR 
 * subsystem to an idle, clean state.
 */
void reset_interrupts_and_timers(){
    cli();

    // Timer0 Reset
    TCCR0A = 0;
    TCCR0B = 0;
    TIMSK0 &= ~(1 << OCIE0A);
    TCNT0 = 0;

    // Timer1 Reset
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    PORTB &= ~(1 << PB1);

    // INT0 Reset
    EIMSK &= ~(1 << INT0);
    EICRA &= ~((1 << ISC01) | (1 << ISC00));

    // Variables reset
    sender_ticks = 0;
    receiver_ticks = 0;
    time_over = false;
    bit_counter = 0;
    irr_finished = false;
    timer0_function = NONE;

    sei();
}