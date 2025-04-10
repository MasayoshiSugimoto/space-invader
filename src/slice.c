#include "slice.h"

void SLICE__uint8_t_init(struct SLICE__Uint8* slice) {
    slice->data = NULL;
    slice->length = 0;
}


uint8_t SLICE__uint8_t_get(const struct SLICE__Uint8* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


void SLICE__uint16_t_init(struct SLICE__Uint16* slice) {
    slice->data = NULL;
    slice->length = 0;
}


uint16_t SLICE__uint16_t_get(const struct SLICE__Uint16* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


void SLICE__uint32_t_init(struct SLICE__Uint32* slice) {
    slice->data = NULL;
    slice->length = 0;
}


uint32_t SLICE__uint32_t_get(const struct SLICE__Uint32* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


void SLICE__main_system_mode_init(struct SLICE__MainSystemMode* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct MainSystemMode* SLICE__main_system_mode_get(const struct SLICE__MainSystemMode* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return slice->data[index];
}


void SLICE__animation_step_init(struct SLICE__AnimationStep* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct AnimationStep* SLICE__animation_step_get(const struct SLICE__AnimationStep* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}


void SLICE__vector_init(struct SLICE__Vector* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct Vector* SLICE__vector_get(const struct SLICE__Vector* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}

