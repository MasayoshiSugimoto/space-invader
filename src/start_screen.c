#include "start_screen.h"


#define FADE_OUT_TIME_MS 1000l
#define DISPLAY_TITLE_TIME_MS 2000l
#define ONE_SECOND milliseconds_as_duration(1000)


static void _release(void) {
  log_info("Releasing start screen.");
}


struct MainSystemMode g_start_screen_main_system_mode = {
    "MAIN_SYSTEM_MODE_START_SCREEN",
    &start_screen_init,
    &_release,
    &main_system_no_op,
    &start_screen_update,
    &start_screen_render
};


enum State {
  STATE_CREDITS_FADE_IN,
  STATE_CREDITS_DISPLAY,
  STATE_CREDITS_FADE_OUT,
  STATE_TITLE_FADE_IN,
  STATE_TITLE_DISPLAY,
  STATE_TITLE_FADE_OUT,
  STATE_DONE
} _state;


enum WindowId {
  WINDOW_ID_CREDITS,
  WINDOW_ID_TITLE,
  WINDOW_ID_MAX
};


static struct FrameTimer _timer;
static struct VirtualWindow2 _windows[WINDOW_ID_MAX];


void _fade_in_title_start(void) {
  _state = STATE_CREDITS_FADE_IN;
  color_fade_start_fade_in(ONE_SECOND);
}


void _state_update(void) {
  switch (_state) {
    case STATE_CREDITS_FADE_IN:
    case STATE_CREDITS_DISPLAY:
    case STATE_CREDITS_FADE_OUT:
      window_manager_window_draw(&_windows[WINDOW_ID_CREDITS]);
      break;
    case STATE_TITLE_FADE_IN:
    case STATE_TITLE_DISPLAY:
    case STATE_TITLE_FADE_OUT:
      window_manager_window_draw(&_windows[WINDOW_ID_TITLE]);
      break;
    case STATE_DONE:
      break;
  }

  if (_state == STATE_CREDITS_FADE_IN && color_fade_is_done()) {
    _state = STATE_CREDITS_DISPLAY;
    frame_timer_start(&_timer, ONE_SECOND);
  } else if (_state == STATE_CREDITS_DISPLAY && frame_timer_is_done(&_timer)) {
    _state = STATE_CREDITS_FADE_OUT;
    color_fade_start_fade_out(ONE_SECOND);
  } else if (_state == STATE_CREDITS_FADE_OUT && color_fade_is_done()) {
    _state = STATE_TITLE_FADE_IN;
    color_fade_start_fade_in(ONE_SECOND);
  } else if (_state == STATE_TITLE_FADE_IN && color_fade_is_done()) {
    _state = STATE_TITLE_DISPLAY;
    frame_timer_start(&_timer, ONE_SECOND);
  } else if (_state == STATE_TITLE_DISPLAY && frame_timer_is_done(&_timer)) {
    _state = STATE_TITLE_FADE_OUT;
    color_fade_start_fade_out(ONE_SECOND);
  } else if (_state == STATE_TITLE_FADE_OUT && color_fade_is_done()) {
    _state = STATE_DONE;
  }
}


void start_screen_init(void) {
  sprite_loader_one_sprite_load(SPRITE_LOADER_FILE_NAME_CREDITS);
  sprite_loader_one_sprite_load(SPRITE_LOADER_FILE_NAME_TITLE);
  for (int i = 0; i < WINDOW_ID_TITLE; i++) {
    struct VirtualWindow2* window = &_windows[i];
    window_manager_window_init(window);
  }
  _windows[WINDOW_ID_CREDITS].buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_CREDITS);
  _windows[WINDOW_ID_TITLE].buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_TITLE);
  window_manager_window_center_screen_x(&_windows[WINDOW_ID_CREDITS]);
  window_manager_window_center_screen_y(&_windows[WINDOW_ID_CREDITS]);
  window_manager_window_center_screen_x(&_windows[WINDOW_ID_TITLE]);
  window_manager_window_center_screen_y(&_windows[WINDOW_ID_TITLE]);
  color_color_set_default();

  _fade_in_title_start();
  frame_timer_start(&_timer, 0);
}


enum MainSystemModeStatus start_screen_update(void) {
  return _state == STATE_DONE ? MAIN_SYSTEM_MODE_DONE : MAIN_SYSTEM_MODE_RUNNING;
}


void start_screen_render(void) {
  curs_set(CURSOR_VISIBILITY_INVISIBLE);

  _state_update();

  virtual_screen_render();
}

