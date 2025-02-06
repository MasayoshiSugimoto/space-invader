#include "array.h"

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


void array_uint8_t_release(struct ArrayUint8* array) {
    if (array->data != NULL) {
        free(array->data);
    }
    array->length = 0;
    array->capacity = 0;
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


void array_uint16_t_release(struct ArrayUint16* array) {
    if (array->data != NULL) {
        free(array->data);
    }
    array->length = 0;
    array->capacity = 0;
}


void array_uint32_t_allocate(struct ArrayUint32* array, uint32_t capacity) {
    array->data = malloc(sizeof(uint32_t) * capacity);
    array->length = 0;
    array->capacity = capacity;
}


uint32_t array_uint32_t_get(const struct ArrayUint32* array, uint32_t index) {
    assert_f(index < array->length, "Index out of bound: capacity=%d, index=%d", array->length, index);
    return array->data[index];
}


void array_uint32_t_set(struct ArrayUint32* array, uint32_t index, uint32_t value) {
    assert_f(index < array->length, "Index out of bound: capacity=%d, index=%d", array->length, index);
    array->data[index] = value;
}


void array_uint32_t_add(struct ArrayUint32* array, uint32_t value) {
    assert_f(array->length <= array->capacity, "Array already full: capacity=%d, length=%d", array->capacity, array->length);
    array->data[array->length++] = value;
}


void array_uint32_t_release(struct ArrayUint32* array) {
    if (array->data != NULL) {
        free(array->data);
    }
    array->length = 0;
    array->capacity = 0;
}

