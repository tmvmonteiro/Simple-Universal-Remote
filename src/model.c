#include <stdint.h>
#include "model.h"
#include <avr/io.h>

void setup_portB(){
    PORTB = 0;
    DDRB = 6;
}

void setup_portC(){
    PORTC = 0;
    DDRC = 63;
}

void setup_buttons(){
    setup_portB();
    setup_portC();
}