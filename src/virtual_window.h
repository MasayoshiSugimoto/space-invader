#ifndef VIRTUAL_WINDOW_H
#define VIRTUAL_WINDOW_H


#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <curses.h>
#include "color.h"
#include "sprite.h"


struct VirtualPixel {
  chtype character;
  ColorPairId color_pair_id;
};


struct VirtualWindow {
  struct VirtualPixel* pixels;
  int width;
  int height;
  int offset_x;
  int offset_y;
  bool has_border;
  bool is_transparent;
};


void virtual_window_init(struct VirtualWindow* window);
void virtual_window_setup(struct VirtualWindow* window, int width, int height, int offset_x, int offset_y);
void virtual_window_setup_from_sprite(struct VirtualWindow* window, const struct Sprite* sprite);
void virtual_window_delete(struct VirtualWindow* window);
void virtual_window_set_string(struct VirtualWindow* window, const char* string, int x, int y);
int virtual_window_center_x(const struct VirtualWindow* window, const char* string);
int virtual_window_center_y(const struct VirtualWindow* window);
void virtual_window_clear(struct VirtualWindow* window, chtype clear_character);
void virtual_window_set(struct VirtualWindow* window, int x, int y, chtype character);
void virtual_window_set_transparency(struct VirtualWindow* window, bool is_transparent);
bool virtual_window_get_transparency(struct VirtualWindow* window);


#endif