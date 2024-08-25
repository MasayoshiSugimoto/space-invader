#include "post_effect.h"


struct FadeOut {
  struct Timer timer;
  struct Color palette[COLOR_CUSTOM_COLOR_MAX];
} g_fade_out;


void fade_start(Duration duration) {
  timer_init(&g_fade_out.timer, duration);
}


void fade_out_render(struct VirtualScreen* virtual_screen) {
  struct Timer* timer = &g_fade_out.timer;
  timer_update_once(timer, timer_get_frame_duration());

  float alpha = 1;
  if (timer->current > 0) {
    alpha = timer_interpolate_linear(timer, 1.0f, 0.0f);
  }
  struct Color* palette = g_fade_out.palette;
  for (unsigned int id = 0; id < color_palette_length_deprecated(); id++) {
    const struct Color* color = color_palette_get_deprecated(id);
    struct Color* color2 = &palette[id];
    color2->red = alpha * color->red;
    color2->green = alpha * color->green;
    color2->blue = alpha * color->blue;
  }
  color_palette_set_deprecated(palette);

  for (int x = 0; x < virtual_screen->width; x++) {
    for (int y = 0; y < virtual_screen->height; y++) {
      short color_pair = COLOR_PAIR(2);
      attron(color_pair);
      mvaddch(y, x, virtual_screen->screen[y * virtual_screen->width + x]);
      attroff(color_pair);
    }
  }
}


void fade_in_render(struct VirtualScreen* virtual_screen) {
  struct Timer* timer = &g_fade_out.timer;
  timer_update_once(timer, timer_get_frame_duration());

  float alpha = 0.0f;
  if (timer->current > 0) {
    alpha = timer_interpolate_linear(timer, 0.0f, 1.0f);
  }
  struct Color* palette = g_fade_out.palette;
  for (unsigned int id = 0; id < color_palette_length_deprecated(); id++) {
    const struct Color* color = color_palette_get_deprecated(id);
    struct Color* color2 = &palette[id];
    color2->red = alpha * color->red;
    color2->green = alpha * color->green;
    color2->blue = alpha * color->blue;
  }
  color_palette_set_deprecated(palette);

  for (int x = 0; x < virtual_screen->width; x++) {
    for (int y = 0; y < virtual_screen->height; y++) {
      short color_pair = COLOR_PAIR(1);
      attron(color_pair);
      mvaddch(y, x, virtual_screen->screen[y * virtual_screen->width + x]);
      attroff(color_pair);
    }
  }
}


bool fade_is_done() {
  return timer_is_done(&g_fade_out.timer);
}


void fade_stop() {
  color_palette_init();
}
