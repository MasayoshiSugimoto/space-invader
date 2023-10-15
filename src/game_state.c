#include "game_state.h"


const char* g_game_state_strings[] = {
  "GAME_STATE_MAIN_MENU",
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


void game_state_print(enum GameState game_state) {
  log_info_f("Game state: %s", g_game_state_strings[game_state]);
}


const char* game_state_as_string(enum GameState game_state) {
  return g_game_state_strings[game_state];
}
