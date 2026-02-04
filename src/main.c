#include <util/delay.h>
#include <avr/io.h>
#include "buttons.h"
#include "interrupts.h"
#include "model.h"
#include "nec.h"

/**
 * Main Application Loop
 * 
 * This program implements a programmable NEC IR remote duplicator. 
 * It operates in two primary modes:
 * 1. Command Learning: Triggered by PINC5, allowing the user to map a 
 * physical button to a new captured IR signal.
 * 2. Command Transmission: The default state where pressing a button 
 * replays its stored 32-bit NEC message.
 */
int main(){
  uint8_t button = 0;
  uint8_t changing_button = 0;
  struct button* buttons[5];
  uint32_t in_message = 0;
  uint32_t out_message = 0;

  setup_ports();
  setup_buttons(buttons);
  while (1){
    while(!receive_input(&button));
    switch (button)
    {
    case PINC5:
      /**
       * Receiving NEC message logic
       */
      blink(&PORTB, PORTB2, ON);
      _delay_ms(2000);
      while (!receive_input(&changing_button));
      blink(&PORTB, PORTB2, OFF);

      if (changing_button == PINC5){ // Cancel changing function
        _delay_ms(200);
        blink(&PORTB, PORTB2, ON);
        _delay_ms(200);
        blink(&PORTB, PORTB2, OFF);
        _delay_ms(200);
      } 
      else if (receive_message(&in_message)){ // Successfully received NEC message
        change_message(buttons[changing_button], in_message);
        _delay_ms(200);
        blink(&PORTB, PORTB2, ON);
        _delay_ms(200);
        blink(&PORTB, PORTB2, OFF);
        _delay_ms(200);
        blink(&PORTB, PORTB2, ON);
        _delay_ms(200);
        blink(&PORTB, PORTB2, OFF);
        _delay_ms(200);
      }
      else { // Unsuccessfully received NEC message
        _delay_ms(200);
        blink(&PORTB, PORTB2, ON);
        _delay_ms(200);
        blink(&PORTB, PORTB2, OFF);
        _delay_ms(200);
      }
      _delay_ms(2000);

      break;
    
    default: 
      /**
       * Sending NEC message logic
       */
      out_message = buttons[button]->message;
      send_message(out_message);
      blink(&PORTB, PORTB2, ON);
      _delay_ms(200);
      blink(&PORTB, PORTB2, OFF);
      _delay_ms(200);
      blink(&PORTB, PORTB2, ON);
      _delay_ms(200);
      blink(&PORTB, PORTB2, OFF);
      break;
    }

    /**
     * Reset variables
     */
    button = 0;
    changing_button = 0;
    in_message = 0;
    out_message = 0;
  }

  return 0;
}