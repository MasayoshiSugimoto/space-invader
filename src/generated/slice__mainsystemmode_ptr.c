#include "slice__mainsystemmode_ptr.h"


void SLICE__MainSystemMode_ptr__init(struct SLICE__MainSystemMode_ptr* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct MainSystemMode** SLICE__MainSystemMode_ptr__get(struct SLICE__MainSystemMode_ptr* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}
