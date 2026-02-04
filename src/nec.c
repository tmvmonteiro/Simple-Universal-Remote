#include "nec.h"
#include "interrupts.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

/**
 * Blink function
 * 
 * This function turns ON/OFF the LED associated
 * to a choosen PIN
 */
void blink(volatile uint8_t* data_register, uint8_t pin, uint8_t state){
    if (!data_register) return;

    if (state)
        *data_register |= (1 << pin);
    else
        *data_register &= ~(1 << pin);
}

/**********************************
*       Sender functions          *
**********************************/

/**
 * Send bit function
 * 
 * This function sends a bit (0/1) from
 * a IR LED using the NEC protocol.
 * For bit 1: 560us of pulse -> 1690us of silence.
 * For bit 0: 560us of pulse -> 560us of silence.
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

/**
 * Send lead function
 * 
 * This function sends a 9000us lead pulse followed 
 * by a 4500us of silence using the NEC protocol.
 */
void send_lead(){
    set_carrier(true);
    setup_timer(9000);
    while (!time_over);
    set_carrier(false);
    setup_timer(4500);
    while (!time_over);
}

/**
 * Send lead function
 * 
 * This function sends a 560 stop pulse using the NEC protocol.
 */
void send_stop(){
    set_carrier(true);
    setup_timer(560);
    while(!time_over);
    set_carrier(false);
}

/**
 * Send message function
 * 
 * This function sends a NEC protocol message via a IR LED.
 * A NEC message is composed by: the lead; 32bit message; stop.
 * The 32bit message, defined by the 'message' argument, is divided 
 * into 4 parts: the address; the inverse of the address; the command;
 * the inverse of the command.
 */
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

/**********************************
*       Receiver functions        *
**********************************/

/**
 * Receive message function
 * 
 * This function receivs a NEC protocol message via a IR Receiver.
 * First, it'll receive the NEC message and populate an array with its
 * timestamps (high and low time intervals). Next, it'll translate this 
 * timestamps into a bits (0/1) using the NEC protocol logic. Lastly, it
 * certificates if the message follows the NEC protocol.
 * Returns true if everything works. Returns false if not.
 */
bool receive_message(uint32_t *message){
    setup_receiver();
    while(!irr_finished);
    EIMSK &= ~(1 << INT0);
    timestamp_to_message(message);
    reset_interrupts_and_timers();
    return check_message(*message);
}

/**
 * Timestamp -> NEC message function
 * 
 * This function 'translates' an array of NEC timestamps (high/low
 * time intervals) in a 32bit NEC message.
 * Since all timestamps containing the time interval for no IR wave are
 * pair, the function will only interate through them.
 * Since time_stamps[2] contains the lead timestamp without IR wave, the loop
 * starts at time_stamps[4] and interates to time_stamps[66].
 * If 1125us < time_stamp < 2255us -> bit = 1.
 * Else bit = 0.
 */
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

/**
 * NEC message validation function
 * 
 * This function verifies the integrity of a 32-bit NEC message by
 * splitting it into its four constituent 8-bit components: Address,
 * Inverse Address, Command, and Inverse Command.
 * The validation logic checks if the Address and Command bytes are 
 * the exact logical inverses of their respective 'inv' counterparts.
 * Returns true if both the Address and Command pass the bitwise 
 * inversion check, ensuring the message was received without error.
 */
bool check_message(uint32_t message){
    uint8_t address = (uint8_t)(message & 0x000000FF);
    uint8_t inv_address = (uint8_t)((message & 0x0000FF00) >> 8);
    uint8_t command = (uint8_t)((message & 0x00FF0000) >> 16);
    uint8_t inv_command = (uint8_t)((message & 0xFF000000) >> 24);
    
    bool addr_ok = (address == (uint8_t)~inv_address);
    bool cmd_ok  = (command == (uint8_t)~inv_command);

    return (addr_ok && cmd_ok);
}