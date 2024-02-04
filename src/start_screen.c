#include "start_screen.h"


#define FADE_OUT_TIME_MS 1000l
#define DISPLAY_TITLE_TIME_MS 2000l


enum State {
  STATE_TITLE_FADE_IN,
  STATE_TITLE_DISPLAY,
  STATE_TITLE_FADE_OUT,
  STATE_CREDITS_FADE_IN,
  STATE_CREDITS_DISPLAY,
  STATE_CREDITS_FADE_OUT,
} g_state;


struct VirtualWindow g_window;
struct Timer g_timer;


void start_screen_title_init_fade_in() {
  g_state = STATE_TITLE_FADE_IN;
  fade_start(milliseconds_as_duration(FADE_OUT_TIME_MS));
}


void start_screen_init() {
  virtual_window_init(&g_window);
  virtual_window_setup_from_sprite(&g_window, sprite_get_sprite(SPRITE_ID_TITLE));
  virtual_window_center(&g_window);
  timer_init(&g_timer, 0);
  start_screen_title_init_fade_in();
}


enum TaskStatus start_screen_fade_in_update() {
  fade_in_render(&g_virtual_screen);
  if (fade_is_done()) {
    fade_stop();
    return TASK_STATUS_DONE;
  }
  return TASK_STATUS_RUNNING;
}


void start_screen_title_display_init() {
  g_state = STATE_TITLE_DISPLAY;
  timer_init(&g_timer, milliseconds_as_duration(DISPLAY_TITLE_TIME_MS));
}


enum TaskStatus start_screen_display_update() {
  virtual_screen_render();
  timer_update_once(&g_timer, timer_get_frame_duration());
  if (timer_is_done(&g_timer)) {
    return TASK_STATUS_DONE;
  } else {
    return TASK_STATUS_RUNNING;
  }
}


void start_screen_title_init_fade_out() {
  g_state = STATE_TITLE_FADE_OUT;
  fade_start(milliseconds_as_duration(FADE_OUT_TIME_MS));
}


enum TaskStatus start_screen_fade_out_update() {
  if (fade_is_done()) {
    fade_stop();
    return TASK_STATUS_DONE;
  } else {
    fade_out_render(&g_virtual_screen);
  }
  return TASK_STATUS_RUNNING;
}


void start_screen_credits_init_fade_in() {
  g_state = STATE_CREDITS_FADE_IN;
  fade_start(milliseconds_as_duration(FADE_OUT_TIME_MS));
  virtual_window_setup_from_sprite(&g_window, sprite_get_sprite(SPRITE_ID_CREDITS));
}


void start_screen_credits_display_init() {
  g_state = STATE_CREDITS_DISPLAY;
  timer_init(&g_timer, milliseconds_as_duration(DISPLAY_TITLE_TIME_MS));
}


void start_screen_credits_init_fade_out() {
  g_state = STATE_CREDITS_FADE_OUT;
  fade_start(milliseconds_as_duration(FADE_OUT_TIME_MS));
}


enum TaskStatus start_screen_render() {
  virtual_screen_reset();
  virtual_window_center(&g_window);
  virtual_window_draw(&g_window);
  switch (g_state) {
    case STATE_TITLE_FADE_IN:
      if (start_screen_fade_in_update() == TASK_STATUS_DONE) {
        start_screen_title_display_init();
      }
      break;
    case STATE_TITLE_DISPLAY:
      if (start_screen_display_update() == TASK_STATUS_DONE) {
        start_screen_title_init_fade_out();
      }
      break;
    case STATE_TITLE_FADE_OUT:
      if (start_screen_fade_out_update() == TASK_STATUS_DONE) {
        start_screen_credits_init_fade_in();
      }
      break;
    case STATE_CREDITS_FADE_IN:
      if (start_screen_fade_in_update() == TASK_STATUS_DONE) {
        start_screen_credits_display_init();
      }
      break;
    case STATE_CREDITS_DISPLAY:
      if (start_screen_display_update() == TASK_STATUS_DONE) {
        start_screen_credits_init_fade_out();
      }
      break;
    case STATE_CREDITS_FADE_OUT:
      if (start_screen_fade_out_update() == TASK_STATUS_DONE) {
        return TASK_STATUS_DONE;
      }
      break;
  }
  return TASK_STATUS_RUNNING;
}

