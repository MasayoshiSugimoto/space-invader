#ifndef VIRTUAL_SCREEN_H
#define VIRTUAL_SCREEN_H


#include <term.h>
#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include "terminal.h"
#include "color.h"
#include "log.h"
#include "virtual_pixel.h"


bool virtual_screen_is_inside(int x, int y);
void virtual_screen_init(void);
void virtual_screen_allocate(void);
void virtual_screen_release(void);
void virtual_screen_reset(void);
void virtual_screen_clear(void);
void virtual_screen_set_char(int x, int y, const chtype ch);
void virtual_screen_set_char_and_color(int x, int y, const chtype ch, ColorPairId color_pair_id);
void virtual_screen_set_string(int x, int y, const char* string);
void virtual_screen_render(void);
int virtual_screen_center_x(void);
int virtual_screen_center_y(void);
int virtual_screen_get_width(void);
int virtual_screen_get_height(void);


#endif
