#include "sprite_editor.h"


#define MENU_HEIGHT 5
#define SPRITE_DEFAULT_WIDTH 10
#define SPRITE_DEFAULT_HEIGHT 10


enum Mode {
  MODE_CHARACTER_SELECT,
  MODE_COLOR_SELECT,
  MODE_MAX,
};


struct SpritePixel {
  char character;
  struct Color color;
};


struct MutableSprite {
  int width;
  int height;
  struct SpritePixel* pixels;
};


struct VirtualWindow g_sprite_widget;
struct VirtualWindow g_menu_widget;
struct MutableSprite g_sprite;
struct Cursor g_cursor;


size_t get_pixel_count() {
  return g_sprite.width * g_sprite.height;
}


void pixel_init(struct SpritePixel* pixel, chtype clear_character) {
  pixel->character = clear_character;
  pixel->color = S_COLOR_BLACK;
}


void sprite_editor_cursor_setup(struct Cursor* cursor) {
  curs_set(CURSOR_VISIBILITY_NORMAL);
  move(1, 1);
}


void sprite_editor_cursor_draw(struct Cursor* cursor) {
  move(cursor->y + 1, cursor->x + 1);
}


void sprite_editor_sprite_clear(chtype clear_character) {
  for (int i = 0; i < get_pixel_count(); i++) {
    pixel_init(&g_sprite.pixels[i], clear_character);
  }
}


void sprite_editor_sprite_init(int width, int height) {
  size_t length = width * height;
  g_sprite.width = width;
  g_sprite.height = height;
  g_sprite.pixels = malloc(sizeof(*g_sprite.pixels)*length);
  sprite_editor_sprite_clear(' ');
}


int sprite_editor_sprite_buffer_index(int x, int y) {
  return y * g_sprite.width + x;
}


void sprite_editor_init() {
  // struct Terminal terminal;
  // terminal_init(&terminal);

  // virtual_window_init(&g_sprite_widget);
  // virtual_window_setup(&g_sprite_widget, terminal.width, terminal.height - MENU_HEIGHT, 0, 0);
  // virtual_window_init(&g_menu_widget);
  // virtual_window_setup(&g_menu_widget, terminal.width, MENU_HEIGHT, 0, terminal.height - MENU_HEIGHT);
  // const int border_size = 2;
  // sprite_editor_sprite_init(g_sprite_widget.width - border_size, g_sprite_widget.height - border_size);
  // sprite_editor_sprite_clear(' ');
  // cursor_init(&g_cursor);

  // sprite_editor_cursor_setup(&g_cursor);
}


void sprite_editor_render() {
  struct Terminal terminal;
  terminal_init(&terminal);

  // virtual_window_setup(&g_sprite_widget, terminal.width, terminal.height - MENU_HEIGHT, 0, 0);

  // virtual_window_clear(&g_sprite_widget, '#');
//  virtual_window_setup_from_sprite(&g_sprite_widget, &sprite);

  // virtual_window_setup(&g_menu_widget, terminal.width, MENU_HEIGHT, 0, terminal.height - MENU_HEIGHT);

  // virtual_window_draw(&g_sprite_widget);
  // virtual_window_draw(&g_menu_widget);

  erase();
  virtual_screen_render();
  sprite_editor_cursor_draw(&g_cursor);
  refresh();
}


void sprite_editor_cursor_move(struct Cursor* cursor, int dx, int dy) {
  cursor->x = iclamp(0, cursor->x + dx, g_sprite.width - 1);
  cursor->y = iclamp(0, cursor->y + dy, g_sprite.height - 1);
}


void sprite_editor_input_update(KeyboardKey key) {
  switch (key)
  {
  case ERR:
    return;
  case KEY_UP:
    sprite_editor_cursor_move(&g_cursor, 0, -1);
    break;
  case KEY_RIGHT:
    sprite_editor_cursor_move(&g_cursor, 1, 0);
    break;
  case KEY_DOWN:
    sprite_editor_cursor_move(&g_cursor, 0, 1);
    break;
  case KEY_LEFT:
    sprite_editor_cursor_move(&g_cursor, -1, 0);
    break;
  default:
    // virtual_window_set(&g_sprite_widget, g_cursor.x + 1, g_cursor.y + 1, key);
    break;
  }
}


void sprite_editor_enable(struct Game* game, struct UI* ui, KeyboardKey key) {
  log_info("Enabling sprite editor...");
  sprite_editor_init();
  game->game_state = GAME_STATE_SPRITE_EDITOR;
}
