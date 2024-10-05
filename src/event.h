#ifndef EVENT_H
#define EVENT_H


#include "virtual_screen.h"
#include "frame_timer.h"
#include "screen.h"
#include "start_screen.h"
#include "game_state.h"


void event_on_start(void);
void event_on_frame_start(void);
void event_on_render_start(void);
void event_on_game_state_change(enum GameState game_state);


#endif