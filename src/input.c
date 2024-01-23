#include "input.h"


#define KEY_ESC 27


typedef int KeyboardKey;


struct InputTableRow {
  enum GameState game_state;
  KeyboardKey key;
  void (*update_with_input)(struct Game* game, struct UI* ui, KeyboardKey key);
};


struct KeyNamePair {
  KeyboardKey key;
  const char* key_name;
};


const struct KeyNamePair key_name_map[] = {
  {KEY_BREAK, "KEY_BREAK"},
  {KEY_DOWN, "KEY_DOWN"},
  {KEY_UP, "KEY_UP"},
  {KEY_LEFT, "KEY_LEFT"},
  {KEY_RIGHT, "KEY_RIGHT"},
  {KEY_EIC, "KEY_EIC"},
  {KEY_CLEAR, "KEY_CLEAR"},
  {KEY_HOME, "KEY_HOME"},
  {KEY_BACKSPACE, "KEY_BACKSPACE"},
  {KEY_F0, "KEY_F0"},
  {KEY_DL, "KEY_DL"},
  {KEY_IL, "KEY_IL"},
  {KEY_DC, "KEY_DC"},
  {KEY_IC, "KEY_IC"},
  {KEY_EIC, "KEY_EIC"},
  {KEY_CLEAR, "KEY_CLEAR"},
  {KEY_EOS, "KEY_EOS"},
  {KEY_EOL, "KEY_EOL"},
  {KEY_SF, "KEY_SF"},
  {KEY_SR, "KEY_SR"},
  {KEY_NPAGE, "KEY_NPAGE"},
  {KEY_PPAGE, "KEY_PPAGE"},
  {KEY_STAB, "KEY_STAB"},
  {KEY_CTAB, "KEY_CTAB"},
  {KEY_CATAB, "KEY_CATAB"},
  {KEY_ENTER, "KEY_ENTER"},
  {KEY_SRESET, "KEY_SRESET"},
  {KEY_RESET, "KEY_RESET"},
  {KEY_PRINT, "KEY_PRINT"},
  {KEY_LL, "KEY_LL"},
  {KEY_A1, "KEY_A1"},
  {KEY_A3, "KEY_A3"},
  {KEY_B2, "KEY_B2"},
  {KEY_C1, "KEY_C1"},
  {KEY_C3, "KEY_C3"},
  {KEY_BTAB, "KEY_BTAB"},
  {KEY_BEG, "KEY_BEG"},
  {KEY_CANCEL, "KEY_CANCEL"},
  {KEY_CLOSE, "KEY_CLOSE"},
  {KEY_COMMAND, "KEY_COMMAND"},
  {KEY_COPY, "KEY_COPY"},
  {KEY_CREATE, "KEY_CREATE"},
  {KEY_END, "KEY_END"},
  {KEY_EXIT, "KEY_EXIT"},
  {KEY_FIND, "KEY_FIND"},
  {KEY_HELP, "KEY_HELP"},
  {KEY_MARK, "KEY_MARK"},
  {KEY_MESSAGE, "KEY_MESSAGE"},
  {KEY_MOUSE, "KEY_MOUSE"},
  {KEY_MOVE, "KEY_MOVE"},
  {KEY_NEXT, "KEY_NEXT"},
  {KEY_OPEN, "KEY_OPEN"},
  {KEY_OPTIONS, "KEY_OPTIONS"},
  {KEY_PREVIOUS, "KEY_PREVIOUS"},
  {KEY_REDO, "KEY_REDO"},
  {KEY_REFERENCE, "KEY_REFERENCE"},
  {KEY_REFRESH, "KEY_REFRESH"},
  {KEY_REPLACE, "KEY_REPLACE"},
  {KEY_RESIZE, "KEY_RESIZE"},
  {KEY_RESTART, "KEY_RESTART"},
  {KEY_RESUME, "KEY_RESUME"},
  {KEY_SAVE, "KEY_SAVE"},
  {KEY_SBEG, "KEY_SBEG"},
  {KEY_SCANCEL, "KEY_SCANCEL"},
  {KEY_SCOMMAND, "KEY_SCOMMAND"},
  {KEY_SCOPY, "KEY_SCOPY"},
  {KEY_SCREATE, "KEY_SCREATE"},
  {KEY_SDC, "KEY_SDC"},
  {KEY_SDL, "KEY_SDL"},
  {KEY_SELECT, "KEY_SELECT"},
  {KEY_SEND, "KEY_SEND"},
  {KEY_SEOL, "KEY_SEOL"},
  {KEY_SEXIT, "KEY_SEXIT"},
  {KEY_SFIND, "KEY_SFIND"},
  {KEY_SHELP, "KEY_SHELP"},
  {KEY_SHOME, "KEY_SHOME"},
  {KEY_SIC, "KEY_SIC"},
  {KEY_SLEFT, "KEY_SLEFT"},
  {KEY_SMESSAGE, "KEY_SMESSAGE"},
  {KEY_SMOVE, "KEY_SMOVE"},
  {KEY_SNEXT, "KEY_SNEXT"},
  {KEY_SOPTIONS, "KEY_SOPTIONS"},
  {KEY_SPREVIOUS, "KEY_SPREVIOUS"},
  {KEY_SPRINT, "KEY_SPRINT"},
  {KEY_SREDO, "KEY_SREDO"},
  {KEY_SREPLACE, "KEY_SREPLACE"},
  {KEY_SRIGHT, "KEY_SRIGHT"},
  {KEY_SRSUME, "KEY_SRSUME"},
  {KEY_SSAVE, "KEY_SSAVE"},
  {KEY_SSUSPEND, "KEY_SSUSPEND"},
  {KEY_SUNDO, "KEY_SUNDO"},
  {KEY_SUSPEND, "KEY_SUSPEND"},
  {KEY_UNDO, "KEY_UNDO"},
};


