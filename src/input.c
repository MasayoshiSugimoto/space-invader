#include "input.h"



struct InputTableRow {
  enum GameState game_state;
  KeyboardKey key;
  void (*update_with_input)(struct Game* game, KeyboardKey key);
};


struct KeyNamePair {
  KeyboardKey key;
  const char* key_name;
};


void input_log_key_pressed(KeyboardKey key) {
  log_info_f("Key pressed: %s", keyboard_get_key_name(key));
}


void input_update_move_space_ship_left(struct Game* game, KeyboardKey key) {
  struct Vector v = {-1, 0};
  entity_system_add_coordinates(
      game->entity_system,
      game->spaceship_id,
      v
  );
}


void input_update_move_space_ship_right(struct Game* game, KeyboardKey key) {
  struct Vector v = {1, 0};
  entity_system_add_coordinates(
      game->entity_system,
      game->spaceship_id,
      v
  );
}


void input_update_spaceship_fire(struct Game* game, KeyboardKey key) {
  entity_spaceship_fire(game);
}


void input_update_main_menu_next(struct Game* game, KeyboardKey key) {
  main_menu_next_selection(main_menu_get_definition());
}


void input_update_main_menu_previous(struct Game* game, KeyboardKey key) {
  main_menu_previous_selection(main_menu_get_definition());
}


void input_update_main_menu_validate_selection(struct Game* game, KeyboardKey key) {
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
  {GAME_STATE_ANY, KEY_F(2), sprite_editor_enable}
};


void input_update(struct Game* game) {
  KeyboardKey key = getch();
  if (key == ERR) return;

  input_log_key_pressed(key);
  game_state_print(game->game_state);

  for (int i = 0; i < array_size(input_transition_table); i++) {
    const struct InputTableRow* transition = &input_transition_table[i];
    if (transition->game_state == GAME_STATE_ANY && transition->key == key) {
      transition->update_with_input(game, key);
    } else if (transition->game_state == game->game_state && transition->key == key) {
      transition->update_with_input(game, key);
    }
  }
}


void input_process(const struct InputMapping* input_mappings, int length) {
  KeyboardKey key = getch();
  if (key == ERR) return;
  input_log_key_pressed(key);
  for (int i = 0; i < length; i++) {
    const struct InputMapping* input_mapping = &input_mappings[i];
    if (input_mapping->key == key) {
      input_mapping->action(key);
    }
  }
}