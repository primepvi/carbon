#include "cb_runtime/bindings/lua_node.h"
#include <cb_engine/core/logger.h>
#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/runtime.h>
#include <cb_runtime/core/scene.h>

#include <cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *read_scene_json_file(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    CB_ERROR("Cannot open scene file at: '%s'", path);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  u32 len = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(len + 1);
  if (buffer == NULL) {
    CB_ERROR("Cannot allocate buffer to read scene source.");
    return NULL;
  }

  fread(buffer, 1, len, file);
  fclose(file);

  buffer[len] = '\0';

  return buffer;
}

Scene *scene_new(const char *name, Camera camera) {
  Scene *scene = malloc(sizeof(Scene));
  scene->name = strdup(name);
  scene->nodes = array_list_new(32, sizeof(Node));
  scene->root = node_new(SCENE_ROOT_NODE_HANDLE, "Root");
  array_list_push(scene->nodes, scene->root);

  scene->camera = camera;

  return scene;
}

void scene_destroy(Scene *scene) {
  free(scene->name);
  node_destroy(scene->root);
  array_list_destroy(scene->nodes);
}

Scene *scene_from_json(Assets *assets, Camera camera, const char *path) {
  const char *source = read_scene_json_file(path);
  cJSON *json = cJSON_Parse(source);

  cJSON *scene_name = cJSON_GetObjectItem(json, "name");
  cJSON *scene_nodes = cJSON_GetObjectItem(json, "nodes");

  Scene *scene = scene_new(scene_name->valuestring, camera);
  CB_INFO("Loading scene %s...", scene_name->valuestring);

  for (i32 i = 0; i < cJSON_GetArraySize(scene_nodes); i++) {
    cJSON *node = cJSON_GetArrayItem(scene_nodes, i);
    cJSON *node_name = cJSON_GetObjectItem(node, "name");
    cJSON *node_components = cJSON_GetObjectItem(node, "components");

    NodeHandle node_handle = scene_node_create(scene, node_name->valuestring);
    CB_INFO("Loading node %s...", node_name->valuestring);

    for (i32 j = 0; j < cJSON_GetArraySize(node_components); j++) {
      cJSON *node_component = cJSON_GetArrayItem(node_components, j);
      cJSON *node_component_kind = cJSON_GetObjectItem(node_component, "kind");

      if (strcmp(node_component_kind->valuestring, "Transform") == 0) {
        cJSON *transform_name = cJSON_GetObjectItem(node_component, "name");
        cJSON *transform_position =
            cJSON_GetObjectItem(node_component, "position");
        cJSON *transform_scale = cJSON_GetObjectItem(node_component, "scale");

        f32 pos_x = cJSON_GetArrayItem(transform_position, 0)->valuedouble;
        f32 pos_y = cJSON_GetArrayItem(transform_position, 1)->valuedouble;
        Vec2 position = VEC2(pos_x, pos_y);

        f32 scale_x = cJSON_GetArrayItem(transform_scale, 0)->valuedouble;
        f32 scale_y = cJSON_GetArrayItem(transform_scale, 1)->valuedouble;
        Vec2 scale = VEC2(scale_x, scale_y);

        Transform transform = transform_create(position, scale);
        Component transform_component = assets_load_transform(
            assets, transform, transform_name->valuestring);
        scene_node_attach_component(scene, node_handle, transform_component);

        CB_INFO("Node %s transform component %s has been loaded.",
                node_name->valuestring, transform_name->valuestring);
      } else if (strcmp(node_component_kind->valuestring, "Sprite") == 0) {
        cJSON *sprite_name = cJSON_GetObjectItem(node_component, "name");
        cJSON *sprite_texture = cJSON_GetObjectItem(node_component, "texture");
        cJSON *sprite_color = cJSON_GetObjectItem(node_component, "color");
        cJSON *sprite_flip = cJSON_GetObjectItem(node_component, "flip");

        f32 color_r = cJSON_GetArrayItem(sprite_color, 0)->valuedouble;
        f32 color_g = cJSON_GetArrayItem(sprite_color, 1)->valuedouble;
        f32 color_b = cJSON_GetArrayItem(sprite_color, 2)->valuedouble;
        f32 color_a = cJSON_GetArrayItem(sprite_color, 3)->valuedouble;
        Color color = RGBA(color_r, color_g, color_b, color_a);

        b8 flip_x = cJSON_GetArrayItem(sprite_flip, 0)->valueint;
        b8 flip_y = cJSON_GetArrayItem(sprite_flip, 1)->valueint;

        ComponentHandle texture_handle = assets_get_component_handle(
            assets, COMPONENT_TEXTURE, sprite_texture->valuestring);
        Component texture_component = assets_load_sprite(
            assets, sprite_create(texture_handle, color, flip_x, flip_y),
            sprite_name->valuestring);
        scene_node_attach_component(scene, node_handle, texture_component);

        CB_INFO("Node %s sprite component %s has been loaded.",
                node_name->valuestring, sprite_name->valuestring);
      } else if (strcmp(node_component_kind->valuestring, "Script") == 0) {
        cJSON *script_name = cJSON_GetObjectItem(node_component, "name");
        cJSON *script_path = cJSON_GetObjectItem(node_component, "path");

        Component script_component = assets_load_script(
            assets, script_path->valuestring, script_name->valuestring);
        scene_node_attach_component(scene, node_handle, script_component);

        CB_INFO("Node %s script component %s has been loaded.",
                node_name->valuestring, script_name->valuestring);
      } else if (strcmp(node_component_kind->valuestring, "Collider") == 0) {
        cJSON *collider_name = cJSON_GetObjectItem(node_component, "name");
        cJSON *collider_size = cJSON_GetObjectItem(node_component, "scale");
        cJSON *collider_is_trigger =
            cJSON_GetObjectItem(node_component, "isTrigger");

        f32 size_x = cJSON_GetArrayItem(collider_size, 0)->valuedouble;
        f32 size_y = cJSON_GetArrayItem(collider_size, 1)->valuedouble;
        Vec2 size = VEC2(size_x, size_y);

        Component collider_component = assets_load_collider(
            assets, collider_create(size, collider_is_trigger->valueint),
            collider_name->valuestring);
        scene_node_attach_component(scene, node_handle, collider_component);

        CB_INFO("Node %s collider component %s has been loaded.",
                node_name->valuestring, collider_name->valuestring);
      }

      CB_INFO("Node %s has been loaded.", node_name->valuestring);
    }
  }

  return scene;
}

