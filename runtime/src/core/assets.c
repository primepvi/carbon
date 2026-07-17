#include <cb_runtime/core/assets.h>
#include <cb_runtime/core/runtime.h>
#include <stdlib.h>

Assets *assets_new(void) {
  Assets *assets = malloc(sizeof(Assets));

  assets->textures = array_list_new(128, sizeof(Texture));
  assets->scripts = array_list_new(128, sizeof(Script));
  assets->sprites = array_list_new(128, sizeof(Sprite));
  assets->transforms = array_list_new(128, sizeof(Transform));
  assets->colliders = array_list_new(128, sizeof(Collider));

  assets->components = hashmap_new(128);

  Texture tex = texture_white_1x1();
  ComponentHandle tex_handle = array_list_push(assets->textures, &tex);
  hashmap_put(assets->components, "internal/1x1", sizeof(Component),
              &(Component){COMPONENT_TEXTURE, tex_handle});

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
  array_list_destroy(assets->transforms);
  array_list_destroy(assets->colliders);
  hashmap_destroy(assets->components);

  free(assets);
}

Component assets_load_texture(Assets *assets, const char *path,
                              const char *name) {

  Texture texture = texture_from_file(path, true);
  ComponentHandle texture_handle = array_list_push(assets->textures, &texture);
  Component texture_component = {COMPONENT_TEXTURE, texture_handle};
  hashmap_put(assets->components, name, sizeof(Component), &texture_component);

  return texture_component;
}

Component assets_load_script(Assets *assets, const char *path,
                             const char *name) {
  Script script = script_new(path, runtime_get_luavm());
  ComponentHandle script_handle = array_list_push(assets->scripts, &script);
  Component script_component = {COMPONENT_SCRIPT, script_handle};
  hashmap_put(assets->components, name, sizeof(Component), &script_component);

  return script_component;
}

Component assets_load_sprite(Assets *assets, Sprite sprite, const char *name) {
  ComponentHandle sprite_handle = array_list_push(assets->sprites, &sprite);
  Component sprite_component = {COMPONENT_SPRITE, sprite_handle};
  hashmap_put(assets->components, name, sizeof(Component), &sprite_component);

  return sprite_component;
}

Component assets_load_transform(Assets *assets, Transform transform,
                                const char *name) {
  ComponentHandle transform_handle =
      array_list_push(assets->transforms, &transform);
  Component transform_component = {COMPONENT_TRANSFORM, transform_handle};
  hashmap_put(assets->components, name, sizeof(Component),
              &transform_component);

  return transform_component;
}

Component assets_load_collider(Assets *assets, Collider collider,
                               const char *name) {
  ComponentHandle collider_handle =
      array_list_push(assets->colliders, &collider);
  Component collider_component = {COMPONENT_COLLIDER, collider_handle};
  hashmap_put(assets->components, name, sizeof(Component), &collider_component);

  return collider_component;
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

Transform *assets_get_transform(Assets *assets, ComponentHandle handle) {
  return array_list_at(assets->transforms, handle);
}

Collider *assets_get_collider(Assets *assets, ComponentHandle handle) {
  return array_list_at(assets->colliders, handle);
}

ComponentHandle assets_get_component_handle(Assets *assets, ComponentKind kind,
                                            const char *name) {
  Component *component = hashmap_get(assets->components, name);
  if (component == NULL)
    return CB_INVALID_HANDLE;

  return component->kind == kind ? component->handle : CB_INVALID_HANDLE;
}

b8 assets_has_component(Assets *assets, ComponentKind kind, const char *name) {
  return assets_get_component_handle(assets, kind, name) != CB_INVALID_HANDLE;
}
