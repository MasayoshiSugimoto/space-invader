#ifndef COLOR_H
#define COLOR_H


#include <curses.h>
#include <ncurses.h>
#include "log.h"
#include "util.h"


#define COLOR_CUSTOM_COLOR_MAX 2


enum ColorPairId {
  COLOR_PAIR_ID_DEFAULT,
  COLOR_PAIR_ID_COLLISION_ON,
  COLOR_PAIR_ID_MENU_SELECTION,
  COLOR_PAIR_ID_MENU_TITLE,
  COLOR_PAIR_ID_MAX
};


struct Color {
  short red;
  short green;
  short blue;
};


void color_init();

void color_palette_init();
void color_set_red(struct Color* color, short red);
void color_set_green(struct Color* color, short green);
void color_set_blue(struct Color* color, short blue);
const struct Color* color_palette_get(unsigned short id);
size_t color_palette_length();
void color_palette_set(const struct Color* palette);
void color_print(const struct Color* color);
short color_pair_id(short foreground, short background);

#endif

