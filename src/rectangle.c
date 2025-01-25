#include "rectangle.h"


uint16_t rectangle_top_get(const struct Rectangle* r) {
    return r->top;
}


uint16_t rectangle_right_get(const struct Rectangle* r) {
    return r->left + r->width;
}


uint16_t rectangle_bottom_get(const struct Rectangle* r) {
    return r->top + r->height;
}


uint16_t rectangle_left_get(const struct Rectangle* r) {
    return r->left;
}