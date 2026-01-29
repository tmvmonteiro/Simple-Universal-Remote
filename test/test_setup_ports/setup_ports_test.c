#include <unity.h>
#include <stdint.h>
#include <util/delay.h>
#include "model.h"
#include <avr/io.h>

/**
 * setUp: Runs automatically BEFORE each test case.
 * Used to reset the hardware state to a known baseline.
 */
void setUp(void) {
    // Set all pins of PORTB and PORTC to LOW (0V)
    PORTB = 0;
    PORTC = 0;

    // Configure all Pins to default value: 0
    DDRB = 0;
    DDRC = 0;
}

/**
 * tearDown: Runs automatically AFTER each test case.
 * Empty here as no specific hardware cleanup is required.
 */
void tearDown(void) {
}

/**
 * TEST CASE: Setup PortB registers
 * Validates that first 3 pins PORTB and DDRB register bits are correctly assigned 
 */
void test_portb_setup(void) {
    TEST_ASSERT_EQUAL_HEX8(0, PORTB);
    TEST_ASSERT_EQUAL_HEX8(0, DDRB);
    setup_portB();
    TEST_ASSERT_EQUAL_HEX8(0, PORTB);
    TEST_ASSERT_EQUAL_HEX8(6, DDRB);
}

/**
 * TEST CASE: Setup PortC registers
 * Validates that that first 6 pins PORTC and DDRC register bits are correctly assigned
 */
void test_portc_setup(void) {
    TEST_ASSERT_EQUAL_HEX8(0, PORTC);
    TEST_ASSERT_EQUAL_HEX8(0, DDRC);
    setup_portC();
    TEST_ASSERT_EQUAL_HEX8(0, PORTC);
    TEST_ASSERT_EQUAL_HEX8(63, DDRC);
}

/**
 * TEST CASE: Setup the Buttons Port registers
 * Validates that the previous pins off PORTB, DDRB, PORTC and DDRC register bits are correctly assigned
 */
void test_buttons_setup(void) {
    TEST_ASSERT_EQUAL_HEX8(0, PORTB);
    TEST_ASSERT_EQUAL_HEX8(0, DDRB);
    TEST_ASSERT_EQUAL_HEX8(0, PORTC);
    TEST_ASSERT_EQUAL_HEX8(0, DDRC);
    setup_buttons();
    TEST_ASSERT_EQUAL_HEX8(0, PORTB);
    TEST_ASSERT_EQUAL_HEX8(6, DDRB);
    TEST_ASSERT_EQUAL_HEX8(0, PORTC);
    TEST_ASSERT_EQUAL_HEX8(63, DDRC);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_portb_setup);
    _delay_ms(200); 
    RUN_TEST(test_portc_setup);
    _delay_ms(200); 
    RUN_TEST(test_buttons_setup);
    return UNITY_END();
}