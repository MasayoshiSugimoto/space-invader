#ifndef ARRAY_BIT_H
#define ARRAY_BIT_H


#include <stdint.h>
#include <stdbool.h>
#include "log.h"


typedef uint64_t ArrayBit;


void array_bit_reset(ArrayBit* bits);
void array_bit_enable(ArrayBit* bits, uint16_t flag);
void array_bit_disable(ArrayBit* bits, uint16_t flag);
bool array_bit_is_enabled(ArrayBit* bits, uint16_t flag);


#endif