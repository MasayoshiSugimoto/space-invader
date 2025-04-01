#include "color.h"


#define COLOR_START 8
#define COLOR_UNIT_MAX 1000
#define COLOR_ANSI_COLOR_COUNT 8
#define COLOR_PAIR_FIRST_ID COLOR_COLOR_PAIR_ID_DEFAULT


static const struct Color BLACK = {0, 0, 0};
static const struct Color WHITE = {255, 255, 255};
static const struct Color RED = {255, 0, 0};
static const struct Color MAGENTA = {255, 0, 255};
static const ColorId COLOR_FIRST_COLOR_ID = 8;


struct Fade {
  struct FrameTimer timer;
  float alpha_start;
  float alpha_end;
} _fade;


struct Color _color_palette[COLOR_PALETTE_ID_MAX][COLOR_COLOR_MAX];
size_t _color_palette_sizes[COLOR_PALETTE_ID_MAX];
struct ColorPair _color_pair_palette[COLOR_COLOR_PAIR_MAX];
size_t _color_pair_palette_size;
ColorId _color_active;
enum ColorPaletteId _palette_last_pushed_id;
enum ColorPaletteId _palette_active_id;


struct ColorManager {
  struct Color* colors;
} color_manager; 


short as_ncurse_color_id(short color_id) {
  return color_id + COLOR_ANSI_COLOR_COUNT;
}


short _as_ncurse_intensity(short intensity) {
  return (int)intensity * 1000 / 255;
}


bool _color_id_is_valid(ColorId color_id) {
  return 0 <= color_id && color_id < COLOR_COLOR_MAX;
}


bool _color_pair_id_is_valid(ColorPairId color_pair_id) {
  return 0 <= color_pair_id && color_pair_id < COLOR_COLOR_PAIR_MAX;
}


bool _color_palette_id_is_valid(enum ColorPaletteId color_palette_id) {
  return 0 <= color_palette_id && color_palette_id < COLOR_PALETTE_ID_MAX;
}


void _fade_init() {
  frame_timer_init();
  frame_timer_stop(&_fade.timer);  // Start timer in disabled state.
  _fade.alpha_start = 0.0f;
  _fade.alpha_end = 0.0f;
}


void _fade_update() {
  if (frame_timer_is_done(&_fade.timer)) {
    return;
  }
  struct FrameTimer* timer = &_fade.timer;
  float alpha = frame_timer_interpolate_cos_f(timer, _fade.alpha_start, _fade.alpha_end);
  struct Color* active_color_palette_id = _color_palette[_palette_active_id];
  struct Color* post_rendering_palette_id = _color_palette[COLOR_PALETTE_ID_POST_RENDERING];
  for (ColorId color_id = COLOR_FIRST_COLOR_ID; color_id < COLOR_COLOR_MAX; color_id++) {
    post_rendering_palette_id[color_id].red = alpha * active_color_palette_id[color_id].red;
    post_rendering_palette_id[color_id].green = alpha * active_color_palette_id[color_id].green;
    post_rendering_palette_id[color_id].blue = alpha * active_color_palette_id[color_id].blue;
  }
  color_color_palette_push(COLOR_PALETTE_ID_POST_RENDERING);
}


void color_color_set_default(void) {
  log_info("Setting default colors.");
  color_reset();
  enum ColorPaletteId color_palette_id = 0;
  color_color_palette_activate(color_palette_id);
  ColorId black_id = color_color_palette_add(BLACK);
  ColorId white_id = color_color_palette_add(WHITE);
  ColorId red_id = color_color_palette_add(RED);
  ColorId magenta_id = color_color_palette_add(MAGENTA);
  color_color_pair_add(black_id, white_id);
  color_color_pair_add(black_id, red_id);
  color_color_pair_add(black_id, magenta_id);
  color_color_palette_push(color_palette_id);
  color_color_pair_push();
}


void color_color_palette_push(enum ColorPaletteId color_palette_id) {
  assert_f(_color_palette_id_is_valid(color_palette_id), "Invalid color_palette_id: %d", color_palette_id);
  log_info_f("Pushing color palette: color_palette_id=%d", color_palette_id);
  for (ColorId color_id = COLOR_FIRST_COLOR_ID; color_id < COLOR_COLOR_MAX; color_id++) {
    struct Color color = _color_palette[color_palette_id][color_id];
    init_color(color_id, _as_ncurse_intensity(color.red), _as_ncurse_intensity(color.green), _as_ncurse_intensity(color.blue));
  }
}


