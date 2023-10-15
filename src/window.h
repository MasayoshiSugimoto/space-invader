#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H


#include <curses.h>
#include <ncurses.h>
#include <string.h>
#include "color.h"


struct Window {
  int top;
  int left;
  int width;
  int height;
};


void window_move(struct Window* window, int y, int x);
void window_addch(struct Window* window, const chtype character);
void window_render_center_string(struct Window* window, int y, const char* string);
void window_render_center_string_selection(struct Window* window, int y, const char* string);
void window_render_border(struct Window* window);


#endif
