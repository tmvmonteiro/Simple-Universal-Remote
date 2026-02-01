/*#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "timers.h"
#include "leds.h"

volatile bool time_over = false;
volatile uint16_t timer_ticks = 0;

void set_carrier(bool state){
    if (state) {
        TCNT1 = 0;
        TCCR1A |= (1 << COM1A0);
    } else {
        TCCR1A &= ~(1 << COM1A0);
        PORTB &= ~(1 << PB1);
    }
}

void setup_38khz_hardware(){
    DDRB |= (1 << PB1);
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS10);
    OCR1A = 210;
}

void setup_timer(uint16_t time_us){
    cli();
    time_over = false;
    timer_ticks = time_us / 10;
    TCNT0 = 0;
    TCCR0A = (1 << WGM01);   
    TCCR0B = (1 << CS01);
    OCR0A  = 19;
    TIMSK0 |= (1 << OCIE0A);
    sei();
}

ISR(TIMER0_COMPA_vect){
    if (timer_ticks > 0) timer_ticks--;
    else {
        time_over = true;
        TIMSK0 &= ~(1 << OCIE0A);
    }
}*/