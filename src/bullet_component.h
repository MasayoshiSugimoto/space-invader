#ifndef BULLET_COMPONENT_H
#define BULLET_COMPONENT_H


#include <stdint.h>
#include <stdbool.h>
#include "entity_system.h"
#include "sprite_component.h"
#include "faction_component.h"
#include "sprite_buffer.h"
#include "sprite_loader.h"
#include "recuring_frame_timer.h"
#include "game_screen.h"
#include "window_manager.h"
#include "collision_manager.h"
#include "bullet_component_struct.h"
#include "generated/slice__bulletcomponent.h"


void bullet_component_init(void);
void bullet_component_setup(void);
void bullet_component_fire(struct Vector bullet_position);
void bullet_component_fire_enemy(EntityId entity_id);
void bullet_component_update(void);
void bullet_component_cleanup(void);
void bullet_component_disable(EntityId entity_id);
bool bullet_component_is_active(EntityId entity_id);


#endif
