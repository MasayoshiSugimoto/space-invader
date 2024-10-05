#include "start_screen.h"


#define FADE_OUT_TIME_MS 1000l
#define DISPLAY_TITLE_TIME_MS 2000l
#define ONE_SECOND milliseconds_as_duration(1000)


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


static struct VirtualWindow* _windows[WINDOW_ID_MAX];
static struct FrameTimer _timer;


void _fade_in_title_start(void) {
  _state = STATE_CREDITS_FADE_IN;
  color_fade_start_fade_in(ONE_SECOND);
}


void _title_render() {
  struct VirtualWindow* title = _windows[WINDOW_ID_TITLE];
  window_manager_window_center_screen_x(title);
  window_manager_window_center_screen_y(title);
  window_manager_window_draw(title);
}


void _credit_render() {
  struct VirtualWindow* credits = _windows[WINDOW_ID_CREDITS];
  window_manager_window_center_screen_x(credits);
  window_manager_window_center_screen_y(credits);
  window_manager_window_draw(credits);
}


void _state_update(void) {

  switch (_state) {
    case STATE_CREDITS_FADE_IN:
    case STATE_CREDITS_DISPLAY:
    case STATE_CREDITS_FADE_OUT:
      _credit_render();
      break;
    case STATE_TITLE_FADE_IN:
    case STATE_TITLE_DISPLAY:
    case STATE_TITLE_FADE_OUT:
      _title_render();
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
  window_manager_init();
  _windows[WINDOW_ID_CREDITS] = window_manager_window_setup_from_sprite(sprite_get_sprite(SPRITE_ID_CREDITS));
  _windows[WINDOW_ID_TITLE] = window_manager_window_setup_from_sprite(sprite_get_sprite(SPRITE_ID_TITLE));
  color_color_set_default();

  _fade_in_title_start();
  frame_timer_start(&_timer, 0);
}


enum TaskStatus start_screen_render(void) {
  curs_set(CURSOR_VISIBILITY_INVISIBLE);

  _state_update();

  virtual_screen_render();

  return _state == STATE_DONE ? TASK_STATUS_DONE : TASK_STATUS_RUNNING;
}

