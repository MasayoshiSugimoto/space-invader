#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H


#include <stdbool.h>
#include "vector.h"
#include "log.h"


#define ENTITY_MAX 100


#define assert_entity_id(entity_id) { \
  if (entity_id >= ENTITY_MAX) log_fatal_f("Invalid entity id: %ld", entity_id); \
}


typedef size_t EntityId;


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
bool entity_system_is_active(EntityId entity_id);


#endif

