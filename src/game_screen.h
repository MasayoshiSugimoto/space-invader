#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H


#include "window_manager.h"
#include "sprite_component.h"
#include "rectangle.h"


void game_screen_init(int width, int height);
void game_screen_release(void);
void game_screen_clear(void);
const struct VirtualWindow* game_screen_get(void);
void game_screen_render(void);
struct Rectangle game_screen_rectangle_get(void);


#endif
