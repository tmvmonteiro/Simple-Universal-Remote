#include "buttons.h"
#include <avr/io.h>
#include <stddef.h>

void select_button(struct button* button, struct button* buttons[]){
    for (size_t i = 0; i < 6; i++)
    {
        if (PINC == (uint8_t)(1 << PINC0)){
            *button = *buttons[i];
            return;
        }
    }
}

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
    static struct button button5 = {&PINC, PINC4, 0};          // Special Button: Change 'message' of other buttons

    buttons[0] = &button0;
    buttons[1] = &button1;
    buttons[2] = &button2;
    buttons[3] = &button3;
    buttons[4] = &button4;
    buttons[5] = &button5;
}

void change_message(struct button* button, uint32_t message){
    if (button != NULL) button->message = message;
}