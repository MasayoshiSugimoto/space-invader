#include "slice.h"

uint8_t slice_uint8_t_get(const struct SliceUint8* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


uint16_t slice_uint16_t_get(const struct SliceUint16* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


uint32_t slice_uint32_t_get(const struct SliceUint32* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


struct MainSystemMode* slice_main_system_mode_get(const struct SliceMainSystemMode* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}

