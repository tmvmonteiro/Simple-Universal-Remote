#include <stdint.h>
#include "model.h"
#include <avr/io.h>

/**
 * PORTB setup
 * 
 * This function is responsible for setting up
 * the micro-controller PB1 and PB2 (PORTB)
 * as Output
 */
void setup_portB(){
    PORTB = 0;
    DDRB = 6;
}

/**
 * PORTC setup
 * 
 * This function is responsible for setting up
 * the micro-controller PC0, PC1, PC2, PC3, PC4 
 * and PC5 (PORTC) as Input
 */
void setup_portC(){
    DDRC = 0;
    PORTC = 0x3F;
}

/**
 * PORTB and PORTC setup
 * 
 * This function is responsible for 
 * calling the above functions
 */
void setup_ports(){
    setup_portB();
    setup_portC();
}