#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H


#include <stdbool.h>
#include "vector.h"
#include "log.h"
#include "sprite.h"


typedef size_t EntityId;
struct EntitySystem;


struct EntitySystem* entity_system_create();
void entity_system_init(struct EntitySystem* entity_system);
EntityId entity_system_create_entity(struct EntitySystem* entity_system);
void entity_system_delete_entity(
    struct EntitySystem* entity_system,
    EntityId entity_id
);
struct Vector entity_system_get_coordinates(
    struct EntitySystem* entity_system,
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


void sprite_component_setup(
    struct EntitySystem* entity_system,
    EntityId entity_id,
    enum SpriteId sprite_id
);
enum SpriteId sprite_component_get_sprite_id(struct EntitySystem* entity_system, EntityId entity_id);


#endif

