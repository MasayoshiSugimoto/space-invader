#include "slice__vector.h"


void SLICE__Vector__init(struct SLICE__Vector* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct Vector* SLICE__Vector__get(struct SLICE__Vector* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}