enum ColorPaletteId color_color_palette_get_last_pushed() {
  return _palette_last_pushed_id;
}


void color_color_palette_activate(enum ColorPaletteId color_palette_id) {
  log_info_f("Activating color palette: %d", color_palette_id);
  assert_f(_color_palette_id_is_valid(color_palette_id), "Invalid color_palette_id: %d", color_palette_id);
  _palette_active_id = color_palette_id;
}


enum ColorPaletteId color_color_palette_get_activated() {
  return _palette_active_id;
}


ColorId color_color_palette_add(struct Color color) {
  ColorId color_id = _color_palette_sizes[_palette_active_id]++;
  _color_palette[_palette_active_id][color_id] = color;
  return color_id;
}


void color_color_set(ColorId color_id, struct Color color) {
  assert_f(_color_id_is_valid(color_id), "Invalid color_id: %d", color_id);
  _color_palette[_palette_active_id][color_id] = color;
}


struct Color color_color_get(ColorId color_id) {
  assert_f(_color_id_is_valid(color_id), "Invalid color_id: %d", color_id);
  return _color_palette[_palette_active_id][color_id];
}


struct ColorPair color_color_pair_get(ColorPairId color_pair_id) {
  assert_f(_color_pair_id_is_valid(color_pair_id), "Invalid color_pair_id: %d", color_pair_id);
  return _color_pair_palette[color_pair_id];
}


void color_color_pair_set(ColorPairId color_pair_id, ColorId background_color_id, ColorId foreground_color_id) {
  assert_f(_color_pair_id_is_valid(color_pair_id), "Invalid color_pair_id: %d", color_pair_id);
  assert_f(_color_id_is_valid(background_color_id), "Invalid background_color_id: %d", background_color_id);
  assert_f(_color_id_is_valid(foreground_color_id), "Invalid foreground_color_id: %d", foreground_color_id);
  _color_pair_palette[color_pair_id].background_color_id = background_color_id;
  _color_pair_palette[color_pair_id].foreground_color_id = foreground_color_id;
}


ColorPairId color_color_pair_add(ColorId background_color_id, ColorId foreground_color_id) {
  ColorPairId color_pair_id = _color_pair_palette_size++;
  color_color_pair_set(color_pair_id, background_color_id, foreground_color_id);
  return color_pair_id;
}


void color_color_pair_push() {
  for (ColorPairId color_pair_id = COLOR_PAIR_FIRST_ID; color_pair_id < COLOR_COLOR_PAIR_MAX; color_pair_id++) {
    struct ColorPair color_pair = color_color_pair_get(color_pair_id);
    init_pair(color_pair_id, color_pair.foreground_color_id, color_pair.background_color_id);
  }
}


void color_fade_start_fade_out(Duration duration) {
  log_info_f("Color fade out start: duration=%ld", duration);
  frame_timer_start(&_fade.timer, duration);
  _fade.alpha_start = 1.0f;
  _fade.alpha_end = 0.0f;
}


void color_fade_start_fade_in(Duration duration) {
  log_info_f("Color fade in start: duration=%ld", duration);
  frame_timer_start(&_fade.timer, duration);
  _fade.alpha_start = 0.0f;
  _fade.alpha_end = 1.0f;
}


void color_fade_end() {
  frame_timer_stop(&_fade.timer);
}


bool color_fade_is_done() {
  return frame_timer_is_done(&_fade.timer);
}


void color_update() {
  _fade_update();
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

  color_reset();
}


void color_reset() {
  log_info("Resetting colors.");
  memset(&_color_palette, 0, sizeof(_color_palette));
  memset(&_color_palette_sizes, 0, sizeof(_color_palette_sizes));
  for (size_t i = 0; i < COLOR_PALETTE_ID_MAX; i++) {
    _color_palette_sizes[i] = COLOR_FIRST_COLOR_ID;
  }
  memset(&_color_pair_palette, 0, sizeof(_color_pair_palette));
  _color_pair_palette_size = COLOR_PAIR_FIRST_ID;
  _color_active = 0;
  _palette_last_pushed_id = 0;
  _palette_active_id = 0;
  _fade_init();
}


void color_set_mapping(short id, const struct Color* color) {
  init_color(as_ncurse_color_id(id), color->red, color->green, color->blue);
}


void color_set_pair_mapping(short id, short foreground, short background) {
  init_pair(id, as_ncurse_color_id(foreground), as_ncurse_color_id(background));
}


void color_print(const struct Color* color) {
  log_info_f("red: %d, green: %d, blue: %d", color->red, color->green, color->blue);
}