#include <unity.h>
#include <stdint.h>
#include <util/delay.h>
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
 * TEST CASE: Setup default button settings
 * This test will create the default button structure settings
 */
void test_setup_buttons(void) {
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_NOT_NULL(buttons[i]);
    }

    TEST_ASSERT_EQUAL_PTR(&PINC, buttons[0]->input_address);
    TEST_ASSERT_EQUAL_PTR(&PINC, buttons[1]->input_address);
    TEST_ASSERT_EQUAL_PTR(&PINC, buttons[2]->input_address);
    TEST_ASSERT_EQUAL_PTR(&PINC, buttons[3]->input_address);
    TEST_ASSERT_EQUAL_PTR(&PINC, buttons[4]->input_address);

    TEST_ASSERT_EQUAL_UINT8(PINC0, buttons[0]->pin);
    TEST_ASSERT_EQUAL_UINT8(PINC1, buttons[1]->pin);
    TEST_ASSERT_EQUAL_UINT8(PINC2, buttons[2]->pin);
    TEST_ASSERT_EQUAL_UINT8(PINC3, buttons[3]->pin);
    TEST_ASSERT_EQUAL_UINT8(PINC4, buttons[4]->pin);

    TEST_ASSERT_EQUAL_UINT32(0xF708FB04, buttons[0]->message);
    TEST_ASSERT_EQUAL_UINT32(0xFD02FB04, buttons[1]->message);
    TEST_ASSERT_EQUAL_UINT32(0xFC03FB04, buttons[2]->message);
    TEST_ASSERT_EQUAL_UINT32(0xFF00FB04, buttons[3]->message);
    TEST_ASSERT_EQUAL_UINT32(0xFE01FB04, buttons[4]->message);
}

/**
 * TEST CASE: validate_message_transmission
 * This test changes a button structure message to another one
 */
void test_change_message(void){
    TEST_ASSERT_NOT_NULL(buttons[0]);
    TEST_ASSERT_EQUAL_PTR(&PINC, buttons[0]->input_address);
    TEST_ASSERT_EQUAL_UINT8(PINC0, buttons[0]->pin);
    TEST_ASSERT_EQUAL_UINT32(0xF708FB04, buttons[0]->message);
    
    uint32_t new_msg = 0xABCDE123;
    change_message(buttons[0], new_msg);

    TEST_ASSERT_NOT_NULL(buttons[0]);
    TEST_ASSERT_EQUAL_PTR(&PINC, buttons[0]->input_address);
    TEST_ASSERT_EQUAL_UINT8(PINC0, buttons[0]->pin);
    TEST_ASSERT_EQUAL_UINT32(0xABCDE123, buttons[0]->message);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) {
    _delay_ms(2000);
    UNITY_BEGIN();
    RUN_TEST(test_setup_buttons);
    _delay_ms(200);
    RUN_TEST(test_change_message);
    return UNITY_END();
}