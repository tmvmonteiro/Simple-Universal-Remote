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
 * timestamps on an 66 size array.
 * Then it passes the array into a function
 * that translates the HIGH IR waves into
 * a 32 bits message (1690us -> 1; 560us ->0).
 * Finally, the message goes through a message
 * that returns true if it follows the 
 * NEC protocol.
 */
void test_irr_receiver(void) {
    setup_receiver();
    while(!irr_finished);
    uint32_t message;
    timestamp_to_message(&message);
    bool is_follows_nec = check_message(message);
    TEST_ASSERT_EQUAL_HEX32(0xF708FB04, message);
    TEST_ASSERT_TRUE(is_follows_nec);
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