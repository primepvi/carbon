#ifndef CB_COLLIDER_H
#define CB_COLLIDER_H

#include <cb_engine/math/rect.h>

typedef struct {
  Rect bounds;
  b8 is_trigger;
} Collider;

CB_API Collider collider_create(Vec2 size, b8 is_trigger);
CB_API Rect collider_world_bounds(Collider *collider, Vec2 position);

b8 collider_component_kind_comparator(void *current);
#endif
