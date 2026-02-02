#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Button structure
 */
struct button
{
    volatile uint8_t* input_address;
    uint8_t pin; 
    uint32_t message;
};


/**
 * Button functions
 */
bool receive_input(uint8_t *button);
void setup_buttons(struct button* buttons[]);
void change_message(struct button* button, uint32_t message);

#endif // BUTTONS_H