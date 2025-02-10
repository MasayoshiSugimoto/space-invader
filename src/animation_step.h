#ifndef ANIMATION_STEP_H
#define ANIMATION_STEP_H


#include "timer.h"
#include "sprite_buffer.h"


struct AnimationStep {
    struct SpriteBuffer* sprite_buffer;
    Duration duration;
};


#endif