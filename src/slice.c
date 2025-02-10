#include "slice.h"

void slice_uint8_t_init(struct SliceUint8* slice) {
    slice->data = NULL;
    slice->length = 0;
}


uint8_t slice_uint8_t_get(const struct SliceUint8* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


void slice_uint16_t_init(struct SliceUint16* slice) {
    slice->data = NULL;
    slice->length = 0;
}


uint16_t slice_uint16_t_get(const struct SliceUint16* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


void slice_uint32_t_init(struct SliceUint32* slice) {
    slice->data = NULL;
    slice->length = 0;
}


uint32_t slice_uint32_t_get(const struct SliceUint32* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


void slice_main_system_mode_init(struct SliceMainSystemMode* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct MainSystemMode* slice_main_system_mode_get(const struct SliceMainSystemMode* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


void slice_animation_step_init(struct SliceAnimationStep* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct AnimationStep* slice_animation_step_get(const struct SliceAnimationStep* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}

