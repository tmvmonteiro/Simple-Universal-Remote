#include <stdint.h>
#include "model.h"
#include <avr/io.h>

void setup_portB(){
    PORTB = 0;
    DDRB = 6;
}

void setup_portC(){
    PORTC = 0;
    DDRC = 0;
}

void setup_ports(){
    setup_portB();
    setup_portC();
}