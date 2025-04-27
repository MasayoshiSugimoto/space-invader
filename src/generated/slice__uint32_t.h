#ifndef SLICE__UINT32_T__H
#define SLICE__UINT32_T__H


#include "../log.h"
#include <stdint.h>
#include <stdint.h>


struct SLICE__uint32_t {
    uint32_t* data;
    uint32_t length;
};


void SLICE__uint32_t__init(struct SLICE__uint32_t* slice);
uint32_t* SLICE__uint32_t__get(struct SLICE__uint32_t* slice, uint32_t index);


#endif
