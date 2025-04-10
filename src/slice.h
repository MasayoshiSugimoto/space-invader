#ifndef SLICE_H
#define SLICE_H

#include <stdint.h>
#include "log.h"
#include "main_system_mode.h"
#include "animation_step.h"
#include "vector.h"


struct SLICE__Uint8 {
    uint8_t* data;
    uint32_t length;
};


void SLICE__uint8_t_init(struct SLICE__Uint8* slice);
uint8_t SLICE__uint8_t_get(const struct SLICE__Uint8* slice, uint32_t index);


struct SLICE__Uint16 {
    uint16_t* data;
    uint32_t length;
};


void SLICE__uint16_t_init(struct SLICE__Uint16* slice);
uint16_t SLICE__uint16_t_get(const struct SLICE__Uint16* slice, uint32_t index);


struct SLICE__Uint32 {
    uint32_t* data;
    uint32_t length;
};


void SLICE__uint32_t_init(struct SLICE__Uint32* slice);
uint32_t SLICE__uint32_t_get(const struct SLICE__Uint32* slice, uint32_t index);


struct SLICE__MainSystemMode {
    struct MainSystemMode** data;
    uint32_t length;
};


void SLICE__main_system_mode_init(struct SLICE__MainSystemMode* slice);
struct MainSystemMode* SLICE__main_system_mode_get(const struct SLICE__MainSystemMode* slice, uint32_t index);


struct SLICE__AnimationStep {
    struct AnimationStep* data;
    uint32_t length;
};


void SLICE__animation_step_init(struct SLICE__AnimationStep* slice);
struct AnimationStep* SLICE__animation_step_get(const struct SLICE__AnimationStep* slice, uint32_t index);


struct SLICE__Vector {
    struct Vector* data;
    uint32_t length;
};


void SLICE__vector_init(struct SLICE__Vector* slice);
struct Vector* SLICE__vector_get(const struct SLICE__Vector* slice, uint32_t index);


#endif
