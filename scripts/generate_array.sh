#!/bin/bash

function generate_array {
    local structure_suffix=$1
    local type_name=$2
    local function_suffix=$3
    cat << EOF
struct Array${structure_suffix} {
    ${type_name}* data;
    uint32_t length;
    uint32_t capacity;
};


void array_${function_suffix}_init(struct Array${structure_suffix}* array, uint32_t capacity) {
    array->data = NULL;
    array->length = 0;
    array->capacity = capacity;
}


void array_${function_suffix}_allocate(struct Array${structure_suffix}* array, uint32_t capacity) {
    array->data = malloc(sizeof(${type_name}) * capacity);
    array->length = 0;
    array->capacity = capacity;
}


${type_name} array_${function_suffix}_get(struct Array${structure_suffix}* array, uint32_t index) {
    assert_f(index < array->capacity, "Index out of bound: capacity=%d, index=%d", array->capacity, index);
    return array->data[index];
}


void array_${function_suffix}_set(struct Array${structure_suffix}* array, uint32_t index, ${type_name} value) {
    assert_f(index < array->capacity, "Index out of bound: capacity=%d, index=%d", array->capacity, index);
    array->data[index] = value;
}


void array_${function_suffix}_add(struct Array${structure_suffix}* array, ${type_name} value) {
    assert_f(array->length <= array->capacity, "Array already full: capacity=%d, length=%d", array->capacity, array->length);
    array->data[array->length++] = value;
}
EOF
}


function generate_arrays {
    cat << EOF
#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include "log.h"


$(generate_array Uint8 uint8_t uint8_t)


#endif
EOF
}

generate_arrays

