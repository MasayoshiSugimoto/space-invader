#ifndef FACTION_COMPONENT_H
#define FACTION_COMPONENT_H


#include <stdbool.h>
#include "entity_system.h"


enum FactionId {
  FACTION_ID_NEUTRAL,
  FACTION_ID_PLAYER,
  FACTION_ID_ALIEN, 
  FACTION_ID_MAX
};


void faction_component_set(EntityId entity_id, enum FactionId faction_id);
bool faction_component_is_enemy(EntityId entity_id_1, EntityId entity_id_2);
void faction_component_disable(EntityId entity_id);


#endif
