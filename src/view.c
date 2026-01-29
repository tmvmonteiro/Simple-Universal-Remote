#include <stdint.h>
#include <stdbool.h>
#include "view.h"
#include "model.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile bool time_over = false;
volatile uint16_t timer_ticks = 0;

void blink(volatile uint8_t* data_register, uint8_t pin, uint8_t state){
    if (!data_register) return;

    if (state)
        *data_register |= (1 << pin);
    else
        *data_register &= ~(1 << pin);
}

void send_bit(uint8_t bit){
    set_carrier(true);
    setup_timer(560);
    while(!time_over);
    set_carrier(false);
    if (bit) setup_timer(1690);
    else setup_timer(560);
    while(!time_over);
}

void send_lead(){
    set_carrier(true);
    setup_timer(9000);
    while (!time_over);
    set_carrier(false);
    setup_timer(4500);
    while (!time_over);
}

void send_message(uint32_t message){
    setup_38khz_hardware();
    send_lead();
    for (int i = 0; i < 32; i++) {
        uint8_t bit = (message >> i) & 0x01;
        send_bit(bit);
    }
    set_carrier(true);
    setup_timer(560);
    while(!time_over);
    set_carrier(false);
}

void set_carrier(bool state){
    if (state) {
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
    TCCR0A = (1 << WGM01);   
    TCCR0B = (1 << CS01);
    OCR0A  = 19;
    TIMSK0 |= (1 << OCIE0A);
    sei();
}

ISR(TIMER0_COMPA_vect){
    if (timer_ticks > 0) timer_ticks--;
    else time_over = true;
}