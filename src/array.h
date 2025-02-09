#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include "log.h"
#include "main_system_mode.h"

struct ArrayUint8 {
    uint8_t* data;
    uint32_t length;
    uint32_t capacity;
};


void array_uint8_t_allocate(struct ArrayUint8* array, uint32_t capacity);
uint8_t array_uint8_t_get(const struct ArrayUint8* array, uint32_t index);
void array_uint8_t_set(struct ArrayUint8* array, uint32_t index, uint8_t value);
void array_uint8_t_add(struct ArrayUint8* array, uint8_t value);
void array_uint8_t_release(struct ArrayUint8* array);


struct ArrayUint16 {
    uint16_t* data;
    uint32_t length;
    uint32_t capacity;
};


void array_uint16_t_allocate(struct ArrayUint16* array, uint32_t capacity);
uint16_t array_uint16_t_get(const struct ArrayUint16* array, uint32_t index);
void array_uint16_t_set(struct ArrayUint16* array, uint32_t index, uint16_t value);
void array_uint16_t_add(struct ArrayUint16* array, uint16_t value);
void array_uint16_t_release(struct ArrayUint16* array);


struct ArrayUint32 {
    uint32_t* data;
    uint32_t length;
    uint32_t capacity;
};


void array_uint32_t_allocate(struct ArrayUint32* array, uint32_t capacity);
uint32_t array_uint32_t_get(const struct ArrayUint32* array, uint32_t index);
void array_uint32_t_set(struct ArrayUint32* array, uint32_t index, uint32_t value);
void array_uint32_t_add(struct ArrayUint32* array, uint32_t value);
void array_uint32_t_release(struct ArrayUint32* array);


#endif
