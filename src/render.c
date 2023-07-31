#include "render.h"


void render_help_menu() {
  mvaddstr(0, 0, "Press `Esc` to display the menu.");
}


void render_center_text(
    struct WindowManager* window_manager,
    enum WindowId window_id,
    int y,
    const char* text
) {
  WINDOW* window = window_manager_get_window(window_manager, window_id);
  int width = window_manager_get_width(window_manager, window_id);
  int left = width / 2 - strlen(text) / 2;
  mvwaddstr(window, y, left, text);
}


void render_menu(
    struct Menu* menu,
    struct WindowManager* window_manager,
    struct Vector center
) {
  WINDOW* window = window_manager_setup_window(
      window_manager,
      WINDOW_ID_MENU,
      center.x,
      center.y
  );


  int text_x = window_manager_get_width(window_manager, WINDOW_ID_MENU) / 2 - 11;
  int text_y = 2;
  mvwaddstr(window, text_y, text_x, "CHOOSE YOUR DIFFICULTY");
  mvwaddstr(window, text_y + 1, text_x, "======================");

  int start_x = 9;
  int start_y = 6;
  mvwaddstr(window, start_y + 0, start_x + 3, "Easy");
  mvwaddstr(window, start_y + 2, start_x + 3, "Medium");
  mvwaddstr(window, start_y + 4, start_x + 3, "Hard");

  // Render cursor.
  mvwaddch(window, start_y + (menu->menu_selection * 2), start_x, '>');
}


void render_game_won(
    struct WindowManager* window_manager,
    struct Vector center
) {
  WINDOW* window = window_manager_setup_window(
      window_manager,
      WINDOW_ID_GAME_WON,
      center.x,
      center.y
  );
  mvwaddstr(window, 1, 1, " YOU WON ");
}


void render_game_over(
    struct WindowManager* window_manager,
    struct Vector center
) {
  WINDOW* window = window_manager_setup_window(
      window_manager,
      WINDOW_ID_GAME_OVER,
      center.x,
      center.y
  );
  mvwaddstr(window, 1, 1, " GAME OVER ");
}


void render_manual(
    struct Manual* manual,
    struct WindowManager* window_manager,
    struct Vector center
) {
  WINDOW* window = window_manager_setup_window(
      window_manager,
      WINDOW_ID_MANUAL,
      center.x,
      center.y
  );

  int height = window_manager_get_height(window_manager, WINDOW_ID_MANUAL) - 2;
  if (height <= 0) return;
  const char* page[height];
  manual_get_page(manual, page, height);
  for (int i = 0; i < height; i++) {
    mvwaddstr(window, i+1, 1, page[i]);
  }
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


void render_game() {
  int y = 0;
  attron(COLOR_PAIR(COLOR_PAIR_ID_SPACE));
  for (int i = 0; i < TERMINAL_MIN_HEIGHT; i++) {
    move(y, 0);
    for (int j = 0; j < TERMINAL_MIN_WIDTH; j++) {
      addch(' ');
    }
    y++;
  }
  attroff(COLOR_PAIR(COLOR_PAIR_ID_SPACE));
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
  struct WindowManager* window_manager = &ui->window_manager;
  //struct Vector center = terminal_center(&ui->terminal);

  erase();
  window_manager_erase(window_manager);
  if (game_state != GAME_STATE_START_SCREEN) {
    //render_help_menu();
  }

  switch (game_state) {
    case GAME_STATE_IN_GAME:
      screen_render(&ui->screen, &ui->terminal, game);
      curs_set(CURSOR_VISIBILITY_INVISIBLE);
      break;
    default: 
      log_fatal_f("Invalid game_state: %d", game_state);
  }

  refresh();
  window_manager_render(window_manager);
}

