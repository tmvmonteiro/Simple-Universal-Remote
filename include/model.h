#ifndef MODEL_H
#define MODEL_H

/**
 * Important PortB memory registers
 */
#define PORTB ((volatile uint8_t*)0x25)
#define DDRB  ((volatile uint8_t*)0x24)
#define PINB ((volatile uint8_t*)0x23)

#define PORTB0 1
#define PORTB1 2
#define PORTB2 4

/**
 * Important PortC memory registers
 */
#define PORTC ((volatile uint8_t*)0x28)
#define DDRC  ((volatile uint8_t*)0x27)
#define PINC ((volatile uint8_t*)0x26)

#define PORTC0 1
#define PORTC1 2
#define PORTC2 4
#define PORTC3 8
#define PORTC4 16
#define PORTC5 32

/**
 * Other important notations
 */
#define OFF 0

void setup_portB();
void setup_portC();
void setup_buttons();

#endif // MODEL_H