#!/bin/bash


readonly TYPE_META_DATAS=(
    'Uint8' 'uint8_t' 'uint8_t'
    'Uint16' 'uint16_t' 'uint16_t'
    'Uint32' 'uint32_t' 'uint32_t'
)
readonly TYPE_COUNT=$((${#TYPE_META_DATAS[@]}/3))


function generate_array_h {
    local structure_suffix=$1
    local type_name=$2
    local function_suffix=$3
    cat << EOF
struct Array${structure_suffix} {
    ${type_name}* data;
    uint32_t length;
    uint32_t capacity;
};


void array_${function_suffix}_allocate(struct Array${structure_suffix}* array, uint32_t capacity);
${type_name} array_${function_suffix}_get(const struct Array${structure_suffix}* array, uint32_t index);
void array_${function_suffix}_set(struct Array${structure_suffix}* array, uint32_t index, ${type_name} value);
void array_${function_suffix}_add(struct Array${structure_suffix}* array, ${type_name} value);
void array_${function_suffix}_release(struct Array${structure_suffix}* array);


EOF
}


function generate_array_c {
    local structure_suffix=$1
    local type_name=$2
    local function_suffix=$3
    cat << EOF
void array_${function_suffix}_allocate(struct Array${structure_suffix}* array, uint32_t capacity) {
    array->data = malloc(sizeof(${type_name}) * capacity);
    array->length = 0;
    array->capacity = capacity;
}


${type_name} array_${function_suffix}_get(const struct Array${structure_suffix}* array, uint32_t index) {
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


void array_${function_suffix}_release(struct Array${structure_suffix}* array) {
    if (array->data != NULL) {
        free(array->data);
    }
    array->length = 0;
    array->capacity = 0;
}


EOF
}


function generate_arrays_h {
    cat << EOF
#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include "log.h"

$(
    for x in $(seq $TYPE_COUNT); do
        x=$((x-1))
        generate_array_h ${TYPE_META_DATAS[$((x*3))]} ${TYPE_META_DATAS[$(((x*3)+1))]} ${TYPE_META_DATAS[$(((x*3)+2))]}
    done
)


#endif
EOF
}


function generate_arrays_c {
    cat << EOF
#include "array.h"

$(
    for x in $(seq $TYPE_COUNT); do
        x=$((x-1))
        generate_array_c ${TYPE_META_DATAS[$((x*3))]} ${TYPE_META_DATAS[$(((x*3)+1))]} ${TYPE_META_DATAS[$(((x*3)+2))]}
    done
)

EOF
}

if [[ $1 == 'h' ]]; then
    generate_arrays_h
elif [[ $1 == 'c' ]]; then
    generate_arrays_c
else
    echo "Only 'h' or 'c' are acceptable parameters." >&2
fi


