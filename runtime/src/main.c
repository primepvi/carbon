#include <cb_engine/core/application.h>
#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/assets.h>
#include <cb_runtime/core/node.h>
#include <cb_runtime/core/scene.h>

int main(void) {
  ApplicationConfig app_config = {
      .window_width = 800, .window_height = 600, .window_title = "Carbon"};

  Application app = application_new(app_config);
  application_init(&app);

  Assets *assets = assets_new();
  Scene *scene = scene_new("Main");

  Texture *player_texture =
      assets_load_texture(assets, "assets/sprites/mario.png", "player");
  Sprite player_sprite =
      sprite_with_texture(player_texture, VEC2(100, 100), VEC2(100, 100));
  Component player_sprite_component =
      scene_create_component(scene, COMPONENT_SPRITE, &player_sprite);
  NodeHandle player_node = scene_node_create(scene, "Player");
  scene_node_attach_component(scene, player_node, &player_sprite_component);

  while (!application_should_close(&app)) {
    application_begin_frame(&app);
    scene_render(scene, application_get_renderer(&app));
    application_end_frame(&app);
  }

  application_destroy(&app);
  assets_destroy(assets);

  return 0;
}
