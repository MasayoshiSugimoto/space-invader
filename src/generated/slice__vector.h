#ifndef SLICE__VECTOR__H
#define SLICE__VECTOR__H


#include "../log.h"
#include <stdint.h>
#include "../vector.h"


struct SLICE__Vector {
    struct Vector* data;
    uint32_t length;
};


void SLICE__Vector__init(struct SLICE__Vector* slice);
struct Vector* SLICE__Vector__get(struct SLICE__Vector* slice, uint32_t index);


#endif
