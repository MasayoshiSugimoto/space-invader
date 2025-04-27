#include "slice__uint8_t.h"


void SLICE__uint8_t__init(struct SLICE__uint8_t* slice) {
    slice->data = NULL;
    slice->length = 0;
}


uint8_t* SLICE__uint8_t__get(struct SLICE__uint8_t* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}
