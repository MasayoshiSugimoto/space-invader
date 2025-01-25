#ifndef VIRTUAL_WINDOW_2_H
#define VIRTUAL_WINDOW_2_H


#include <stdbool.h>
#include <stdint.h>


struct VirtualWindow2 {
  int offset_x;
  int offset_y;
  bool has_border;
  bool is_transparent;
  struct SpriteBuffer* buffer;
  const struct VirtualWindow2* container;
  uint8_t z;
};


#endif