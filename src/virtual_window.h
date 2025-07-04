#ifndef VIRTUAL_WINDOW_H
#define VIRTUAL_WINDOW_H


#include <stdbool.h>
#include <stdint.h>
#include "sprite_buffer.h"
#include "rectangle.h"


struct VirtualWindow {
  int offset_x;
  int offset_y;
  bool has_border;
  bool is_transparent;
  struct SpriteBuffer* buffer;
  const struct VirtualWindow* container;
  uint8_t z;
};


int virtual_window_top_get(const struct VirtualWindow* window);
int virtual_window_right_get(const struct VirtualWindow* window);
int virtual_window_bottom_get(const struct VirtualWindow* window);
int virtual_window_left_get(const struct VirtualWindow* window);
struct Rectangle virtual_window_as_rectangle(const struct VirtualWindow* window);


#endif