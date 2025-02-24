#ifndef SPACE_H
#define SPACE_H


#include <stdint.h>
#include "slice.h"
#include "virtual_screen.h"
#include "recuring_frame_timer.h"


void space_init(void);
void space_allocate(void);
void space_release(void);
void space_setup(void);
void space_update(void);
void space_draw(void);


#endif