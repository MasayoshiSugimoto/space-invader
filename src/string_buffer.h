#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H


#include <stdint.h>
#include <stddef.h>
#include "log.h"


#define ARRAY_AS_STRING_BUFFER(array) { \
    .data = array, \
    .length = 0, \
    .capacity = array_size(array), \
};


struct StringBuffer {
    char* data;
    uint32_t length;
    uint32_t capacity;
};


void string_buffer_init(struct StringBuffer* string_buffer);
void string_buffer_add(struct StringBuffer* string_buffer, char c);
void string_buffer_string_add(struct StringBuffer* string_buffer, const char* string);
char string_buffer_get(struct StringBuffer* string_buffer, uint32_t index);
char* string_buffer_access(struct StringBuffer* string_buffer, uint32_t index);
void string_buffer_terminate(struct StringBuffer* string_buffer);


#endif