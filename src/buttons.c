#include "buttons.h"
#include <avr/io.h>
#include <stddef.h>

void setup_buttons(struct button* buttons[]){
    /**
     * Predefined Button setup
     * May change in the future
     */
    static struct button button0 = {&PINC, PINC0, 0x20DF10EF}; // Power ON/OFF
    static struct button button1 = {&PINC, PINC1, 0x20DF40BF}; // Volume UP
    static struct button button2 = {&PINC, PINC2, 0x20DFC03F}; // Volume DOWN
    static struct button button3 = {&PINC, PINC3, 0x20DF00FF}; // Channel UP
    static struct button button4 = {&PINC, PINC4, 0x20DF807F}; // Channel DOWN

    buttons[0] = &button0;
    buttons[1] = &button1;
    buttons[2] = &button2;
    buttons[3] = &button3;
    buttons[4] = &button4;
}

void change_message(struct button* button, uint32_t message){
    if (button != NULL) button->message = message;
}