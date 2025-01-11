#ifndef ENEMY_AI_BASIC_H
#define ENEMY_AI_BASIC_H


#include <stdint.h>
#include "entity_system.h"
#include "sprite_component.h"


void enemy_ai_basic_init(void);
void enemy_ai_basic_update(uint64_t delta_time_millisecond);
void enemy_ai_basic_disable(EntityId entity_id);
void enemy_ai_basic_margin_from_border_set(int margin_from_border);
void enemy_ai_basic_activate(EntityId entity_id);


#endif
