#include "slice__mainsystemmode.h"


void SLICE__MainSystemMode__init(struct SLICE__MainSystemMode* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct MainSystemMode* SLICE__MainSystemMode__get(struct SLICE__MainSystemMode* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}
