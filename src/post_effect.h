#ifndef POST_EFFECT_H
#define POST_EFFECT_H


#include "virtual_screen.h"
#include "timer.h"
#include "color.h"


void fade_out_start();
void fade_out_render(struct VirtualScreen* virtual_screen);
bool fade_out_is_done();
void fade_out_stop();


#endif
