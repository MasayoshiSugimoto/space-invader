#ifndef EVENT_H
#define EVENT_H


#include <curses.h>
#include "virtual_screen.h"
#include "frame_timer.h"
#include "start_screen.h"
#include "game_state.h"
#include "main_system_mode.h"
#include "main_system_game.h"
#include "sprite_editor_2.h"
#include "collision_manager_test.h"
#include "entity_spaceship_test.h"
#include "animation_test.h"
#include "main_system_sequence.h"
#include "arena.h"
#include "color_loader.h"
#include "space.h"


void event_on_program_start(void);
void event_on_system_start(void);
void event_on_frame_start(void);
void event_on_render_start(void);
void event_on_render_end(void);
void event_on_system_release(void);
void event_on_program_shutdown(void);


#endif