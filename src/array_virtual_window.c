#include "array_virtual_window.h"


void array_virtual_window_allocate(struct ArrayVirtualWindow* ptr, uint16_t length) {
    ptr->windows = malloc(sizeof(*ptr->windows) * length);
    ptr->length = length;
}


void array_virtual_window_free(struct ArrayVirtualWindow* ptr) {
    assert(ptr->windows != NULL, "ArrayVirtualWindowPtr is null");
    free(ptr->windows);
}


