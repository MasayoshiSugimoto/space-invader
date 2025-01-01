#include "bullet_component.h"


#define UPDATE_RATE_MILLISECOND 100


struct BulletComponent {
  uint64_t timer_millisecond;
  bool active[ENTITY_MAX];
} bullet_component;


void bullet_component_init() {
  bullet_component.timer_millisecond = 0;
  for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    bullet_component.active[entity_id] = false;
  }
}


void bullet_component_fire(struct EntitySystem* entity_system, struct Vector bullet_position) {
  EntityId bullet_entity_id = entity_system_create_entity(entity_system);
  entity_system_set_coordinates(entity_system, bullet_entity_id, bullet_position);
  struct SpriteComponentUnit sprite_unit = sprite_component_get(bullet_entity_id);
  sprite_unit.sprite_id = SPRITE_ID_SPACESHIP_BULLET;
  sprite_unit.active = true;
  sprite_unit.sprite_buffer = sprite_loader_sprite_get(SPRITE_LOADER_FILE_NAME_SPACESHIP_BULLET);
  sprite_component_set(&sprite_unit);

  bullet_component.active[bullet_entity_id] = true;

  faction_component_set(bullet_entity_id, FACTION_ID_PLAYER);
}


void bullet_component_setup(struct EntitySystem* entity_system, EntityId entity_id) {
  assert_entity_id(entity_id);
  bullet_component.active[entity_id] = true;
}


void bullet_component_update(struct EntitySystem* entity_system, uint64_t delta_time_millisecond) {
  bullet_component.timer_millisecond += delta_time_millisecond;
  if (bullet_component.timer_millisecond < UPDATE_RATE_MILLISECOND) return;
  bullet_component.timer_millisecond = 0;

  struct Vector v = {0, -1};

  for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!bullet_component.active[entity_id]) continue;
    entity_system_add_coordinates(entity_system, entity_id, v);
  }
}


void bullet_component_cleanup(struct EntitySystem* entity_system) {
  for (int entity_id = 0; entity_id < ENTITY_MAX; entity_id++) {
    if (!bullet_component.active[entity_id]) continue;
    if (entity_system_get_coordinates(entity_system, entity_id).y >= 0) continue;
    component_manager_cleanup(entity_system, entity_id);
  }
}


void bullet_component_disable(struct EntitySystem* entity_system, EntityId entity_id) {
  assert_entity_id(entity_id);
  bullet_component.active[entity_id] = false;
}
