#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H


#include "window_manager_2.h"
#include "sprite_component.h"


void game_screen_init(int width, int height);
void game_screen_release(void);
const struct VirtualWindow2* game_screen_get(void);
void game_screen_render(void);


#endif
