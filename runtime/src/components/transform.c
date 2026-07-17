#include <cb_runtime/components/component.h>
#include <cb_runtime/components/transform.h>

Transform transform_create(Vec2 position, Vec2 scale) {
  return (Transform){
      .position = position, .previous_position = position, .scale = scale};
}

b8 transform_component_kind_comparator(void *current) {
  return ((Component *)current)->kind == COMPONENT_TRANSFORM;
}
