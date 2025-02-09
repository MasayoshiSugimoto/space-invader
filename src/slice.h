#ifndef SLICE_H
#define SLICE_H

#include <stdint.h>
#include "log.h"
#include "main_system_mode.h"

struct SliceUint8 {
    uint8_t* data;
    uint32_t length;
};


uint8_t slice_uint8_t_get(const struct SliceUint8* slice, uint32_t index);


struct SliceUint16 {
    uint16_t* data;
    uint32_t length;
};


uint16_t slice_uint16_t_get(const struct SliceUint16* slice, uint32_t index);


struct SliceUint32 {
    uint32_t* data;
    uint32_t length;
};


uint32_t slice_uint32_t_get(const struct SliceUint32* slice, uint32_t index);


struct SliceMainSystemMode {
    struct MainSystemMode** data;
    uint32_t length;
};


struct MainSystemMode* slice_main_system_mode_get(const struct SliceMainSystemMode* slice, uint32_t index);


#endif
