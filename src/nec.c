#include "nec.h"
#include "interrupts.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
/**
 * Debug functions
 */
void blink(volatile uint8_t* data_register, uint8_t pin, uint8_t state){
    if (!data_register) return;

    if (state)
        *data_register |= (1 << pin);
    else
        *data_register &= ~(1 << pin);
}

/**
 * Sender functions
 */
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
    setup_sender();
    send_lead();
    for (int i = 0; i < 32; i++) {
        uint8_t bit = (message >> i) & 0x01;
        send_bit(bit);
    }
    send_stop();
    reset_interrupts_and_timers(); 
}

/**
 * Receiver functions
 */
bool receive_message(uint32_t *message){
    setup_receiver();
    while(!irr_finished);
    EIMSK &= ~(1 << INT0);
    timestamp_to_message(message);
    reset_interrupts_and_timers();
    return check_message(*message);
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

bool check_message(uint32_t message){
    uint8_t address = (uint8_t)(message & 0x000000FF);
    uint8_t inv_address = (uint8_t)((message & 0x0000FF00) >> 8);
    uint8_t command = (uint8_t)((message & 0x00FF0000) >> 16);
    uint8_t inv_command = (uint8_t)((message & 0xFF000000) >> 24);
    
    bool addr_ok = (address == (uint8_t)~inv_address);
    bool cmd_ok  = (command == (uint8_t)~inv_command);

    return (addr_ok && cmd_ok);
}