void scene_update(Scene *scene) {
  ArrayList *handles = scene->root->childrens;

  for (u32 i = 0; i < array_list_length(handles); i++) {
    NodeHandle curr_handle = *(NodeHandle *)array_list_at(handles, i);
    if (curr_handle == CB_INVALID_HANDLE) {
      CB_ERROR("Invalid node handle found during %s update.", scene->name);
      continue;
    }

    Node *curr_node = array_list_at(scene->nodes, curr_handle);
    if (curr_node == NULL) {
      CB_ERROR("Cannot find node with handle %d during %s update.", curr_handle,
               scene->name);
      continue;
    }

    Component *script_component = array_list_find(
        curr_node->components, script_component_kind_comparator);
    if (script_component == NULL)
      continue;

    Assets *assets = runtime_get_assets();
    Script *script = assets_get_script(assets, script_component->handle);
    if (script == NULL) {
      CB_ERROR("Cannot find script with handle %d of node %s during %s update.",
               script_component->handle, curr_node->name, scene->name);
      continue;
    }

    Application *app = runtime_get_application();

    lua_State *L = runtime_get_luavm();
    lua_rawgeti(L, LUA_REGISTRYINDEX, script->ref);
    lua_getfield(L, -1, "Update");

    if (!lua_isfunction(L, -1)) {
      lua_pop(L, 2);
      CB_DEBUG("Script in %s dont have an update function.", script->path);
      continue;
    }

    lua_newtable(L);
    lua_push_node(L, curr_node);
    lua_setfield(L, -2, "Node");
    lua_pushnumber(L, application_delta_time(app));

    if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
      const char *error = lua_tostring(L, -1);
      CB_ERROR("Lua Error\n Script Path: %s\n Error: %s", script->path, error);
      lua_pop(L, 1);
    }

    lua_pop(L, 1);
  }
}

