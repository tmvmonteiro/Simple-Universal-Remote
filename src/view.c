#include <stdint.h>
#include <stdbool.h>
#include "view.h"
#include "model.h"

uint8_t time;

void blink(volatile uint8_t* data_register, uint8_t pin){
    if (data_register != 0) *data_register = pin;
}

void send_bit(volatile uint8_t* data_register, uint8_t pin, uint8_t bit){
    blink(data_register, pin);
    wait(560);
    blink(data_register, OFF); 
    if(bit == 1) wait(1690);
    else wait(560);
}

void send_lead(volatile uint8_t* data_register, uint8_t pin){
    blink(data_register, pin);
    wait(9000);
    blink(data_register, OFF);
    wait(4500);
}

void send_message(volatile uint8_t* data_register, uint8_t pin, uint32_t message){
    send_lead(data_register, pin);
    for (int i = 0; i < 32; i++) {
        uint8_t bit = (message >> i) & 0x01;
        send_bit(data_register, pin, bit);
    }
}

void timer(uint8_t time){

}