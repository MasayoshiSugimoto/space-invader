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
#include "window_manager_2.h"


void bullet_component_init(void);
void bullet_component_setup(void);
void bullet_component_fire(struct Vector bullet_position);
void bullet_component_update(void);
void bullet_component_cleanup(void);
void bullet_component_disable(EntityId entity_id);


#endif
