#include "post_effect.h"


#define FADE_OUT_TIME_MS 2000


struct FadeOut {
  struct Timer timer;
} g_fade_out;


void fade_out_init() {
  timer_init(&g_fade_out.timer, FADE_OUT_TIME_MS);
}


void fade_out_update(struct VirtualScreen* virtual_screen) {

//  log_info_f("d: %ld", timer_get_frame_duration());
//  log_info_f("now: %ld", timer_get_frame_start());
  timer_update_once(&g_fade_out.timer, timer_get_frame_duration());
  timer_print(&g_fade_out.timer);

  float alpha = 1;
  if (g_fade_out.timer.current > 0) {
    alpha = 1.0f - (1.0f * g_fade_out.timer.current / g_fade_out.timer.max);
  }
  log_info_f("alpha: %f", alpha);
  struct Color* palette = malloc(sizeof(struct Color) * color_palette_length());
  for (unsigned int id = 0; id < color_palette_length(); id++) {
    const struct Color* color = color_palette_get(id);
    color_set_red(&palette[id], alpha * color->red);
    color_set_green(&palette[id], alpha * color->green);
    color_set_blue(&palette[id], alpha * color->blue);
    color_print(&palette[id]);
  }
  color_palette_set(palette);

  //float alpha = 0;
  for (int x = 0; x < virtual_screen->width; x++) {
    for (int y = 0; y < virtual_screen->height; y++) {
      attron(COLOR_PAIR(color_pair_id(1, 0)));
      mvaddch(y, x, virtual_screen->screen[y * virtual_screen->width + x]);
      attroff(COLOR_PAIR(color_pair_id(1, 0)));
    }
  }

  free(palette);
}
