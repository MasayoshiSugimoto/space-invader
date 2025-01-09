#ifndef BULLET_COMPONENT_H
#define BULLET_COMPONENT_H


#include <stdint.h>
#include <stdbool.h>
#include "entity_system.h"
#include "sprite_component.h"
#include "component_manager.h"
#include "faction_component.h"
#include "sprite_buffer.h"
#include "sprite_loader.h"


void bullet_component_init();
void bullet_component_fire(struct Vector bullet_position);
void bullet_component_setup(EntityId entity_id);
void bullet_component_update(uint64_t delta_time_millisecond);
void bullet_component_cleanup(void);
void bullet_component_disable(EntityId entity_id);


#endif
