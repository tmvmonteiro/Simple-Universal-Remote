#include <stdint.h>
#include <stdbool.h>
#include "view.h"
#include "model.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile bool time_over = false;
volatile uint16_t timer_ticks = 0;

void blink(volatile uint8_t* data_register, uint8_t pin, uint8_t state) {
    if (!data_register) return;

    if (state)
        *data_register |= (1 << pin);
    else
        *data_register &= ~(1 << pin);
}


void send_bit(volatile uint8_t* data_register, uint8_t pin, uint8_t bit){
    // to implement
}

void send_lead(volatile uint8_t* data_register, uint8_t pin){
    // to implement
}


void send_message(volatile uint8_t* data_register, uint8_t pin, uint32_t message){
    send_lead(data_register, pin);
    for (int i = 0; i < 32; i++) {
        uint8_t bit = (message >> i) & 0x01;
        send_bit(data_register, pin, bit);
    }
}

ISR(TIMER0_COMPA_vect) {
    if (timer_ticks > 0) {
        timer_ticks--;
    } else {
        time_over = true;
    }
}

void setup_38khz_frequency(volatile uint8_t* data_register, uint8_t pin){
    TCCR1A = (1 << COM1A0);
    TCCR1B = (1 << WGM12) | (1 << CS10);
    OCR1A = 210;

    blink(data_register, pin, ON);
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