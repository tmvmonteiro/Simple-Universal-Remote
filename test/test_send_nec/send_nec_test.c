#include <unity.h>
#include <stdint.h>
#include <util/delay.h>
#include "leds.h"
#include "timers.h"
#include "buttons.h"
#include "model.h"
#include <avr/io.h>

struct button* buttons[5];

/**
 * setUp: Runs automatically BEFORE each test case.
 * Used to reset the hardware state to a known baseline.
 */
void setUp(void) {
    setup_ports();
    setup_buttons(buttons);
}

/**
 * tearDown: Runs automatically AFTER each test case.
 * Empty here as no specific hardware cleanup is required.
 */
void tearDown(void) {
}

/**
 * TEST CASE: Send Power ON/OFF NEC message
 * This test sends a 32-bit NEC message,
 * displays it through a LED to turn on/off
 * a device (in this case, LG TV)
 */
void test_power_nec_message(void) {
    uint32_t message = buttons[0]->message;
    send_message(message);
    TEST_ASSERT_EQUAL_HEX32(buttons[0]->message, message);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) {
    _delay_ms(2000);
    UNITY_BEGIN();
    RUN_TEST(test_power_nec_message);
    return UNITY_END();
}