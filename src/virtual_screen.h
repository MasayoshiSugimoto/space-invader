#ifndef VIRTUAL_SCREEN_H
#define VIRTUAL_SCREEN_H


#include <term.h>
#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include "terminal.h"
#include "sprite.h"
#include "color.h"
#include "log.h"
#include "window_manager.h"


struct VirtualScreen {
  struct VirtualPixel* screen;
  int width;
  int height;
} g_virtual_screen;


void virtual_screen_init();
void virtual_screen_setup();
void virtual_screen_reset();
void virtual_screen_set_char(int x, int y, const chtype ch);
void virtual_screen_set_char_and_color(int x, int y, const chtype ch, ColorPairId color_pair_id);
void virtual_screen_set_string(int x, int y, const char* string);
void virtual_screen_render();
int virtual_screen_center_x();
int virtual_screen_center_y();
int virtual_screen_get_width();
int virtual_screen_get_height();


#endif
