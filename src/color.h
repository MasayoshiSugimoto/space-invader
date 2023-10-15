#ifndef COLOR_H
#define COLOR_H


#include <curses.h>
#include <ncurses.h>
#include "log.h"
#include "util.h"


enum ColorPairId {
  COLOR_PAIR_ID_DEFAULT,
  COLOR_PAIR_ID_COLLISION_ON,
  COLOR_PAIR_ID_MENU_SELECTION,
  COLOR_PAIR_ID_MENU_TITLE,
  COLOR_PAIR_ID_MAX
};


void color_init();


#endif

