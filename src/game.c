#include "game.h"


const char* g_game_state_strings[] = {
  "GAME_STATE_START_MENU",
  "GAME_STATE_IN_GAME",
  "GAME_STATE_GAME_OVER",
  "GAME_STATE_GAME_WON",
  "GAME_STATE_MENU",
  "GAME_STATE_MANUAL",
  "GAME_STATE_START_SCREEN",
  "GAME_STATE_CREDITS",
  "GAME_STATE_QUIT",
  "GAME_STATE_MAX"
};


void game_init_spaceship(struct Game* game) {
  EntityId entity_id = entity_spaceship_create(game->entity_system);
  game->spaceship_id = entity_id;
  const struct Sprite* sprite = sprite_get_sprite(SPRITE_ID_SPACESHIP);
  struct Vector v = {
    SCREEN_WIDTH / 2 - sprite->width / 2,
    SCREEN_HEIGHT - sprite->height
  };
  entity_system_set_coordinates(game->entity_system, entity_id, v);
}


void game_init(struct Game* game) {
  log_info("game_init(game)");
  game->cursor.x = 0;
  game->cursor.y = 0;
  game->game_state = GAME_STATE_IN_GAME;


  game_board_init(&game->game_board, 2, 2);

  game->entity_system = entity_system_create();
  entity_system_init(game->entity_system);
  game_init_spaceship(game);
}


void game_print_state(enum GameState game_state) {
  log_info_f("Game state: %s", g_game_state_strings[game_state]);
}


void game_set_game_state(struct Game* game, enum GameState game_state) {
  log_info_f("Game state set to: %s", g_game_state_strings[game_state]);
  if (game_state >= GAME_STATE_MAX) return;
  game->game_state = game_state;
}
