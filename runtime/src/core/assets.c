#include <cb_runtime/core/assets.h>
#include <cb_runtime/core/runtime.h>
#include <stdlib.h>

Assets *assets_new(void) {
  Assets *assets = malloc(sizeof(Assets));

  assets->textures = array_list_new(128, sizeof(Texture));
  assets->textures_handles = hashmap_new(128);

  assets->scripts = array_list_new(128, sizeof(Script));
  assets->scripts_handles = hashmap_new(128);

  assets->sprites = array_list_new(128, sizeof(Sprite));
  assets->sprites_handles = hashmap_new(128);

  return assets;
}

void assets_destroy(Assets *assets) {
  for (u32 i = 0; i < array_list_length(assets->textures); i++) {
    Texture *texture = array_list_at(assets->textures, i);
    if (texture != NULL)
      texture_free(texture);
  }

  for (u32 i = 0; i < array_list_length(assets->scripts); i++) {
    Script *script = array_list_at(assets->scripts, i);
    if (script != NULL)
      script_destroy(script, runtime_get_luavm());
  }

  array_list_destroy(assets->textures);
  array_list_destroy(assets->scripts);
  array_list_destroy(assets->sprites);

  hashmap_destroy(assets->textures_handles);
  hashmap_destroy(assets->scripts_handles);
  hashmap_destroy(assets->sprites_handles);

  free(assets);
}

Component assets_load_texture(Assets *assets, const char *path,
                              const char *name) {

  Texture texture = texture_from_file(path, true);
  ComponentHandle texture_handle = array_list_push(assets->textures, &texture);
  Component texture_component = {COMPONENT_TEXTURE, texture_handle};
  hashmap_put(assets->textures_handles, name, sizeof(ComponentHandle),
              &texture_handle);

  return texture_component;
}

Component assets_load_script(Assets *assets, const char *path,
                             const char *name) {
  Script script = script_new(path, runtime_get_luavm());
  ComponentHandle script_handle = array_list_push(assets->scripts, &script);
  Component script_component = {COMPONENT_SCRIPT, script_handle};
  hashmap_put(assets->scripts_handles, name, sizeof(ComponentHandle),
              &script_handle);

  return script_component;
}

Component assets_load_sprite(Assets *assets, Sprite sprite, const char *name) {
  ComponentHandle sprite_handle = array_list_push(assets->sprites, &sprite);
  Component sprite_component = {COMPONENT_SPRITE, sprite_handle};
  hashmap_put(assets->sprites_handles, name, sizeof(ComponentHandle),
              &sprite_handle);

  return sprite_component;
}

Texture *assets_get_texture(Assets *assets, ComponentHandle handle) {
  return array_list_at(assets->textures, handle);
}

Script *assets_get_script(Assets *assets, ComponentHandle handle) {
  return array_list_at(assets->scripts, handle);
}

Sprite *assets_get_sprite(Assets *assets, ComponentHandle handle) {
  return array_list_at(assets->sprites, handle);
}

ComponentHandle assets_get_component_handle(Assets *assets, ComponentKind kind,
                                            const char *name) {
  ComponentHandle *handle;

  switch (kind) {
  case COMPONENT_TEXTURE:
    handle = hashmap_get(assets->textures_handles, name);
    break;
  case COMPONENT_SCRIPT:
    handle = hashmap_get(assets->scripts_handles, name);
    break;
  case COMPONENT_SPRITE:
    handle = hashmap_get(assets->sprites_handles, name);
    break;
  default:
    handle = NULL;
  }

  return handle == NULL ? CB_INVALID_HANDLE : *handle;
}

b8 assets_has_component(Assets *assets, ComponentKind kind, const char *name) {
  ComponentHandle *handle;

  switch (kind) {
  case COMPONENT_TEXTURE:
    handle = hashmap_get(assets->textures_handles, name);
    break;
  case COMPONENT_SCRIPT:
    handle = hashmap_get(assets->scripts_handles, name);
    break;
  case COMPONENT_SPRITE:
    handle = hashmap_get(assets->sprites_handles, name);
    break;
  default:
    handle = NULL;
  }

  return handle == NULL ? false : true;
}
