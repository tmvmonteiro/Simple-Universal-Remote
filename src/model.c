#include <stdint.h>
#include "model.h"

void setup_portB(){
    *PORTB = 0;
    *DDRB = PORTB1 + PORTB2;
}

void setup_portC(){
    *PORTC = 0;
    *DDRC = PORTC0 + PORTC1 + PORTC2 + PORTC3 + PORTC4 + PORTC5;
}

void setup_buttons(){
    setup_portB();
    setup_portC();
}