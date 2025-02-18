#ifndef  COLOR_LOADER_H
#define  COLOR_LOADER_H


#include "consts.h"
#include "string.h"
#include "string_buffer.h"
#include "util.h"
#include "color.h"


#define COLOR_LOADER_COLOR_PALETTE_FILE_NAME_DEFAULT "color_palette_default.dat"
#define COLOR_LOADER_COLOR_PAIR_PALETTE_FILE_NAME_DEFAULT "color_pair_palette_default.dat"


void color_loader_load_color_palette(const char* color_palette_file_name);
void color_loader_color_pair_palette_load(const char* color_pair_palette_file_name);


#endif