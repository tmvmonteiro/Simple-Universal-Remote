#include "buttons.h"
#include <stdbool.h>
#include <avr/io.h>
#include <stddef.h>

/**
 * Input handling
 * 
 * This function handles input coming from
 * PC0, PC1, PC2, PC3, PC4 and PC5 (PORTC).
 * Returs false if no input received.
 * Returns true if input is received. 'button'
 * value changes to the number of the corresponding
 * button pressed at the circuit. 
 */
bool receive_input(uint8_t *button){
    uint8_t port_state = (~PINC) & 0x3F;
    
    if (port_state != 0) { 
        for (uint8_t i = 0; i < 6; i++) {
            if (port_state & (1 << i)){
                *button = i;
                return true;
            }
        }
    }
    return false;
}

/**
 * Default buttons
 * 
 * This functions sets up the default values
 * for the NEC messages. In this case, it'll 
 * probably work for a LG device.
 */
void setup_buttons(struct button* buttons[]){
    /**
     * Predefined Button setup
     * May change in the future
     */
    static struct button button0 = {&PINC, PINC0, 0xF708FB04}; // Power ON/OFF
    static struct button button1 = {&PINC, PINC1, 0xFD02FB04}; // Volume UP
    static struct button button2 = {&PINC, PINC2, 0xFC03FB04}; // Volume DOWN
    static struct button button3 = {&PINC, PINC3, 0xFF00FB04}; // Channel UP
    static struct button button4 = {&PINC, PINC4, 0xFE01FB04}; // Channel DOWN

    buttons[0] = &button0;
    buttons[1] = &button1;
    buttons[2] = &button2;
    buttons[3] = &button3;
    buttons[4] = &button4;
}

/**
 * Changing button NEC message
 * 
 * This functions changes the NEC message associated to
 * a choosen 'button' with a given one.
 */
void change_message(struct button* button, uint32_t message){
    if (button != NULL) button->message = message;
}