#ifndef POST_EFFECT_H
#define POST_EFFECT_H


#include "virtual_screen.h"
#include "timer.h"
#include "color.h"


void fade_start(Duration duration);
void fade_out_render(struct VirtualScreen* virtual_screen);
void fade_in_render(struct VirtualScreen* virtual_screen);
bool fade_is_done();
void fade_stop();


#endif
