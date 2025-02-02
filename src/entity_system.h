#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H


#include <stdint.h>
#include <stdbool.h>
#include "vector.h"
#include "log.h"
#include "array_bit.h"


#define ENTITY_MAX 100
#define ENTITY_ID_INVALID ENTITY_MAX


#define assert_entity_id(entity_id) { \
  if (entity_id >= ENTITY_MAX) log_fatal_f("Invalid entity id: %ld", entity_id); \
}


typedef size_t EntityId;


enum ComponentId {
    COMPONENT_ID_MASTER,
    COMPONENT_ID_SPRITE,
    COMPONENT_ID_ANIMATION,
    COMPONENT_ID_BASIC_AI,
    COMPONENT_ID_BULLET,
    COMPONENT_ID_MAX
};


struct Entity {
  EntityId entity_id;
  struct Vector coordinates;
};


void entity_system_init(void);
EntityId entity_system_create_entity(void);
void entity_system_delete_entity(EntityId entity_id);
struct Vector entity_system_get_coordinates(EntityId entity_id);
void entity_system_set_coordinates(EntityId entity_id, struct Vector coordinates);
void entity_system_add_coordinates(EntityId entity_id, struct Vector delta);
void entity_system_disable(EntityId entity_id);
void entity_system_enable(EntityId entity_id);
bool entity_system_is_active(EntityId entity_id);
void entity_system_set_friendly_id(EntityId entity_id, uint16_t friendly_id);
uint16_t entity_system_get_friendly_id(EntityId entity_id);
EntityId entity_system_get_by_friendly_id(uint16_t friendly_id);
void entity_system_active_flags_reset_all(void);
bool entity_system_component_is_active(EntityId entity_id, enum ComponentId component_id);
void entity_system_component_activate(EntityId entity_id, enum ComponentId component_id);
void entity_system_component_deactivate(EntityId entity_id, enum ComponentId component_id);
void entity_system_component_active_flags_reset(EntityId entity_id);


#endif

