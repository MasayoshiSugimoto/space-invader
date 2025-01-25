#include "virtual_window.h"


int virtual_window_top_get(const struct VirtualWindow* window) {
    return window->offset_y;
}


int virtual_window_right_get(const struct VirtualWindow* window) {
    return window->offset_x + window->buffer->width;
}


int virtual_window_bottom_get(const struct VirtualWindow* window) {
    return window->offset_y + window->buffer->height;
}


int virtual_window_left_get(const struct VirtualWindow* window) {
    return window->offset_x;
}


struct Rectangle virtual_window_as_rectangle(const struct VirtualWindow* window) {
    struct Rectangle rectangle = {
        .left = window->offset_x,
        .top = window->offset_y,
        .width = window->buffer->width,
        .height = window->buffer->height
    };
    return rectangle;
}