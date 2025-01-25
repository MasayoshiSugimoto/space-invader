#ifndef ARRAY_VIRTUAL_WINDOW_H
#define ARRAY_VIRTUAL_WINDOW_H


#include <stdint.h>
#include <stdlib.h>
#include "log.h"
#include "virtual_window_2.h"


struct ArrayVirtualWindow {
    struct VirtualWindow2* windows;
    uint16_t length;
};


void array_virtual_window_allocate(struct ArrayVirtualWindow* ptr, uint16_t length);
void array_virtual_window_free(struct ArrayVirtualWindow* ptr);


#endif