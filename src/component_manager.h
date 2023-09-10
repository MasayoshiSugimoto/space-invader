#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H


#include "sprite_component.h"
#include "bullet_component.h"
#include "enemy_ai_basic_component.h"
#include "faction_component.h"


void component_manager_cleanup(struct EntitySystem* entity_system, EntityId entity_id);


#endif
