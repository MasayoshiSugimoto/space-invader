#ifndef VIRTUAL_PIXEL_H
#define VIRTUAL_PIXEL_H


#include "color.h"


struct VirtualPixel {
  chtype character;
  ColorPairId color_pair_id;
};


#endif