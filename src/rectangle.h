#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <stdint.h>
#include "vector.h"


struct Rectangle {
    uint16_t top;
    uint16_t left;
    uint16_t width;
    uint16_t height;
};


uint16_t rectangle_top_get(const struct Rectangle* r);
uint16_t rectangle_right_get(const struct Rectangle* r);
uint16_t rectangle_bottom_get(const struct Rectangle* r);
uint16_t rectangle_left_get(const struct Rectangle* r);


#endif