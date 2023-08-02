#ifndef ENEMY_AI_BASIC_H
#define ENEMY_AI_BASIC_H


#include <stdint.h>
#include "entity_system.h"
#include "sprite_component.h"


void enemy_ai_basic_init();
void enemy_ai_basic_update(struct EntitySystem* entity_system, uint64_t delta_time_millisecond);


#endif
