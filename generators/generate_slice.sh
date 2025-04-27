#!/bin/bash


readonly TYPE_META_DATAS=(
    'uint8_t' '<stdint.h>'
    'uint16_t' '<stdint.h>'
    'uint32_t' '<stdint.h>'
    'struct BulletComponent' '"../bullet_component_struct.h"'
    'struct MainSystemMode*' '"../main_system_mode.h"'
    'struct Vector' '"../vector.h"'
    'struct AnimationStep' '"../animation_step.h"'
)
readonly TYPE_SIZE=2
readonly TYPE_COUNT=$((${#TYPE_META_DATAS[@]}/TYPE_SIZE))
readonly OUTPUT_DIR='src/generated'


function fatal {
    echo "[FATAL]$1" >&2
    exit 1
}


function space_to_underscore {
    tr ' ' '_'
}


function remove_struct {
    sed -E 's/^struct //'
}


function convert_ptr {
    sed -E 's/\*/_ptr/'
}


function type_to_header_file {
    local type_name="$1"
    local file_name="slice__$(echo "$type_name" | remove_struct | space_to_underscore | convert_ptr).h"
    file_name="${file_name,,}"
    echo "$file_name"
}


function type_to_c_file {
    local type_name="$1"
    local file_name="slice__$(echo "$type_name" | remove_struct | space_to_underscore | convert_ptr).c"
    file_name="${file_name,,}"
    echo "$file_name"
}


function as_slice_type {
    local type_name="$1"
    echo "SLICE__$(echo "$type_name" | remove_struct | convert_ptr)"
}


function generate_slice_h {
    local type_name="$1"
    local include="$2"
    local type_in_define="$(as_slice_type "$type_name")"
    type_in_define="${type_in_define^^}"
    local slice_type="$(as_slice_type "$type_name")"
    cat << EOF
#ifndef ${type_in_define}__H
#define ${type_in_define}__H


#include "../log.h"
#include <stdint.h>
#include $include


struct ${slice_type} {
    ${type_name}* data;
    uint32_t length;
};


void ${slice_type}__init(struct ${slice_type}* slice);
${type_name}* ${slice_type}__get(struct ${slice_type}* slice, uint32_t index);


#endif
EOF
}


function generate_slice_c {
    local type_name="$1"
    local include="$2"
    local slice_type="$(as_slice_type "$type_name")"
    local header_file="$(type_to_header_file "$type_name")"
    cat << EOF
#include "${header_file,,}"


void ${slice_type}__init(struct ${slice_type}* slice) {
    slice->data = NULL;
    slice->length = 0;
}


${type_name}* ${slice_type}__get(struct ${slice_type}* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return &slice->data[index];
}
EOF
}


function generate_slices_h {
    for x in $(seq $TYPE_COUNT); do
        local offset=$(((x-1)*TYPE_SIZE))
        local type_name="${TYPE_META_DATAS[$((offset))]}"
        generate_slice_h \
            "${TYPE_META_DATAS[$((offset))]}" \
            "${TYPE_META_DATAS[$((offset+1))]}" \
            > "$OUTPUT_DIR/$(type_to_header_file "$type_name")"
        continue
    done
}


function generate_slices_c {
    for x in $(seq $TYPE_COUNT); do
        local offset=$(((x-1)*TYPE_SIZE))
        local type_name="${TYPE_META_DATAS[$((offset))]}"
        generate_slice_c \
            "${TYPE_META_DATAS[$((offset))]}" \
            "${TYPE_META_DATAS[$((offset+1))]}" \
            > "$OUTPUT_DIR/$(type_to_c_file "$type_name")"
    done
}


generate_slices_h
generate_slices_c
