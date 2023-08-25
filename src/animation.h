#ifndef ANIMATION_H
#define ANIMATION_H


#include <stdbool.h>
#include "sprite.h"
#include "entity_system.h"
#include "timer.h"
#include "sprite_component.h"


typedef int AnimationId;


void animation_init();
void animation_update(struct EntitySystem* entity_system, Duration delta_time);
void animation_set(EntityId entity_id, AnimationId animation_id);


#endif
