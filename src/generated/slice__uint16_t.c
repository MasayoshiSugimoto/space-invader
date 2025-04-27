#include "slice__uint16_t.h"


void SLICE__uint16_t__init(struct SLICE__uint16_t* slice) {
    slice->data = NULL;
    slice->length = 0;
}


uint16_t* SLICE__uint16_t__get(struct SLICE__uint16_t* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}
