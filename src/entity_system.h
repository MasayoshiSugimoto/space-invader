#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H


#include <stdbool.h>
#include "vector.h"
#include "log.h"
#include "sprite.h"


#define ENTITY_MAX 100


#define assert_entity_id(entity_id) { \
  if (entity_id >= ENTITY_MAX) log_fatal_f("Invalid entity id: %ld", entity_id); \
}


typedef size_t EntityId;


struct Entity {
  EntityId entity_id;
  struct Vector coordinates;
};


struct EntitySystem {
  EntityId next_entity;
  bool active[ENTITY_MAX];
  struct Vector coordinates[ENTITY_MAX];
};


struct EntitySystem* entity_system_create();
void entity_system_init(struct EntitySystem* entity_system);
EntityId entity_system_create_entity(struct EntitySystem* entity_system);
void entity_system_delete_entity(
    struct EntitySystem* entity_system,
    EntityId entity_id
);
struct Vector entity_system_get_coordinates(
    const struct EntitySystem* entity_system,
    EntityId entity_id
);
void entity_system_set_coordinates(
    struct EntitySystem* entity_system,
    EntityId entity_id,
    struct Vector coordinates
);
void entity_system_add_coordinates(
    struct EntitySystem* entity_system,
    EntityId entity_id,
    struct Vector delta
);
void entity_system_disable(struct EntitySystem*, EntityId);


#endif

