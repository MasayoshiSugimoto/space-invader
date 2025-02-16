#ifndef STRING_H
#define STRING_H


#include <stdint.h>
#include <stddef.h>
#include "log.h"


struct String {
    const char* data;
    uint32_t length;
};


void string_init(struct String* string);
void string_setup(struct String* string, const char* data);
char string_get_char(const struct String* string, uint32_t index);


#endif