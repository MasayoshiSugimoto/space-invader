#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H


#include "consts.h"
#include "entity_system.h"
#include "sprite_component.h"
#include "util.h"
#include "faction_component.h"


void collision_manager_init(void);
void collision_manager_allocate(int width, int height);
void collision_manager_release(void);
void collision_manager_update(struct EntitySystem* entity_system);
bool collision_manager_is_collision(EntityId entity_id);


#endif