void scene_physics_update(Scene *scene) {
  ArrayList *handles = scene->root->childrens;

  for (u32 i = 0; i < array_list_length(handles); i++) {
    NodeHandle curr_handle = *(NodeHandle *)array_list_at(handles, i);
    if (curr_handle == CB_INVALID_HANDLE) {
      CB_ERROR("Invalid node handle found during %s physics update.",
               scene->name);
      continue;
    }

    Node *curr_node = array_list_at(scene->nodes, curr_handle);
    if (curr_node == NULL) {
      CB_ERROR("Cannot find node with handle %d during %s physics update.",
               curr_handle, scene->name);
      continue;
    }

    Component *transform_component = array_list_find(
        curr_node->components, transform_component_kind_comparator);
    if (transform_component == NULL)
      continue;

    Assets *assets = runtime_get_assets();

    Transform *transform =
        assets_get_transform(assets, transform_component->handle);
    if (transform == NULL) {
      CB_ERROR("Cannot find transform with handle %d of node %s during %s "
               "physics update.",
               transform_component->handle, curr_node->name, scene->name);
      continue;
    }

    Component *collider_component = array_list_find(
        curr_node->components, collider_component_kind_comparator);
    if (collider_component == NULL)
      continue;

    Collider *collider =
        assets_get_collider(assets, collider_component->handle);
    if (collider == NULL) {
      CB_ERROR("Cannot find collider with handle %d of node %s during %s "
               "physics update.",
               transform_component->handle, curr_node->name, scene->name);
      continue;
    }

    Rect collider_bounds = collider_world_bounds(collider, transform->scale);
  }
}

void scene_draw(Scene *scene, Renderer *renderer) {
  ArrayList *handles = scene->root->childrens;

  renderer_set_projection(renderer, scene->camera.projection);
  renderer_set_view(renderer, scene->camera.view);

  for (u32 i = 0; i < array_list_length(handles); i++) {
    NodeHandle curr_handle = *(NodeHandle *)array_list_at(handles, i);
    if (curr_handle == CB_INVALID_HANDLE) {
      CB_ERROR("Invalid node handle found during %s draw.", scene->name);
      continue;
    }

    Node *curr_node = array_list_at(scene->nodes, curr_handle);
    if (curr_node == NULL) {
      CB_ERROR("Cannot find node with handle %d during %s draw.", curr_handle,
               scene->name);
      continue;
    }

    Component *sprite_component = array_list_find(
        curr_node->components, sprite_component_kind_comparator);
    if (sprite_component == NULL)
      continue;

    Component *transform_component = array_list_find(
        curr_node->components, transform_component_kind_comparator);
    if (transform_component == NULL)
      continue;

    Assets *assets = runtime_get_assets();
    Sprite *sprite = assets_get_sprite(assets, sprite_component->handle);
    if (sprite == NULL) {
      CB_ERROR("Cannot find sprite with handle %d of node %s during %s draw.",
               sprite_component->handle, curr_node->name, scene->name);
      continue;
    }

    Transform *transform =
        assets_get_transform(assets, transform_component->handle);
    if (transform == NULL) {
      CB_ERROR(
          "Cannot find transform with handle %d of node %s during %s draw.",
          transform_component->handle, curr_node->name, scene->name);
      continue;
    }

    Texture *texture = assets_get_texture(assets, sprite->texture_handle);
    renderer_draw_texture(renderer, transform->position, transform->scale,
                          texture, sprite->color);
  }
}

Node *scene_get_node(Scene *scene, NodeHandle handle) {
  return handle == CB_INVALID_HANDLE ? NULL
                                     : array_list_at(scene->nodes, handle);
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
                                 Component component) {
  Node *node = array_list_at(scene->nodes, node_handle);
  array_list_push(node->components, &component);
}
