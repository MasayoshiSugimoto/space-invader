#ifndef GAME_H
#define GAME_H


#include "cursor.h"
#include "entity_system.h"
#include "consts.h"
#include "enemy_ai_basic_component.h"
#include "bullet_component.h"
#include "collision_manager.h"
#include "animation.h"
#include "faction_component.h"
#include "game_state.h"
#include "main_system_mode.h"
#include "entity_data.h"


enum GameOverResult {
    GAME_OVER_NONE,
    GAME_OVER_WIN,
    GAME_OVER_LOOSE,
};


struct MainSystemMode g_game_main_system_mode;


void game_init(void);
void game_init_entities(const struct EntityData* entity_datas, size_t entity_datas_length);
void game_print_state(enum GameState game_state);
void game_set_game_state(enum GameState game_state);
void game_update(void);
void game_render(void);
enum GameOverResult game_game_over_result_get(void);


#endif
