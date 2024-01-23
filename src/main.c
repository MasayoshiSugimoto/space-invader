#include <time.h>
#include "input.h"
#include "render.h"
#include "ui.h"
#include "consts.h"
#include "game.h"
#include "screen.h"
#include "color.h"
#include "window.h"
#include "render.h"
#include "main_menu.h"
#include "virtual_screen.h"
#include "post_effect.h"


/********************************************************************************
* Main
********************************************************************************/


#if DEBUG_ENABLE_TEST

void debug_init2() {

  erase();

  short i = 0;
  for (short r = 0; r < 4; r++) {
    for (short g = 0; g < 4; g++) {
      for (short b = 0; b < 4; b++) {
        init_color(i, r * 250, g * 250, b * 250);
        init_pair(i, i, 0);
        i++;
      }
    }
  }

  for (int i = 0; i < 64; i++) {
    attron(COLOR_PAIR(i));
    addch('@');
    attroff(COLOR_PAIR(i));
  }

  refresh();
}


void debug_init() {
  erase();

  game_menu_render_items(game_menu_get_definition());
  game_menu_previous_selection(game_menu_get_definition());

  refresh();
}


#endif


struct UI ui;
struct Game game;


void main_update_game(struct Game* game, struct UI* ui) {
  switch (game->game_state) {
    case GAME_STATE_IN_GAME:
      game_update(game);
      break;
    case GAME_STATE_START_SCREEN:
      break;
    case GAME_STATE_CREDITS:
      break;
    default:
      // Do nothing.
      break;
  }
}


int main() {
  log_init();
  srand(time(NULL));
  ui_init(&ui);
  game_init(&game);
  virtual_screen_init();
  color_palette_init();
  fade_out_init();
  timer_frame_init();

  // Loop to track cursor position
  while (true) {
    log_info("LOOP BEGIN");
    timer_on_frame_start();

#if DEBUG_ENABLE_TEST
    debug_init();
    continue;
#endif

    struct Terminal* terminal = &ui.terminal;
    terminal_init(terminal);
    log_info_f("terminal={width:%d, height:%d}", terminal->width, terminal->height);

    if (terminal->height < TERMINAL_MIN_HEIGHT || terminal->width < TERMINAL_MIN_WIDTH) {
      log_info("Terminal is too small. Please resize the terminal.");
      erase();
      addstr(
          "Terminal is too small.\n"
          "Please resize the terminal.\n"
      );
      refresh();
      getch();  // Wait for resize.
      continue;
    }

    render(&ui, &game);

    input_update(&game, &ui);
    game_state_print(game.game_state);
    if (game.game_state == GAME_STATE_QUIT) {
      break;
    }

    main_update_game(&game, &ui);
  }

  endwin();  // End ncurses.
  return 0;
}

