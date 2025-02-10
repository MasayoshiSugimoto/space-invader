#ifndef SLICE_H
#define SLICE_H

#include <stdint.h>
#include "log.h"
#include "main_system_mode.h"
#include "animation_step.h"


struct SliceUint8 {
    uint8_t* data;
    uint32_t length;
};


void slice_uint8_t_init(struct SliceUint8* slice);
uint8_t slice_uint8_t_get(const struct SliceUint8* slice, uint32_t index);


struct SliceUint16 {
    uint16_t* data;
    uint32_t length;
};


void slice_uint16_t_init(struct SliceUint16* slice);
uint16_t slice_uint16_t_get(const struct SliceUint16* slice, uint32_t index);


struct SliceUint32 {
    uint32_t* data;
    uint32_t length;
};


void slice_uint32_t_init(struct SliceUint32* slice);
uint32_t slice_uint32_t_get(const struct SliceUint32* slice, uint32_t index);


struct SliceMainSystemMode {
    struct MainSystemMode** data;
    uint32_t length;
};


void slice_main_system_mode_init(struct SliceMainSystemMode* slice);
struct MainSystemMode* slice_main_system_mode_get(const struct SliceMainSystemMode* slice, uint32_t index);


struct SliceAnimationStep {
    struct AnimationStep* data;
    uint32_t length;
};


void slice_animation_step_init(struct SliceAnimationStep* slice);
struct AnimationStep* slice_animation_step_get(const struct SliceAnimationStep* slice, uint32_t index);


#endif
