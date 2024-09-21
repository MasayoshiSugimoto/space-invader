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


struct VirtualPixel {
  chtype character;
  ColorPairId color_pair_id;
};


struct VirtualScreen {
  struct VirtualPixel* screen;
  int width;
  int height;
} g_virtual_screen;


struct VirtualWindow {
  struct VirtualPixel* pixels;
  int width;
  int height;
  int offset_x;
  int offset_y;
  bool has_border;
};


void virtual_window_init(struct VirtualWindow* window);
void virtual_window_setup(struct VirtualWindow* window, int width, int height, int offset_x, int offset_y);
void virtual_window_setup_from_sprite(struct VirtualWindow* window, const struct Sprite* sprite);
void virtual_window_delete(struct VirtualWindow* window);
void virtual_window_set_string(struct VirtualWindow* window, const char* string, int x, int y);
void virtual_window_draw(const struct VirtualWindow* window);
int virtual_window_center_x(const struct VirtualWindow* window, const char* string);
int virtual_window_center_y(const struct VirtualWindow* window);
void virtual_window_center(struct VirtualWindow* window);
void virtual_window_clear(struct VirtualWindow* window, chtype clear_character);
void virtual_window_set(struct VirtualWindow* window, int x, int y, chtype character);

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
