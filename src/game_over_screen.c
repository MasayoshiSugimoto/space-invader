#include "game_over_screen.h"


#define FADE_OUT_TIME_MS 1000l
#define DISPLAY_TITLE_TIME_MS 2000l
#define ONE_SECOND milliseconds_as_duration(1000)


static void _release(void) {
  log_info("Releasing game over screen.");
}


enum State {
  STATE_GAME_OVER_FADE_IN,
  STATE_GAME_OVER_DISPLAY,
  STATE_GAME_OVER_FADE_OUT,
  STATE_DONE
} _state;


enum WindowId {
  WINDOW_ID_GAME_OVER,
  WINDOW_ID_MAX
};


static struct FrameTimer _timer;
static struct VirtualWindow _windows[WINDOW_ID_MAX];


static void _fade_in_title_start(void) {
  _state = STATE_GAME_OVER_FADE_IN;
  color_fade_start_fade_in(ONE_SECOND);
}


void _state_update(void) {
  switch (_state) {
    case STATE_GAME_OVER_FADE_IN:
    case STATE_GAME_OVER_DISPLAY:
    case STATE_GAME_OVER_FADE_OUT:
      window_manager_window_draw(&_windows[WINDOW_ID_GAME_OVER]);
      break;
    case STATE_DONE:
      break;
  }

  if (_state == STATE_GAME_OVER_FADE_IN && color_fade_is_done()) {
    _state = STATE_GAME_OVER_DISPLAY;
    frame_timer_start(&_timer, ONE_SECOND);
  } else if (_state == STATE_GAME_OVER_DISPLAY && frame_timer_is_done(&_timer)) {
    _state = STATE_GAME_OVER_FADE_OUT;
    color_fade_start_fade_out(ONE_SECOND);
  } else if (_state == STATE_GAME_OVER_FADE_OUT && color_fade_is_done()) {
    _state = STATE_DONE;
  }
}


static void _game_over_screen_init(void) {
  sprite_loader_one_sprite_load(SPRITE_LOADER_FILE_NAME_GAME_OVER);
  struct VirtualWindow* window = &_windows[WINDOW_ID_GAME_OVER];
  window_manager_window_init(window);
  _windows[WINDOW_ID_GAME_OVER].buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_GAME_OVER);
  window_manager_window_center_screen_x(&_windows[WINDOW_ID_GAME_OVER]);
  window_manager_window_center_screen_y(&_windows[WINDOW_ID_GAME_OVER]);

  _fade_in_title_start();
  frame_timer_start(&_timer, 0);
}


enum MainSystemModeStatus _game_over_screen_update(void) {
  return _state == STATE_DONE ? MAIN_SYSTEM_MODE_DONE : MAIN_SYSTEM_MODE_RUNNING;
}


void _game_over_screen_render(void) {
  curs_set(CURSOR_VISIBILITY_INVISIBLE);

  _state_update();

  virtual_screen_render();
}


struct MainSystemMode g_game_over_screen_main_system_mode = {
  "MAIN_SYSTEM_MODE_GAME_OVER_SCREEN",
  &_game_over_screen_init,
  &_release,
  &main_system_no_op,
  &_game_over_screen_update,
  &_game_over_screen_render
};
