#include "cb_engine/core/logger.h"
#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/scene.h>

#include <stdlib.h>
#include <string.h>

Scene *scene_new(const char *name) {
  Scene *scene = malloc(sizeof(Scene));
  scene->name = strdup(name);
  scene->nodes = array_list_new(32, sizeof(Node));
  scene->sprites = array_list_new(32, sizeof(Sprite));

  scene->root = node_new(SCENE_ROOT_NODE_HANDLE, "Root");
  array_list_push(scene->nodes, scene->root);

  return scene;
}

void scene_destroy(Scene *scene) {
  free(scene->name);

  node_destroy(scene->root);

  array_list_destroy(scene->nodes);
  array_list_destroy(scene->sprites);
}

void scene_render(Scene *scene, Renderer *renderer) {
  ArrayList *handles = scene->root->childrens;

  for (u32 i = 0; i < array_list_length(handles); i++) {
    NodeHandle curr_handle = *(NodeHandle *)array_list_at(handles, i);
    if (curr_handle == CB_INVALID_HANDLE) {
      CB_ERROR("Invalid node handle found during %s render.", scene->name);
      continue;
    }

    Node *curr_node = array_list_at(scene->nodes, curr_handle);
    if (curr_node == NULL) {
      CB_ERROR("Cannot find node with handle %d during %s render.", curr_handle,
               scene->name);
      continue;
    }

    Component *sprite_component = array_list_find(
        curr_node->components, sprite_component_kind_comparator);
    if (sprite_component == NULL)
      continue;

    Sprite *sprite = array_list_at(scene->sprites, sprite_component->handle);
    if (sprite == NULL) {
      CB_ERROR("Cannot find sprite with handle %d of node %s during %s render.",
               sprite_component->handle, curr_node->name, scene->name);
      continue;
    }

    if (sprite->texture == NULL)
      renderer_draw_quad(renderer, sprite->position, sprite->scale,
                         sprite->color);
    else
      renderer_draw_texture(renderer, sprite->position, sprite->scale,
                            sprite->texture);
  }
}

Component scene_create_component(Scene *scene, ComponentKind kind, void *data) {
  ComponentHandle handle;

  switch (kind) {
  case COMPONENT_SPRITE: {
    handle = array_list_push(scene->sprites, data);
    break;
  }
  default:
    handle = CB_INVALID_HANDLE;
  }

  return (Component){kind, handle};
}

NodeHandle scene_find_node(Scene *scene, const char *name) {
  ArrayList *handles = scene->root->childrens;
  NodeHandle handle = CB_INVALID_HANDLE;

  for (u32 i = 0; array_list_length(handles); i++) {
    NodeHandle curr_handle = *(NodeHandle *)array_list_at(handles, i);
    if (curr_handle == CB_INVALID_HANDLE)
      continue;

    Node *curr_node = array_list_at(scene->nodes, curr_handle);
    if (curr_node == NULL)
      continue;

    if (strcmp(curr_node->name, name) == 0) {
      handle = curr_handle;
      break;
    }
  }

  return handle;
}

NodeHandle scene_node_create(Scene *scene, const char *name) {
  Node *node = node_new(SCENE_ROOT_NODE_HANDLE, name);
  NodeHandle handle = array_list_push(scene->nodes, node);
  array_list_push(scene->root->childrens, &handle);

  // destroying source
  free(node);

  return handle;
}

NodeHandle scene_node_find_child(Scene *scene, NodeHandle parent_handle,
                                 const char *name) {
  Node *parent = array_list_at(scene->nodes, parent_handle);
  ArrayList *parent_handles = parent->childrens;
  NodeHandle handle = CB_INVALID_HANDLE;

  for (u32 i = 0; array_list_length(parent_handles); i++) {
    NodeHandle curr_handle = *(NodeHandle *)array_list_at(parent_handles, i);
    if (curr_handle == CB_INVALID_HANDLE)
      continue;

    Node *curr_node = array_list_at(scene->nodes, curr_handle);
    if (curr_node == NULL)
      continue;

    if (strcmp(curr_node->name, name) == 0) {
      handle = curr_handle;
      break;
    }
  }

  return handle;
}

void scene_node_attach_component(Scene *scene, NodeHandle node_handle,
                                 Component *component) {
  Node *node = array_list_at(scene->nodes, node_handle);
  array_list_push(node->components, component);
}
