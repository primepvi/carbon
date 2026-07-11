#include <cb_runtime/core/assets.h>
#include <stdlib.h>

Assets *assets_new(void) {
  Assets *assets = malloc(sizeof(Assets));
  assets->textures = hashmap_new(128);
  return assets;
}

void assets_destroy(Assets *assets) {
  hashmap_destroy(assets->textures);
  free(assets);
}

Texture *assets_load_texture(Assets *assets, const char *path,
                             const char *name) {

  Texture *texture = malloc(sizeof(Texture));
  *texture = texture_from_file(path, true);

  hashmap_put(assets->textures, name, texture);
  return texture;
}

Texture *assets_get_texture(Assets *assets, const char *name) {
  return (Texture *)hashmap_get(assets->textures, name);
}

b8 assets_has_texture(Assets *assets, const char *name) {
  return hashmap_has(assets->textures, name);
}
