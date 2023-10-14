#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H


#include <curses.h>
#include <ncurses.h>


struct Window {
  int top;
  int left;
  int width;
  int height;
};


void window_move(struct Window* window, int y, int x);
void window_addch(struct Window* window, const chtype character);
void window_render_border(struct Window* window);


#endif
