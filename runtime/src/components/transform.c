#include <cb_runtime/components/transform.h>
#include <cb_runtime/components/component.h>

Transform transform_create(Vec2 position, Vec2 scale) {
  return (Transform){.position = position, .scale = scale};
}

b8 transform_component_kind_comparator(void *current) {
  return ((Component *)current)->kind == COMPONENT_TRANSFORM;
}
