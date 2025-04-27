#ifndef SLICE__ANIMATIONSTEP__H
#define SLICE__ANIMATIONSTEP__H


#include "../log.h"
#include <stdint.h>
#include "../animation_step.h"


struct SLICE__AnimationStep {
    struct AnimationStep* data;
    uint32_t length;
};


void SLICE__AnimationStep__init(struct SLICE__AnimationStep* slice);
struct AnimationStep* SLICE__AnimationStep__get(struct SLICE__AnimationStep* slice, uint32_t index);


#endif
