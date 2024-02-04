#include "start_screen.h"


struct VirtualWindow g_window;


void start_screen_init() {
  virtual_window_init(&g_window);
  virtual_window_setup_from_sprite(&g_window, sprite_get_sprite(SPRITE_ID_TITLE));
  virtual_window_center(&g_window);
}


enum TaskStatus start_screen_render() {
  if (fade_out_is_done()) {
    fade_out_stop();
    return TASK_STATUS_DONE;
  }
  virtual_screen_reset();
  virtual_window_draw(&g_window);
  fade_out_render(&g_virtual_screen);
  return TASK_STATUS_RUNNING;
}
