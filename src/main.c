#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "leds.h"
#include "buttons.h"
#include "timers.h"
#include <IRremote.h>

void main(){
    struct button buttons[6];
    setup_ports();
    setup_buttons();

    IrReceiver.begin(PINB0, ENABLE_LED_FEEDBACK);
    IrSender.begin();

    while (true)
    {
        _delay_ms(200);
        struct button button;
        while (!PINC);
        select_button(&button, buttons);
        switch (button.pin)
        {
        case PINC5:
            _delay_ms(200);
            struct button change_button;
            blink(PORTB, PORTB2, ON);
            while (true)
            {
                while (!PINC);
                select_button(&change_button, buttons);
                if (change_button.pin != button.pin) break;
            }
            while (!IrReceiver.decode());
            blink(PORTB, PORTB2, OFF);
            uint32_t message = IrReceiver.decodedIRData.decodedRawData;
            change_message(&change_button, message);
            IrReceiver.resume();
            break;
        
        default:
            send_message(button.message);
            break;
        }
    }
}