#ifndef GAME_H
#define GAME_H


#include "cursor.h"
#include "entity_system.h"
#include "consts.h"
#include "sprite.h"
#include "enemy_ai_basic_component.h"
#include "bullet_component.h"
#include "collision_manager.h"


enum GameState {
  GAME_STATE_START_MENU,
  GAME_STATE_IN_GAME,
  GAME_STATE_GAME_OVER,
  GAME_STATE_GAME_WON,
  GAME_STATE_MENU,
  GAME_STATE_MANUAL,
  GAME_STATE_START_SCREEN,
  GAME_STATE_CREDITS,
  GAME_STATE_QUIT,
  GAME_STATE_MAX
};


struct Game {
  struct Cursor cursor; 
  enum GameState game_state;
  struct EntitySystem* entity_system;
  EntityId spaceship_id;
  uint64_t last_frame_time_millisecond;
};


void game_init(struct Game* game);
void game_print_state(enum GameState game_state);
void game_set_game_state(struct Game* game, enum GameState game_state);
void game_update(struct Game* game);


#endif
