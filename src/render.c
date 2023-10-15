#include "render.h"


void render_help_menu() {
  mvaddstr(0, 0, "Press `Esc` to display the menu.");
}


void render_start_screen(struct Terminal* terminal) {
  log_info("BEGIN render_start_screen()");

  FILE* file = fopen("title.txt", "r");
  if (file == NULL) {
    log_fatal("Could not load `title.txt`.");
  }

  size_t buf_size = 512;
  char buf[buf_size];
  int c;
  int length = 0;
  for (int i = 0; i < buf_size; i++) {
    c = fgetc(file);
    if (c == EOF) {
      length = i;
      break;
    }
    buf[i] = c;
  }
  fclose(file);
  log_info_f("Buffer size: %d", length);

  // Count number of lines.
  int line_number = 0;
  for (int i = 0; i < length; i++) {
    if (buf[i] == '\n') line_number++;
  }
  log_info_f("Number of lines: %d", line_number);

  // Count width.
  int logo_width = 0;
  for (int i = 0; i < length; i++) {
    if (buf[i] == '\n') {
      logo_width = i;
      break;
    }
  }
  log_info_f("Logo width: %d", logo_width);

  int y = (terminal->height / 2) - (line_number / 2);
  int left = (terminal->width / 2) - (logo_width / 2);
  move(y++, left);
  for (int i = 0; i < length; i++) {
    if (buf[i] == '\n') {
      move(y++, left);
    } else if (buf[i] == EOF) {
      break;
    } else {
      addch(buf[i]);
    }
  }

  log_info("END render_start_screen()");
}


void render_credits(struct Terminal* terminal) {
  char* developed_by = "Developed by Masayoshi Sugimoto";
  int top = terminal->height / 2;
  int left = (terminal->width / 2) - (strlen(developed_by) / 2);
  mvaddstr(top, left, developed_by);
}


void render_sprite(enum SpriteId sprite_id, int left, int top) {
  const char* buf = sprite_as_string(sprite_id);
  int x = left;
  int y = top;
  for (int i = 0; i < strlen(buf); i++) {
    int c = buf[i];
    if (c == '\n') {
      x = left;
      y++;
    } else if (c == ' ') {
      x++;
    } else {
      mvaddch(y, x, c);
      x++;
    }
  }
}


void render(struct UI* ui, struct Game* game) {
  enum GameState game_state = game->game_state;

  erase();

  curs_set(CURSOR_VISIBILITY_INVISIBLE);
  switch (game_state) {
    case GAME_STATE_IN_GAME:
      screen_render(screen_get_screen(), &ui->terminal, game->entity_system);
      break;
    case GAME_STATE_MAIN_MENU:
      main_menu_render_items(main_menu_get_definition());
      break;
    default: 
      log_fatal_f("Invalid game_state: %d", game_state);
  }

  refresh();
}

