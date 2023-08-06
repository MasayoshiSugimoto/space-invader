#ifndef BULLET_COMPONENT_H
#define BULLET_COMPONENT_H


#include <stdint.h>
#include <stdbool.h>
#include "entity_system.h"
#include "sprite_component.h"
#include "component_manager.h"


void bullet_component_init();
void bullet_component_fire(struct EntitySystem* entity_system, struct Vector bullet_position);
void bullet_component_setup(struct EntitySystem* entity_system, EntityId entity_id);
void bullet_component_update(struct EntitySystem* entity_system, uint64_t delta_time_millisecond);
void bullet_component_cleanup(struct EntitySystem* entity_system);
void bullet_component_disable(struct EntitySystem* entity_system, EntityId entity_id);


#endif
