#ifndef ANIMATION_H
#define ANIMATION_H


#include <stdbool.h>
#include "entity_system.h"
#include "timer.h"
#include "sprite_component.h"
#include "sprite_loader.h"
#include "animation_step.h"
#include "slice.h"


#define ANIMATION_NAME_EXPLOSION "animation_explosion.dat"
#define ANIMATION_NAME_SPACESHIP "animation_spaceship.dat"
#define ANIMATION_NAME_ALIEN "animation_alien.dat"


void animation_init(void);
void animation_setup(void);
void animation_update(void);
void animation_set(EntityId entity_id, const char* animation_name);
void animation_start(EntityId entity_id);
bool animation_is_done(EntityId entity_id);
void animation_is_loop_set(EntityId entity_id, bool is_loop);


#endif
