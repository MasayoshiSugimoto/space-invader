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
#include "sprite_editor.h"
#include "frame_timer_test.h"
#include "test_suite.h"


/********************************************************************************
* Main
********************************************************************************/


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
  timer_frame_init();
  virtual_screen_setup();
  start_screen_init();
  srand(time(NULL));

  #if TEST_MODE_ENABLE
    test_suite_run();
  #endif

  // Loop to track cursor position
  while (true) {
    log_info("LOOP BEGIN");
    timer_on_frame_start();

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

