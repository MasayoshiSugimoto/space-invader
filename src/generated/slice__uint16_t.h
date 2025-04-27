#ifndef SLICE__UINT16_T__H
#define SLICE__UINT16_T__H


#include "../log.h"
#include <stdint.h>
#include <stdint.h>


struct SLICE__uint16_t {
    uint16_t* data;
    uint32_t length;
};


void SLICE__uint16_t__init(struct SLICE__uint16_t* slice);
uint16_t* SLICE__uint16_t__get(struct SLICE__uint16_t* slice, uint32_t index);


#endif
