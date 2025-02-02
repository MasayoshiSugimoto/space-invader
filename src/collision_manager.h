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
void collision_manager_update(void);
bool collision_manager_is_collision(EntityId entity_id);
void collision_manager_set_collision_handler(EntityId entity_id, void (*on_collision)(EntityId));
void collision_manager_deactivate(EntityId entity_id);
void collision_manager_activate(EntityId entity_id);


#endif
