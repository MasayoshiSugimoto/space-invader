#include "color.h"


#define COLOR_START 8
#define COLOR_UNIT_MAX 1000


struct ColorPair {
  enum ColorPairId id;
  short foreground_color;
  short background_color;
};


const struct ColorPair palette[] = {
  {COLOR_PAIR_ID_DEFAULT, COLOR_WHITE, COLOR_BLACK},
  {COLOR_PAIR_ID_COLLISION_ON, COLOR_WHITE, COLOR_RED},
  {COLOR_PAIR_ID_MENU_SELECTION, COLOR_BLACK, COLOR_WHITE},
  {COLOR_PAIR_ID_MENU_SELECTION, COLOR_RED, COLOR_BLACK},
};


struct Color {
  short red;
  short green;
  short blue;
};


struct ColorManager {
  struct Color* colors;
} color_manager; 


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
