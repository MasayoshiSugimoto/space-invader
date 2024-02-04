#include "start_screen.h"


#define FADE_OUT_TIME_MS 1000l
#define DISPLAY_TITLE_TIME_MS 2000l


enum State {
  STATE_FADE_IN,
  STATE_DISPLAY_TITLE,
  STATE_FADE_OUT,
} g_state;


struct VirtualWindow g_window;
struct Timer g_timer;


void start_screen_init() {
  virtual_window_init(&g_window);
  virtual_window_setup_from_sprite(&g_window, sprite_get_sprite(SPRITE_ID_TITLE));
  virtual_window_center(&g_window);
  fade_start(milliseconds_as_duration(FADE_OUT_TIME_MS));
  g_state = STATE_FADE_IN;
  timer_init(&g_timer, 0);
}


enum TaskStatus start_screen_render() {
  virtual_screen_reset();
  virtual_window_center(&g_window);
  virtual_window_draw(&g_window);
  switch (g_state) {
    case STATE_FADE_IN:
      if (fade_is_done()) {
        fade_stop();
        g_state = STATE_DISPLAY_TITLE;
        timer_init(&g_timer, milliseconds_as_duration(DISPLAY_TITLE_TIME_MS));
      } else {
        fade_in_render(&g_virtual_screen);
      }
      break;
    case STATE_DISPLAY_TITLE:
      virtual_screen_render();
      timer_update_once(&g_timer, timer_get_frame_duration());
      if (timer_is_done(&g_timer)) {
        g_state = STATE_FADE_OUT;
        fade_start(milliseconds_as_duration(FADE_OUT_TIME_MS));
      }
      break;
    case STATE_FADE_OUT:
      if (fade_is_done()) {
          fade_stop();
          return TASK_STATUS_DONE;
      } else {
        fade_out_render(&g_virtual_screen);
      }
      break;
  }
  return TASK_STATUS_RUNNING;
}
