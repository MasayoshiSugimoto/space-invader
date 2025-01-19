#ifndef ARRAY_INT_H
#define ARRAY_INT_H


#include <stdint.h>


struct ArrayInt32 {
    int32_t* data;
    int32_t length;
    int32_t capacity;
};


void array_int_init(struct ArrayInt32* array, int32_t capacity);
void array_int_get(struct ArrayInt32* array, int32_t index);
void array_int_set(struct ArrayInt32* array, int32_t index);
void array_int_add(struct ArrayInt32* array, int32_t index);


#endif