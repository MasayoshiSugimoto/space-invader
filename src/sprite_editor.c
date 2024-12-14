#include "sprite_editor.h"


#define WINDOW_INFO_HEIGHT 5


enum Mode {
  MODE_EDIT,
  MODE_SELECTION,
};


static struct Selection {
  int start_x;
  int start_y;
  bool is_active;
} _selection;
static struct VirtualWindow* _window_edit;
static struct VirtualCursor _cursor;
static struct VirtualWindow* _window_selection;
static struct VirtualCursor _cursor_selection;
static struct VirtualWindow* _window_log;
static struct VirtualCursor _cursor_log;
static const struct Color BLACK = {0, 0, 0};
static const struct Color WHITE = {255, 255, 255};
static ColorPairId _selection_color_pair_id;


void _log(const char* text) {
  log_info_f("%s", text);
  virtual_cursor_text_print(&_cursor_log, text);
  if (_cursor_log.y + 1 == _window_log->height) {
    window_manager_window_scroll_down(_window_log);
    _cursor_log.x = 0;
  } else {
    virtual_cursor_new_line(&_cursor_log);
  }
}


void _selection_init(void) {
  memset(&_selection, 0, sizeof(_selection));
}


static void _selection_mode_on(void) {
  _log("Selection mode on.");
  _selection.is_active = true;
  _selection.start_x = _cursor.x;
  _selection.start_y = _cursor.y;
}


static void _selection_mode_off(void) {
  _log("Selection mode off.");
  _selection.is_active = false;
}


static void _selection_mode_switch(KeyboardKey key) {
  if (_selection.is_active) {
    _selection_mode_off();
  } else {
    _selection_mode_on();
  }
}


static enum Mode _mode_get(void) {
  if (_selection.is_active) {
    return MODE_SELECTION;
  } else {
    return MODE_EDIT;
  }
}


static void _cursor_move_up(KeyboardKey key) {
  virtual_cursor_move_up(&_cursor);
}


static void _cursor_move_right(KeyboardKey key) {
  virtual_cursor_move_right(&_cursor);
}


static void _cursor_move_down(KeyboardKey key) {
  virtual_cursor_move_down(&_cursor);
}


static void _cursor_move_left(KeyboardKey key) {
  virtual_cursor_move_left(&_cursor);
}


static void _key_handle_key_default(KeyboardKey key) {
  // All printable characters.
  int space = 32;
  int tilde = 126;
  if (space <= key && key <= tilde) {
    virtual_cursor_character_set(&_cursor, key, COLOR_PAIR_ID_DEFAULT);
  }
}


static void _copy(KeyboardKey key) {

}


static void _paste(KeyboardKey key) {
  
}


static struct InputMapping _input_mappings_default[] = {
  {KEY_UP, _cursor_move_up},
  {KEY_RIGHT, _cursor_move_right},
  {KEY_DOWN, _cursor_move_down},
  {KEY_LEFT, _cursor_move_left},
};


static struct InputMapping _input_mappings_selection[] = {
  {KEY_F(2), _selection_mode_switch},
  {KEY_F(3), _copy},
};


static struct InputMapping _input_mappings_edit[] = {
  {KEY_F(2), _selection_mode_switch},
  {KEY_F(4), _paste},
  {KEY_MAX, _key_handle_key_default},
};


static void _init(void) {
   window_manager_init();

  int separator_y = virtual_screen_get_height() - 2 - WINDOW_INFO_HEIGHT;

  _window_edit = window_manager_window_new(virtual_screen_get_width() - 2, separator_y - 1);
  _window_edit->has_border = true;
  _window_edit->offset_x = 1;
  _window_edit->offset_y = 1;
  virtual_cursor_init(&_cursor);
  _cursor.window = _window_edit;

  _window_log = window_manager_window_new(virtual_screen_get_width() - 2, WINDOW_INFO_HEIGHT);
  _window_log->has_border = true;
  _window_log->offset_x = 1;
  _window_log->offset_y = separator_y + 1;

  virtual_cursor_init(&_cursor_log);
  _cursor_log.window = _window_log;

  _window_selection = window_manager_window_new(virtual_screen_get_width() - 2, separator_y - 1);
  _window_selection->has_border = false;
  _window_selection->is_transparent = true;
  _window_selection->offset_x = 1;
  _window_selection->offset_y = 1;
  virtual_cursor_init(&_cursor_selection);
  _cursor_selection.window = _window_selection;

  _selection_init();

  color_reset();
  color_color_palette_activate(0);
  ColorId black = color_color_palette_add(BLACK);
  ColorId white = color_color_palette_add(WHITE);
  color_color_pair_add(black, white);  // 1
  _selection_color_pair_id = color_color_pair_add(white, black);  // 2
  color_color_palette_push(0);
  color_color_pair_push();

  _log("Sprite editor initialized.");
}


static void _input_update(void) {
  KeyboardKey key = input_get();
  if (input_process(_input_mappings_default, array_size(_input_mappings_default), key) == key) return;
  switch (_mode_get())
  {
  case MODE_EDIT:
    input_process(_input_mappings_edit, array_size(_input_mappings_edit), key);
    break;
  case MODE_SELECTION:
    input_process(_input_mappings_selection, array_size(_input_mappings_selection), key);
    break;
  default:
    break;
  }
}


static enum MainSystemModeStatus _system_update(void) {
  return MAIN_SYSTEM_MODE_RUNNING;
}


static void _render(void) {
  window_manager_window_draw(_window_edit);
  window_manager_window_draw(_window_log);
  if (_selection.is_active) {
    window_manager_window_fill_character(_window_selection, 0);
    int min_x = imin(_selection.start_x, _cursor.x);
    int min_y = imin(_selection.start_y, _cursor.y);
    int max_x = imax(_selection.start_x, _cursor.x);
    int max_y = imax(_selection.start_y, _cursor.y);
    for (int x = min_x; x <= max_x; x++) {
      struct VirtualPixel pixel = window_manager_window_get_pixel(_window_edit, x, min_y);
      pixel.color_pair_id = _selection_color_pair_id;
      window_manager_window_set_pixel(_window_selection, x, min_y, pixel);
    }
    for (int x = min_x; x <= max_x; x++) {
      struct VirtualPixel pixel = window_manager_window_get_pixel(_window_edit, x, max_y);
      pixel.color_pair_id = _selection_color_pair_id;
      window_manager_window_set_pixel(_window_selection, x, max_y, pixel);
    }
    for (int y = min_y; y <= max_y; y++) {
      struct VirtualPixel pixel = window_manager_window_get_pixel(_window_edit, min_x, y);
      pixel.color_pair_id = _selection_color_pair_id;
      window_manager_window_set_pixel(_window_selection, min_x, y, pixel);
    }
    for (int y = min_y; y <= max_y; y++) {
      struct VirtualPixel pixel = window_manager_window_get_pixel(_window_edit, max_x, y);
      pixel.color_pair_id = _selection_color_pair_id;
      window_manager_window_set_pixel(_window_selection, max_x, y, pixel);
    }
    window_manager_window_draw(_window_selection);
  }
  virtual_screen_render();
  virtual_cursor_show(&_cursor);
}


struct MainSystemMode g_main_system_mode_sprite_editor = {
  "MAIN_SYSTEM_MODE_SPRITE_EDITOR",
  _init,
  _input_update,
  _system_update,
  _render
};
