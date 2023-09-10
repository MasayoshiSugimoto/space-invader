#include "component_manager.h"


void component_manager_cleanup(struct EntitySystem* entity_system, EntityId entity_id) {
  assert_entity_id(entity_id);
  if (!entity_system->active[entity_id]) return;

  entity_system->active[entity_id] = false;

  bullet_component_disable(entity_system, entity_id);
  enemy_ai_basic_disable(entity_system, entity_id);
  sprite_component_disable(entity_id);
  faction_component_disable(entity_id);
}

