#include <unity.h>
#include <stdint.h>
#include <util/delay.h>
#include "nec.h"
#include "model.h"
#include <avr/io.h>

/**
 * setUp: Runs automatically BEFORE each test case.
 * Used to reset the hardware state to a known baseline.
 */
void setUp(void) {
    setup_portB();
}

/**
 * tearDown: Runs automatically AFTER each test case.
 * Empty here as no specific hardware cleanup is required.
 */
void tearDown(void) {
}

/**
 * TEST CASE: Turn ON LED
 * Validates that the blink function writes 0x04 to the correct register.
 */
void test_led_d10_setup_and_turn_on(void) {
    blink(&PORTB, PORTB2, ON);
    TEST_ASSERT_EQUAL_HEX8(0x04, PORTB);
    TEST_ASSERT_BIT_HIGH(PORTB2, PORTB);
}

/**
 * TEST CASE: Turn OFF LED
 * Validates that the blink function writes 0x00 to the correct register.
 */
void test_led_d10_setup_and_turn_off(void) {
    blink(&PORTB, PORTB2, OFF);
    TEST_ASSERT_EQUAL_HEX8(0x0, PORTB);
    TEST_ASSERT_BIT_LOW(PORTB2, PORTB);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) { 
    UNITY_BEGIN();
    RUN_TEST(test_led_d10_setup_and_turn_on);
    _delay_ms(2000); 
    RUN_TEST(test_led_d10_setup_and_turn_off);
    return UNITY_END();
}