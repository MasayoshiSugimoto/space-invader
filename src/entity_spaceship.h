#ifndef ENTITY_SPACESHIP_H
#define ENTITY_SPACESHIP_H


#include "entity_system.h"
#include "game.h"
#include "bullet_component.h"


void entity_spaceship_fire(void);
void entity_spaceship_update(struct EntitySystem*);
EntityId entity_spaceship_get_entity_id(void);


#endif

