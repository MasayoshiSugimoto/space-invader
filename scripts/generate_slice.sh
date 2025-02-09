#!/bin/bash


readonly POINTER_ENABLED='POINTER_ENABLED'
readonly POINTER_DISABLED='POINTER_DISABLED'
readonly TYPE_META_DATAS=(
    'Uint8' 'uint8_t' 'uint8_t' $POINTER_DISABLED
    'Uint16' 'uint16_t' 'uint16_t' $POINTER_DISABLED
    'Uint32' 'uint32_t' 'uint32_t' $POINTER_DISABLED
    'MainSystemMode' 'struct MainSystemMode*' 'main_system_mode' $POINTER_DISABLED
)
readonly TYPE_COUNT=$((${#TYPE_META_DATAS[@]}/4))


function generate_slice_h {
    local structure_suffix="$1"
    local type_name="$2"
    local function_suffix="$3"
    local is_pointer_enabled="$4"
    local slice_struct="struct Slice${structure_suffix}"
    local pointer_mark=$([[ $is_pointer_enabled == $POINTER_ENABLED ]] && echo '*')
    cat << EOF
${slice_struct} {
    ${type_name}* data;
    uint32_t length;
};


${type_name}${pointer_mark} slice_${function_suffix}_get(const ${slice_struct}* slice, uint32_t index);


EOF
}


function generate_slice_c {
    local structure_suffix="$1"
    local type_name="$2"
    local function_suffix="$3"
    local is_pointer_enabled="$4"
    local slice_struct="struct Slice${structure_suffix}"
    local pointer_mark=$([[ $is_pointer_enabled == $POINTER_ENABLED ]] && echo '*')
    cat << EOF
${type_name}${pointer_mark} slice_${function_suffix}_get(const ${slice_struct}* slice, uint32_t index) {
    assert_f(index < slice->length, "Index out of bound: length=%d, index=%d", slice->length, index);
    return $(
        if [[ $is_pointer_enabled == $POINTER_ENABLED ]]; then
            echo '&slice->data[index];'
        else
            echo 'slice->data[index];'
        fi
        
    )
}


EOF
}


function generate_slices_h {
    cat << EOF
#ifndef SLICE_H
#define SLICE_H

#include <stdint.h>
#include "log.h"
#include "main_system_mode.h"

$(
    for x in $(seq $TYPE_COUNT); do
        x=$((x-1))
        generate_slice_h \
            "${TYPE_META_DATAS[$((x*4))]}" \
            "${TYPE_META_DATAS[$(((x*4)+1))]}" \
            "${TYPE_META_DATAS[$(((x*4)+2))]}" \
            "${TYPE_META_DATAS[$(((x*4)+3))]}"
    done
)


#endif
EOF
}


function generate_slices_c {
    cat << EOF
#include "slice.h"

$(
    for x in $(seq $TYPE_COUNT); do
        x=$((x-1))
        generate_slice_c \
            "${TYPE_META_DATAS[$((x*4))]}" \
            "${TYPE_META_DATAS[$(((x*4)+1))]}" \
            "${TYPE_META_DATAS[$(((x*4)+2))]}" \
            "${TYPE_META_DATAS[$(((x*4)+3))]}"
    done
)

EOF
}

if [[ $1 == 'h' ]]; then
    generate_slices_h
elif [[ $1 == 'c' ]]; then
    generate_slices_c
else
    echo "Only 'h' or 'c' are acceptable parameters." >&2
fi


