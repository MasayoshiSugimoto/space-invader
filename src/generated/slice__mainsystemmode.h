#ifndef SLICE__MAINSYSTEMMODE__H
#define SLICE__MAINSYSTEMMODE__H


#include "../log.h"
#include <stdint.h>
#include "../main_system_mode.h"


struct SLICE__MainSystemMode {
    struct MainSystemMode* data;
    uint32_t length;
};


void SLICE__MainSystemMode__init(struct SLICE__MainSystemMode* slice);
struct MainSystemMode* SLICE__MainSystemMode__get(struct SLICE__MainSystemMode* slice, uint32_t index);


#endif
