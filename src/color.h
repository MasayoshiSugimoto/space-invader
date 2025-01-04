#ifndef COLOR_H
#define COLOR_H


#include <curses.h>
#include <ncurses.h>
#include "log.h"
#include "util.h"
#include "frame_timer.h"


#define COLOR_COLOR_MAX 256
#define COLOR_COLOR_PAIR_MAX 256
#define COLOR_COLOR_PAIR_ID_DEFAULT 8


typedef short ColorId;
typedef short ColorPairId;


enum ColorPairId {
  COLOR_PAIR_ID_DEFAULT,
  COLOR_PAIR_ID_COLLISION_ON,
  COLOR_PAIR_ID_MENU_SELECTION,
  COLOR_PAIR_ID_MENU_TITLE,
  COLOR_PAIR_ID_MAX
};


enum ColorPaletteId {
  COLOR_PALETTE_ID_DEFAULT,
  COLOR_PALETTE_ID_POST_RENDERING,
  COLOR_PALETTE_ID_TODO_1,  // Used in the tests. Not used for now otherwise.
  COLOR_PALETTE_ID_TODO_2,  // Used in the tests. Not used for now otherwise.
  COLOR_PALETTE_ID_MAX
};


struct Color {
  short red;
  short green;
  short blue;
};


struct ColorPair {
  ColorId background_color_id;
  ColorId foreground_color_id;
};


void color_color_set_default(void);
void color_color_palette_push(enum ColorPaletteId color_palette_id);
enum ColorPaletteId color_color_palette_get_last_pushed();
void color_color_palette_activate(enum ColorPaletteId color_palette_id);
enum ColorPaletteId color_color_palette_get_activated();
ColorId color_color_palette_add(struct Color color);
void color_color_set(ColorId colorId, struct Color color);
struct Color color_color_get(ColorId color_id);
struct ColorPair color_color_pair_get(ColorPairId color_pair_id);
void color_color_pair_set(ColorPairId color_pair_id, ColorId background_color_id, ColorId foreground_color_id);
ColorPairId color_color_pair_add(ColorId background_color_id, ColorId foreground_color_id);
void color_color_pair_push();
void color_fade_start_fade_out(Duration duration);
void color_fade_start_fade_in(Duration duration);
void color_fade_end();
bool color_fade_is_done();
void color_update();


void color_init();
void color_reset();
void color_print(const struct Color* color);


#endif

