#ifndef GAME_STATE_H
#define GAME_STATE_H


#include "log.h"


enum GameState {
  GAME_STATE_ANY = -1,
  GAME_STATE_MAIN_MENU,
  GAME_STATE_IN_GAME,
  GAME_STATE_IN_GAME_2_INIT,
  GAME_STATE_IN_GAME_2,
  GAME_STATE_GAME_OVER,
  GAME_STATE_GAME_WON,
  GAME_STATE_MENU,
  GAME_STATE_MANUAL,
  GAME_STATE_START_SCREEN_INIT,
  GAME_STATE_START_SCREEN,
  GAME_STATE_CREDITS,
  GAME_STATE_QUIT,
  GAME_STATE_MAX
};


void game_state_print(enum GameState game_state);
const char* game_state_as_string(enum GameState game_state);


#endif
