#include "sprite_editor_2.h"


#define SPRITE_EDITOR_WINDOW_EDIT_WIDTH 40
#define SPRITE_EDITOR_WINDOW_LOG_HEIGHT 5


static const int LOG_BUFFER_SIZE = 1024 * 50;
static uint32_t _current_file_index = 0;
static uint32_t _file_count = 0;
static char _current_sprite_name[SYSTEM_FILE_NAME_MAX];


enum Mode {
  MODE_EDIT,
  MODE_SELECTION,
};


struct Widget {
  struct SpriteBuffer sprite_buffer;
  struct VirtualWindow window;
  struct VirtualCursor cursor;
};


static struct Selection {
  int start_x;
  int start_y;
  bool is_active;
} _selection;
static struct Widget _widget_edit;
static struct Widget _widget_log;
static struct Widget _widget_palette;
static struct LogBuffer _log_buffer;


static void _load_sprite(void) {
  const char* directory_path = "./data/sprites";
  _file_count = 0;
  {
    DIR* d = opendir(directory_path);
    struct dirent *dir;
    assert_f(d != NULL, "Failed to read directory: %s", directory_path);
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") == 0) continue;
      if (strcmp(dir->d_name, "..") == 0) continue;
      if (_file_count == _current_file_index) {
        sprite_loader_release();
        sprite_loader_one_sprite_load(dir->d_name);
        strcpy(_current_sprite_name, dir->d_name);
      }
      _file_count++;
    }
    closedir(d);
  }
}


static void _log(const char* text) {
  log_info_f("%s", text);
  log_buffer_add_string(&_log_buffer, text);
}


static void _widget_init(struct Widget* widget, int width, int height) {
  sprite_buffer_allocate(&widget->sprite_buffer, width, height);
  sprite_buffer_clear(&widget->sprite_buffer);
  virtual_cursor_init(&widget->cursor, &widget->sprite_buffer);
  window_manager_window_init(&widget->window);
  widget->window.buffer = &widget->sprite_buffer;
}


// static void _selection_init(void) {
//   memset(&_selection, 0, sizeof(_selection));
// }


static void _selection_mode_on(void) {
  _log("Selection mode on.");
  _selection.is_active = true;
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
  virtual_cursor_move_up(&_widget_edit.cursor);
}


static void _cursor_move_right(KeyboardKey key) {
  virtual_cursor_move_right(&_widget_edit.cursor);
}


static void _cursor_move_down(KeyboardKey key) {
  virtual_cursor_move_down(&_widget_edit.cursor);
}


static void _cursor_move_left(KeyboardKey key) {
  virtual_cursor_move_left(&_widget_edit.cursor);
}


static void _load_previous_sprite(KeyboardKey key) {
  log_info("Loading previous sprite.");
  _current_file_index = (_current_file_index + _file_count - 1 ) % _file_count;
  _load_sprite();
  _widget_edit.sprite_buffer = *sprite_loader_sprite_get(_current_sprite_name);
  virtual_cursor_init(&_widget_edit.cursor, &_widget_edit.sprite_buffer);
  _widget_edit.window.buffer = &_widget_edit.sprite_buffer;
}


static void _load_next_sprite(KeyboardKey key) {
  log_info("Loading next sprite.");
  _current_file_index = (_current_file_index + 1) % _file_count;
  _load_sprite();
  _widget_edit.sprite_buffer = *sprite_loader_sprite_get(_current_sprite_name);
  virtual_cursor_init(&_widget_edit.cursor, &_widget_edit.sprite_buffer);
  _widget_edit.window.buffer = &_widget_edit.sprite_buffer;
}


static void _key_handle_key_default(KeyboardKey key) {
  // All printable characters.
  int space = 32;
  int tilde = 126;
  if (space <= key && key <= tilde) {
    virtual_cursor_character_set(&_widget_edit.cursor, key, COLOR_PAIR_ID_DEFAULT);
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
  {KEY_PPAGE, _load_previous_sprite},
  {KEY_NPAGE, _load_next_sprite},
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
  log_info("Initializing sprite editor.");
  _load_sprite();

  int border = 1;

  _widget_edit.sprite_buffer = *sprite_loader_sprite_get(_current_sprite_name);
  virtual_cursor_init(&_widget_edit.cursor, &_widget_edit.sprite_buffer);
  window_manager_window_init(&_widget_edit.window);
  _widget_edit.window.buffer = &_widget_edit.sprite_buffer;
  _widget_edit.window.has_border = true;
  _widget_edit.window.offset_x = border;
  _widget_edit.window.offset_y = border;

  _widget_init(
    &_widget_palette, 
    virtual_screen_get_width() - SPRITE_EDITOR_WINDOW_EDIT_WIDTH - 3 * border, 
    virtual_screen_get_height() - SPRITE_EDITOR_WINDOW_LOG_HEIGHT - 3 * border
  );
  _widget_palette.window.has_border = true;
  _widget_palette.window.offset_x = SPRITE_EDITOR_WINDOW_EDIT_WIDTH + 2;
  _widget_palette.window.offset_y = 1;

  _widget_init(&_widget_log, virtual_screen_get_width() - 2 * border, SPRITE_EDITOR_WINDOW_LOG_HEIGHT);
  log_buffer_init(&_log_buffer);
  log_buffer_allocate(&_log_buffer, LOG_BUFFER_SIZE);
  _widget_log.window.has_border = true;
  _widget_log.window.offset_x = border;
  _widget_log.window.offset_y = virtual_screen_get_height() - border - SPRITE_EDITOR_WINDOW_LOG_HEIGHT;
}


static void _release(void) {
  log_info("Releasing sprite editor.");
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
  log_buffer_draw_to_sprite_buffer(&_log_buffer, &_widget_log.sprite_buffer);
  window_manager_window_draw(&_widget_edit.window);
  window_manager_window_draw(&_widget_log.window);
  window_manager_window_draw(&_widget_palette.window);
  virtual_screen_render();
  window_manager_cursor_show(&_widget_edit.window, _widget_edit.cursor.x, _widget_edit.cursor.y);
}


struct MainSystemMode g_main_system_mode_sprite_editor_2 = {
  "MAIN_SYSTEM_MODE_SPRITE_EDITOR_2",
  _init,
  _release,
  _input_update,
  _system_update,
  _render
};
