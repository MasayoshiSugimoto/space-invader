#ifndef SLICE__MAINSYSTEMMODE_PTR__H
#define SLICE__MAINSYSTEMMODE_PTR__H


#include "../log.h"
#include <stdint.h>
#include "../main_system_mode.h"


struct SLICE__MainSystemMode_ptr {
    struct MainSystemMode** data;
    uint32_t length;
};


void SLICE__MainSystemMode_ptr__init(struct SLICE__MainSystemMode_ptr* slice);
struct MainSystemMode** SLICE__MainSystemMode_ptr__get(struct SLICE__MainSystemMode_ptr* slice, uint32_t index);


#endif
