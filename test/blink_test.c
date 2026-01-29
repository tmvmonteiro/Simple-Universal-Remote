#include <unity.h>
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "view.h"

#define DDRB  ((volatile uint8_t*)0x24)
#define PORTB ((volatile uint8_t*)0x25)

/**
 * setUp: Runs automatically BEFORE each test case.
 * Used to reset the hardware state to a known baseline.
 */
void setUp(void) {
    // Set all pins of PORTB to LOW (0V)
    *PORTB = 0;
    
    // Configure Pin 0 (D8 on Arduino Uno) as an OUTPUT by setting bit 0 to 1
    *DDRB = 1;
}

/**
 * tearDown: Runs automatically AFTER each test case.
 * Empty here as no specific hardware cleanup is required.
 */
void tearDown(void) {
}

/**
 * TEST CASE: Turn ON LED
 * Validates that the blink function writes 0x01 to the correct register.
 */
void test_led_d8_setup_and_turn_on(void) {
    TEST_ASSERT_BIT_HIGH(0, *DDRB);
    blink(PORTB, 0x01);
    TEST_ASSERT_EQUAL_HEX8(0x01, *PORTB);
    TEST_ASSERT_BIT_HIGH(0, *PORTB);
}

/**
 * TEST CASE: Turn OFF LED
 * Validates that the blink function writes 0x00 to the correct register.
 */
void test_led_d8_setup_and_turn_off(void) {
    TEST_ASSERT_BIT_HIGH(0, *DDRB);
    blink(PORTB, 0x0);
    TEST_ASSERT_EQUAL_HEX8(0x0, *PORTB);
    TEST_ASSERT_BIT_LOW(0, *PORTB);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) {
    _delay_ms(2000); 
    UNITY_BEGIN();
    RUN_TEST(test_led_d8_setup_and_turn_on);
    _delay_ms(2000); 
    RUN_TEST(test_led_d8_setup_and_turn_off);
    return UNITY_END();
}