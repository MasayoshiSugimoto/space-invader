#ifndef SLICE__UINT8_T__H
#define SLICE__UINT8_T__H


#include "../log.h"
#include <stdint.h>
#include <stdint.h>


struct SLICE__uint8_t {
    uint8_t* data;
    uint32_t length;
};


void SLICE__uint8_t__init(struct SLICE__uint8_t* slice);
uint8_t* SLICE__uint8_t__get(struct SLICE__uint8_t* slice, uint32_t index);


#endif
