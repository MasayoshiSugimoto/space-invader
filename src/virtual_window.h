#ifndef VIRTUAL_WINDOW_H
#define VIRTUAL_WINDOW_H


#include <stdbool.h>


struct VirtualWindow {
  int width;
  int height;
  int offset_x;
  int offset_y;
  bool has_border;
  bool is_transparent;
};


#endif