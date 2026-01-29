#include <stdint.h>
#include <stdbool.h>
#include "view.h"

void blink(volatile uint8_t* data_register, uint8_t output){
    if (data_register != 0) *data_register = output;
}