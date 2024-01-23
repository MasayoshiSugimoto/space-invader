#include "post_effect.h"


#define FADE_OUT_TIME_MS 2000


struct FadeOut {
  struct Timer timer;
  struct Color palette[COLOR_CUSTOM_COLOR_MAX];
} g_fade_out;


void fade_out_start() {
  timer_init(&g_fade_out.timer, FADE_OUT_TIME_MS);
}


void fade_out_render(struct VirtualScreen* virtual_screen) {
  struct Timer* timer = &g_fade_out.timer;
  timer_update_once(timer, timer_get_frame_duration());

  float alpha = 1;
  if (timer->current > 0) {
    alpha = timer_interpolate_linear(timer, 1.0f, 0.0f);
  }
  struct Color* palette = g_fade_out.palette;
  for (unsigned int id = 0; id < color_palette_length(); id++) {
    const struct Color* color = color_palette_get(id);
    color_set_red(&palette[id], alpha * color->red);
    color_set_green(&palette[id], alpha * color->green);
    color_set_blue(&palette[id], alpha * color->blue);
  }
  color_palette_set(palette);

  for (int x = 0; x < virtual_screen->width; x++) {
    for (int y = 0; y < virtual_screen->height; y++) {
      attron(COLOR_PAIR(color_pair_id(1, 0)));
      mvaddch(y, x, virtual_screen->screen[y * virtual_screen->width + x]);
      attroff(COLOR_PAIR(color_pair_id(1, 0)));
    }
  }
}


bool fade_out_is_done() {
  return timer_is_done(&g_fade_out.timer);
}


void fade_out_stop() {
  color_palette_init();
}
