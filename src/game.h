#ifndef GAME_H
#define GAME_H


#include "cursor.h"
#include "entity_system.h"
#include "consts.h"
#include "sprite.h"
#include "enemy_ai_basic_component.h"
#include "bullet_component.h"
#include "collision_manager.h"
#include "animation.h"
#include "faction_component.h"
#include "screen.h"
#include "game_state.h"
#include "main_system_mode.h"


struct Game {
  struct Cursor cursor; 
  enum GameState game_state;
  struct EntitySystem* entity_system;
  EntityId spaceship_id;
  uint64_t last_frame_time_millisecond;
};


struct MainSystemMode g_game_main_system_mode;


void game_init(struct Game* game);
void game_print_state(enum GameState game_state);
void game_set_game_state(struct Game* game, enum GameState game_state);
void game_update(struct Game* game);


#endif
