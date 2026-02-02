#include <unity.h>
#include <stdint.h>
#include <util/delay.h>
#include "model.h"
#include "buttons.h"
#include <avr/io.h>

struct button* buttons[5];

/**
 * setUp: Runs automatically BEFORE each test case.
 * Used to reset the hardware state to a known baseline.
 */
void setUp(void) {
    setup_portC();
    setup_buttons(buttons);
}

/**
 * tearDown: Runs automatically AFTER each test case.
 * Empty here as no specific hardware cleanup is required.
 */
void tearDown(void) {
}

/**
 * TEST CASE: Setup PortB and PortC registers
 * Validates that the previous pins off PORTB, DDRB, PORTC and DDRC register bits are correctly assigned
 */
void test_receive_input(void){
    uint8_t desired_button = buttons[0]->pin;
    uint8_t button = 0; 
    while (!receive_input(&button));
    TEST_ASSERT_EQUAL(desired_button, button);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) {
    _delay_ms(200); 
    UNITY_BEGIN();
    RUN_TEST(test_receive_input);
    return UNITY_END();
}