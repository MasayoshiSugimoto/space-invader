#include "slice__animationstep.h"


void SLICE__AnimationStep__init(struct SLICE__AnimationStep* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct AnimationStep* SLICE__AnimationStep__get(struct SLICE__AnimationStep* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}
