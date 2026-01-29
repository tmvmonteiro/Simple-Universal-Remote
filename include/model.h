#ifndef MODEL_H
#define MODEL_H

/**
 * Important PortB memory registers
 */
#define PORTB ((volatile uint8_t*)0x25)
#define DDRB  ((volatile uint8_t*)0x24)
#define PINB ((volatile uint8_t*)0x23)

/**
 * Important PortC memory registers
 */
#define PORTC ((volatile uint8_t*)0x28)
#define DDRC  ((volatile uint8_t*)0x27)
#define PINC ((volatile uint8_t*)0x26)

void setup_portB();
void setup_portC();
void setup_buttons();

#endif // MODEL_H