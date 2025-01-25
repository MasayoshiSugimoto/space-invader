#ifndef VIRTUAL_WINDOW_2_H
#define VIRTUAL_WINDOW_2_H


#include <stdbool.h>
#include <stdint.h>
#include "sprite_buffer.h"
#include "rectangle.h"


struct VirtualWindow2 {
  int offset_x;
  int offset_y;
  bool has_border;
  bool is_transparent;
  struct SpriteBuffer* buffer;
  const struct VirtualWindow2* container;
  uint8_t z;
};


int virtual_window_top_get(const struct VirtualWindow2* window);
int virtual_window_right_get(const struct VirtualWindow2* window);
int virtual_window_bottom_get(const struct VirtualWindow2* window);
int virtual_window_left_get(const struct VirtualWindow2* window);
struct Rectangle virtual_window_as_rectangle(const struct VirtualWindow2* window);


#endif