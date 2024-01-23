#include "color.h"


#define COLOR_START 8
#define COLOR_UNIT_MAX 1000
#define COLOR_ANSI_COLOR_COUNT 8

enum PaletteColor {
  PALETTE_COLOR_BLACK,
  PALETTE_COLOR_WHITE,
  PALETTE_COLOR_MAX
};


struct ColorPair {
  enum ColorPairId id;
  short foreground_color;
  short background_color;
};


struct Color g_colors[COLOR_CUSTOM_COLOR_MAX] = {
  {0, 0, 0},
  {1000, 1000, 1000},
};
const struct Color* g_custom_colors = NULL;


const struct ColorPair palette[] = {
  {COLOR_PAIR_ID_DEFAULT, COLOR_WHITE, COLOR_BLACK},
  {COLOR_PAIR_ID_COLLISION_ON, COLOR_WHITE, COLOR_RED},
  {COLOR_PAIR_ID_MENU_SELECTION, COLOR_BLACK, COLOR_WHITE},
  {COLOR_PAIR_ID_MENU_SELECTION, COLOR_RED, COLOR_BLACK},
};


struct ColorManager {
  struct Color* colors;
} color_manager; 


short as_ncurse_color_id(short color_id) {
  return color_id + COLOR_ANSI_COLOR_COUNT;
}


void color_init() {
  if (!has_colors() || !can_change_color()) {
    endwin();
    log_fatal("Your terminal does not support color\n");
  }

  start_color();

  log_info_f("Maximum number of colors: %d", COLORS);
  log_info_f("Maximum number of pairs: %d", COLOR_PAIRS);

  log_info("Default Colors:");
  log_info_f("Black=%d", COLOR_BLACK);
  log_info_f("Red=%d", COLOR_RED);
  log_info_f("Green=%d", COLOR_GREEN);
  log_info_f("Yellow=%d", COLOR_YELLOW);
  log_info_f("Blue=%d", COLOR_BLUE);
  log_info_f("Magenta=%d", COLOR_MAGENTA);
  log_info_f("Cyan=%d", COLOR_CYAN);
  log_info_f("White=%d", COLOR_WHITE);

  for (int color_id = 0; color_id < array_size(palette); color_id++) {
    const struct ColorPair* color_pair = &palette[color_id];
    init_pair(color_id, color_pair->foreground_color, color_pair->background_color);
  }
}


void color_set_red(struct Color* color, short red) {
  if (red < 0) {
    red = 0;
  }
  if (red > 1000) {
    red = 1000;
  }
  color->red = red;
}


void color_set_green(struct Color* color, short green) {
  if (green < 0) {
    green = 0;
  }
  if (green > 1000) {
    green = 1000;
  }
  color->green = green;
}


void color_set_blue(struct Color* color, short blue) {
  if (blue < 0) {
    blue = 0;
  }
  if (blue > 1000) {
    blue = 1000;
  }
  color->blue = blue;
}


void color_palette_init() {
  for (int i = 0; i < PALETTE_COLOR_MAX; i++) {
    int id = as_ncurse_color_id(i);
    const struct Color* color = &g_colors[i];
    init_color(id, color->red, color->green, color->blue);
    log_info_f("init_color(%d, %d, %d, %d)", id, color->red, color->green, color->blue);
  }

  for (int i = 0; i < PALETTE_COLOR_MAX; i++) {
    for (int j = 0; j < PALETTE_COLOR_MAX; j++) {
      init_pair(color_pair_id(i, j), as_ncurse_color_id(i), as_ncurse_color_id(j));
      log_info_f("init_pair(%d, %d, %d)", color_pair_id(i, j), as_ncurse_color_id(i), as_ncurse_color_id(j));
    }
  }
}


const struct Color* color_palette_get(unsigned short id) {
  if (id > PALETTE_COLOR_MAX) return NULL;
  return &g_colors[id];
}


size_t color_palette_length() {
  return PALETTE_COLOR_MAX;
}


void color_palette_set(const struct Color* palette) {
  g_custom_colors = palette;
  for (int i = 0; i < PALETTE_COLOR_MAX; i++) {
    int id = as_ncurse_color_id(i);
    const struct Color* color = &g_custom_colors[i];
    init_color(id, color->red, color->green, color->blue);
    log_info_f("init_color(%d, %d, %d, %d)", id, color->red, color->green, color->blue);
  }
}


void color_print(const struct Color* color) {
  log_info_f("red: %d, green: %d, blue: %d", color->red, color->green, color->blue);
}


short color_pair_id(short foreground, short background) {
  return foreground * PALETTE_COLOR_MAX + background;
}
