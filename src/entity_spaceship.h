#ifndef ENTITY_SPACESHIP_H
#define ENTITY_SPACESHIP_H


#include "entity_system.h"
#include "game.h"
#include "bullet_component.h"
#include "keyboard.h"
#include "input.h"


void entity_spaceship_fire(void);
EntityId entity_spaceship_get_entity_id(void);
void entity_spaceship_move_left(void);
void entity_spaceship_move_right(void);


extern const struct InputMapping g_entity_spaceship_input_mapping[5];


#endif

