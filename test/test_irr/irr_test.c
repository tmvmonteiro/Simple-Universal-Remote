#include <avr/io.h>
#include <util/delay.h>
#include <unity.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "interrupts.h"
#include "buttons.h"

/**
 * setUp: Runs automatically BEFORE each test case.
 * Used to reset the hardware state to a known baseline.
 */
void setUp(void) {
}

/**
 * tearDown: Runs automatically AFTER each test case.
 * Empty here as no specific hardware cleanup is required.
 */
void tearDown(void) {
}

/**
 * TEST CASE: Receives NEC Message
 * This test receives a NEC Message
 * and inserts the HIGH and LOW WAVES 
 * timestamps on an 66 size array
 * Checks if second timestamp is correct
 */
void test_irr_receiver(void) {
    setup_receiver();
    while(!irr_finished);
    bool lead_low = ((8550 < time_stamps[1])&&(9450 > time_stamps[1]));
    TEST_ASSERT_TRUE(lead_low);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) {
    _delay_ms(200);
    UNITY_BEGIN();
    RUN_TEST(test_irr_receiver);
    return UNITY_END();
}