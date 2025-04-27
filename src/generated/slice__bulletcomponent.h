#ifndef SLICE__BULLETCOMPONENT__H
#define SLICE__BULLETCOMPONENT__H


#include "../log.h"
#include <stdint.h>
#include "../bullet_component_struct.h"


struct SLICE__BulletComponent {
    struct BulletComponent* data;
    uint32_t length;
};


void SLICE__BulletComponent__init(struct SLICE__BulletComponent* slice);
struct BulletComponent* SLICE__BulletComponent__get(struct SLICE__BulletComponent* slice, uint32_t index);


#endif
