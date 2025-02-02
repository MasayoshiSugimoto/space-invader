#include "array_bit.h"


void array_bit_reset(ArrayBit* bits) {
    *bits = 0;
}


void array_bit_enable(ArrayBit* bits, uint16_t flag) {
    assert_f(flag < 64, "Invalid flag: %d", flag);
    *bits |= ((uint64_t)1 << flag);
}


void array_bit_disable(ArrayBit* bits, uint16_t flag) {
    assert_f(flag < 64, "Invalid flag: %d", flag);
    *bits &= ~((uint64_t)1 << flag);
}


bool array_bit_is_enabled(ArrayBit* bits, uint16_t flag) {
    assert_f(flag < 64, "Invalid flag: %d", flag);
    return  *bits & ((uint64_t)1 << flag);
}