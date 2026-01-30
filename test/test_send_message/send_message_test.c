#include <unity.h>
#include <stdint.h>
#include <util/delay.h>
#include "leds.h"
#include "timers.h"
#include "model.h"
#include <avr/io.h>

/**
 * setUp: Runs automatically BEFORE each test case.
 * Used to reset the hardware state to a known baseline.
 */
void setUp(void) {
    setup_ports();
}

/**
 * tearDown: Runs automatically AFTER each test case.
 * Empty here as no specific hardware cleanup is required.
 */
void tearDown(void) {
}

/**
 * TEST CASE: Validate message transmission
 * This test sends a 32-bit NEC message and displays it through a LED 
 */
void test_transmit_specific_nec_message(void) {
    uint32_t message = 0xFF00FF00;
    send_message(message);
    TEST_ASSERT_EQUAL_HEX32(0xFF00FF00, message);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) {
    _delay_ms(2000);
    UNITY_BEGIN();
    RUN_TEST(test_transmit_specific_nec_message);
    return UNITY_END();
}