const char* get_key_name(KeyboardKey key) {
  for (int i = 0; i < array_size(key_name_map); i++) {
    if (key_name_map[i].key == key) {
      return key_name_map[i].key_name;
    }
  }

  log_info_f("Invalid key pressed: {unicode: %d, character: '%c'}", key, (char)key);
  return "";
}


void input_log_key_pressed(KeyboardKey key) {
  log_info_f("Key pressed: %s", get_key_name(key));
}


void input_update_move_space_ship_left(struct Game* game, struct UI* ui, KeyboardKey key) {
  struct Vector v = {-1, 0};
  entity_system_add_coordinates(
      game->entity_system,
      game->spaceship_id,
      v
  );
}


void input_update_move_space_ship_right(struct Game* game, struct UI* ui, KeyboardKey key) {
  struct Vector v = {1, 0};
  entity_system_add_coordinates(
      game->entity_system,
      game->spaceship_id,
      v
  );
}


void input_update_spaceship_fire(struct Game* game, struct UI* ui, KeyboardKey key) {
  entity_spaceship_fire(game);
}


void input_update_main_menu_next(struct Game* game, struct UI* ui, KeyboardKey key) {
  main_menu_next_selection(main_menu_get_definition());
}


void input_update_main_menu_previous(struct Game* game, struct UI* ui, KeyboardKey key) {
  main_menu_previous_selection(main_menu_get_definition());
}


void input_update_main_menu_validate_selection(struct Game* game, struct UI* ui, KeyboardKey key) {
  log_info("Main menu selection update");
  switch (main_menu_get_selection(main_menu_get_definition())) {
    case MAIN_MENU_SELECTION_START:
      log_info("Main menu selection: START");
      game_set_game_state(game, GAME_STATE_IN_GAME);
      break;
    case MAIN_MENU_SELECTION_MANUAL:
      log_info("Main menu selection: MANUAL");
      // Do nothing
      break;
    case MAIN_MENU_SELECTION_QUIT:
      log_info("Main menu selection: QUIT");
      // Do nothing
      break;
  }
}


const struct InputTableRow input_transition_table[] = {
  {GAME_STATE_IN_GAME, KEY_LEFT, input_update_move_space_ship_left},
  {GAME_STATE_IN_GAME, KEY_RIGHT, input_update_move_space_ship_right},
  {GAME_STATE_IN_GAME, ' ', input_update_spaceship_fire},
  {GAME_STATE_IN_GAME, 'a', input_update_move_space_ship_left},
  {GAME_STATE_IN_GAME, 'd', input_update_move_space_ship_right},
  {GAME_STATE_MAIN_MENU, KEY_UP, input_update_main_menu_previous},
  {GAME_STATE_MAIN_MENU, KEY_DOWN, input_update_main_menu_next},
  {GAME_STATE_MAIN_MENU, 'w', input_update_main_menu_previous},
  {GAME_STATE_MAIN_MENU, 's', input_update_main_menu_next},
  {GAME_STATE_MAIN_MENU, '\n', input_update_main_menu_validate_selection},
};


void input_update(struct Game* game, struct UI* ui) {
  KeyboardKey key = getch();
  if (key == ERR) return;

  input_log_key_pressed(key);
  game_state_print(game->game_state);

  for (int i = 0; i < array_size(input_transition_table); i++) {
    const struct InputTableRow* transition = &input_transition_table[i];
    if (game->game_state == GAME_STATE_START_SCREEN) {
      game->game_state = GAME_STATE_IN_GAME;
    } else if (transition->game_state == game->game_state && transition->key == key) {
      transition->update_with_input(game, ui, key);
    }
  }
}


