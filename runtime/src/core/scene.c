#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/scene.h>

#include <stdlib.h>
#include <string.h>

Scene *scene_new(const char *name) {
  Scene *scene = malloc(sizeof(Scene));
  scene->name = strdup(name);
  scene->root = node_new(NULL, "Root");
  scene->sprites = array_list_new(32, sizeof(Sprite));

  return scene;
}

void scene_destroy(Scene *scene) {
  free(scene->name);
  node_destroy(scene->root);
  array_list_destroy(scene->sprites);
}

void scene_render(Scene *scene, Renderer *renderer) {
  ArrayList *objects = scene->root->childrens;
  for (u32 i = 0; i < array_list_length(objects); i++) {
    Node *node = array_list_at(objects, i);
    if (node == NULL)
      continue;

    ArrayList *node_components = node->components;
    ComponentHandle node_sprite_handle = array_list_find_index(
        node_components, sprite_component_kind_comparator, NULL);
    if ((i32)node_sprite_handle == -1)
      continue;

    Sprite *node_sprite = array_list_at(scene->sprites, node_sprite_handle);
    if (node_sprite->texture == NULL) {
      renderer_draw_quad(renderer, node_sprite->position, node_sprite->scale,
                         node_sprite->color);
    } else {
      renderer_draw_texture(renderer, node_sprite->position, node_sprite->scale,
                            node_sprite->texture);
    }
  }
}

void scene_append_node(Scene *scene, Node *node) {
  node->parent = scene->root;
  node_push_children(scene->root, node);
}

ComponentHandle scene_register_sprite(Scene *scene, Sprite *sprite) {
  return (ComponentHandle)array_list_push(scene->sprites, sprite);
}
