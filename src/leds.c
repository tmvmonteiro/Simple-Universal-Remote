#include <stdint.h>
#include <stdbool.h>
#include "leds.h"
#include "model.h"
#include "timers.h"
#include <avr/interrupt.h>
#include <avr/io.h>

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

void send_stop(){
    set_carrier(true);
    setup_timer(560);
    while(!time_over);
    set_carrier(false);
}

void send_message(uint32_t message){
    setup_38khz_hardware();
    send_lead();
    for (int i = 0; i < 32; i++) {
        uint8_t bit = (message >> i) & 0x01;
        send_bit(bit);
    }
    send_stop();
}