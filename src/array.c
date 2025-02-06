#include "array.h"

struct ArrayUint8 {
    uint8_t* data;
    uint32_t length;
    uint32_t capacity;
};


void array_uint8_t_init(struct ArrayUint8* array, uint32_t capacity) {
    array->data = NULL;
    array->length = 0;
    array->capacity = capacity;
}


void array_uint8_t_allocate(struct ArrayUint8* array, uint32_t capacity) {
    array->data = malloc(sizeof(uint8_t) * capacity);
    array->length = 0;
    array->capacity = capacity;
}


uint8_t array_uint8_t_get(const struct ArrayUint8* array, uint32_t index) {
    assert_f(index < array->capacity, "Index out of bound: capacity=%d, index=%d", array->capacity, index);
    return array->data[index];
}


void array_uint8_t_set(struct ArrayUint8* array, uint32_t index, uint8_t value) {
    assert_f(index < array->capacity, "Index out of bound: capacity=%d, index=%d", array->capacity, index);
    array->data[index] = value;
}


void array_uint8_t_add(struct ArrayUint8* array, uint8_t value) {
    assert_f(array->length <= array->capacity, "Array already full: capacity=%d, length=%d", array->capacity, array->length);
    array->data[array->length++] = value;
}


struct ArrayUint16 {
    uint16_t* data;
    uint32_t length;
    uint32_t capacity;
};


void array_uint16_t_init(struct ArrayUint16* array, uint32_t capacity) {
    array->data = NULL;
    array->length = 0;
    array->capacity = capacity;
}


void array_uint16_t_allocate(struct ArrayUint16* array, uint32_t capacity) {
    array->data = malloc(sizeof(uint16_t) * capacity);
    array->length = 0;
    array->capacity = capacity;
}


uint16_t array_uint16_t_get(const struct ArrayUint16* array, uint32_t index) {
    assert_f(index < array->capacity, "Index out of bound: capacity=%d, index=%d", array->capacity, index);
    return array->data[index];
}


void array_uint16_t_set(struct ArrayUint16* array, uint32_t index, uint16_t value) {
    assert_f(index < array->capacity, "Index out of bound: capacity=%d, index=%d", array->capacity, index);
    array->data[index] = value;
}


void array_uint16_t_add(struct ArrayUint16* array, uint16_t value) {
    assert_f(array->length <= array->capacity, "Array already full: capacity=%d, length=%d", array->capacity, array->length);
    array->data[array->length++] = value;
}


struct ArrayUint32 {
    uint32_t* data;
    uint32_t length;
    uint32_t capacity;
};


void array_uint32_t_init(struct ArrayUint32* array, uint32_t capacity) {
    array->data = NULL;
    array->length = 0;
    array->capacity = capacity;
}


void array_uint32_t_allocate(struct ArrayUint32* array, uint32_t capacity) {
    array->data = malloc(sizeof(uint32_t) * capacity);
    array->length = 0;
    array->capacity = capacity;
}


uint32_t array_uint32_t_get(const struct ArrayUint32* array, uint32_t index) {
    assert_f(index < array->capacity, "Index out of bound: capacity=%d, index=%d", array->capacity, index);
    return array->data[index];
}


void array_uint32_t_set(struct ArrayUint32* array, uint32_t index, uint32_t value) {
    assert_f(index < array->capacity, "Index out of bound: capacity=%d, index=%d", array->capacity, index);
    array->data[index] = value;
}


void array_uint32_t_add(struct ArrayUint32* array, uint32_t value) {
    assert_f(array->length <= array->capacity, "Array already full: capacity=%d, length=%d", array->capacity, array->length);
    array->data[array->length++] = value;
}

