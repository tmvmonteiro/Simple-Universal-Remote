#include <stdint.h>
#include "model.h"
#include <avr/io.h>

void setup_portB(){
    PORTB = 0;
    DDRB = 6;
}

void setup_portC(){
    DDRC = 0;
    PORTC = 0x3F;
}

void setup_ports(){
    setup_portB();
    setup_portC();
}