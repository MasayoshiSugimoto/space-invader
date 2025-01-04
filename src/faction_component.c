#include "faction_component.h"


struct FactionComponent {
    bool active[ENTITY_MAX];
    enum FactionId faction_map[ENTITY_MAX];
} faction_component;


void faction_component_set(EntityId entity_id, enum FactionId faction_id) {
  faction_component.active[entity_id] = true;
  faction_component.faction_map[entity_id] = faction_id;
}


bool faction_component_is_enemy(EntityId entity_id_1, EntityId entity_id_2) {
  if (!faction_component.active[entity_id_1] || !faction_component.active[entity_id_2]) return false;
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


void faction_component_disable(EntityId entity_id) {
  faction_component.active[entity_id] = false;
}


enum FactionId faction_component_faction_id_get(EntityId entity_id) {
  assert_entity_id(entity_id);
  return faction_component.faction_map[entity_id];
}