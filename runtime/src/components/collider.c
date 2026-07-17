#include <cb_runtime/components/component.h>
#include <cb_runtime/components/collider.h>

Collider collider_create(Vec2 size, b8 is_trigger) {
  return (Collider){.bounds = RECT(0, 0, size.x, size.y),
                    .is_trigger = is_trigger};
}

Rect collider_world_bounds(Collider *collider, Vec2 position) {
  Rect result = collider->bounds;
  result.position = vec2_add(result.position, position);
  return result;
}

b8 collider_component_kind_comparator(void *current) {
 return ((Component *)current)->kind == COMPONENT_COLLIDER;
}
