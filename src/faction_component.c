#include "faction_component.h"


struct FactionComponent {
    enum FactionId faction_map[ENTITY_MAX];
} faction_component;


void faction_component_set(EntityId entity_id, enum FactionId faction_id) {
  faction_component.faction_map[entity_id] = faction_id;
}


bool faction_component_is_enemy(EntityId entity_id_1, EntityId entity_id_2) {
  if (!entity_system_component_is_active(entity_id_1, COMPONENT_ID_FACTION)) return false;
  if (!entity_system_component_is_active(entity_id_2, COMPONENT_ID_FACTION)) return false;
  if (
      faction_component.faction_map[entity_id_1] == FACTION_ID_PLAYER
      && faction_component.faction_map[entity_id_2] == FACTION_ID_ALIEN
  ) return true;
  if (
      faction_component.faction_map[entity_id_2] == FACTION_ID_PLAYER 
      && faction_component.faction_map[entity_id_1] == FACTION_ID_ALIEN
  ) return true;
  return false;
}


void faction_component_enable(EntityId entity_id) {
  entity_system_component_activate(entity_id, COMPONENT_ID_FACTION);
}


void faction_component_disable(EntityId entity_id) {
  entity_system_component_deactivate(entity_id, COMPONENT_ID_FACTION);
}


bool faction_component_is_enabled(EntityId entity_id) {
  return entity_system_component_is_active(entity_id, COMPONENT_ID_FACTION);
}


enum FactionId faction_component_faction_id_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  return faction_component.faction_map[entity_id];
}