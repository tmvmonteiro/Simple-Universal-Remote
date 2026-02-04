#include <avr/io.h>
#include <util/delay.h>
#include <unity.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "interrupts.h"
#include "nec.h"

/**
 * setUp: Runs automatically BEFORE each test case.
 * Used to reset the hardware state to a known baseline.
 */
void setUp(void) {
    //init_debug_uart();
}

/**
 * tearDown: Runs automatically AFTER each test case.
 * Empty here as no specific hardware cleanup is required.
 */
void tearDown(void) {
}

void test_nec_receiver_receiver(void){
    uint32_t message1;
    bool message_correct1 = receive_message(&message1);
    TEST_ASSERT_EQUAL_HEX32(0xF708FB04, message1);
    uint32_t message2;
    _delay_ms(500);
    bool message_correct2 = receive_message(&message2);
    TEST_ASSERT_EQUAL_HEX32(0xF708FB04, message2);
}

/**
 * TEST CASE: Receive NEC Message
 * This test receives a NEC Message 
 * (Power ON/OFF) from a device (LG TV remote)
 */
void test_nec_receiver(void){
    uint32_t message;
    receive_message(&message);
    TEST_ASSERT_EQUAL_HEX32(0xF708FB04, message);
}

/**
 * TEST CASE: Send NEC Message
 * This test sends a NEC Message 
 * (Power ON/OFF) to a device (LG TV)
 */
void test_nec_sender(void){
    uint32_t message = 0xF708FB04;
    send_message(message);
    TEST_ASSERT_EQUAL_HEX32(0xF708FB04, message);
}

/**
 * main: Entry point for the test runner on the microcontroller.
 */
int main(void) {
    _delay_ms(200);
    UNITY_BEGIN();
    RUN_TEST(test_nec_receiver_receiver);
    _delay_ms(200);
    RUN_TEST(test_nec_sender);
    _delay_ms(200);
    RUN_TEST(test_nec_receiver);
    return UNITY_END();
}