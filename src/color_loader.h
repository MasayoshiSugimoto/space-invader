#ifndef  COLOR_LOADER_H
#define  COLOR_LOADER_H


#include "consts.h"
#include "string.h"
#include "string_buffer.h"
#include "util.h"
#include "color.h"


void color_loader_load_color_palette(const char* color_palette_file_name);
void color_loader_color_pair_palette_load(const char* color_pair_palette_file_name);


#endif