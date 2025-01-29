#ifndef ANIMATION_H
#define ANIMATION_H


#include <stdbool.h>
#include "entity_system.h"
#include "timer.h"
#include "sprite_component.h"
#include "sprite_loader.h"


#define ANIMATION_NAME_EXPLOSION "animation_explosion.dat"


void animation_init(void);
void animation_setup(void);
void animation_update(void);
void animation_set(EntityId entity_id, const char* animation_name);
bool animation_is_done(EntityId entity_id);


#endif
