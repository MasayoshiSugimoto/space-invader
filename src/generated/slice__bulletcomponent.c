#include "slice__bulletcomponent.h"


void SLICE__BulletComponent__init(struct SLICE__BulletComponent* slice) {
    slice->data = NULL;
    slice->length = 0;
}


struct BulletComponent* SLICE__BulletComponent__get(struct SLICE__BulletComponent* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}
