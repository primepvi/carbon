#include "cb_runtime/components/component.h"
#include <cb_runtime/components/sprite.h>

Sprite sprite_create(ComponentHandle texture_handle, Color color, b8 flip_x, b8 flip_y) {
  return (Sprite){
      .texture_handle = texture_handle,
      .color = color,
      .flip_x = flip_x,
      .flip_y = flip_y,
  };
}

void sprite_flip_horizontal(Sprite *sprite) {
  sprite->flip_x = !sprite->flip_x;
}

void sprite_flip_vertical(Sprite *sprite) { sprite->flip_y = !sprite->flip_y; }

b8 sprite_component_kind_comparator(void *current) {
  return ((Component *)current)->kind == COMPONENT_SPRITE;
};
