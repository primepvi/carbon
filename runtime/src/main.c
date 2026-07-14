#include <cb_engine/core/application.h>
#include <cb_runtime/components/sprite.h>
#include <cb_runtime/core/assets.h>
#include <cb_runtime/core/node.h>
#include <cb_runtime/core/runtime.h>
#include <cb_runtime/core/scene.h>

int main(void) {
  ApplicationConfig app_config = {
      .window_width = 800, .window_height = 600, .window_title = "Carbon"};

  Application app = application_new(app_config);
  application_init(&app);

  runtime_init(&app, "Main");

  Assets *assets = runtime_get_assets();
  Scene *scene = runtime_get_scene();

  Component player_texture =
      assets_load_texture(assets, "assets/sprites/mario.png", "player_texture");
  Component player_script =
      assets_load_script(assets, "assets/scripts/player.lua", "player_script");
  Component player_sprite =
      assets_load_sprite(assets,
                         sprite_with_texture(player_texture.handle,
                                             VEC2(100, 100), VEC2(100, 100)),
                         "player_sprite");

  NodeHandle player_node = scene_node_create(scene, "Player");
  scene_node_attach_component(scene, player_node, player_sprite);
  scene_node_attach_component(scene, player_node, player_script);

  while (!application_should_close(&app)) {
    application_begin_frame(&app);
    runtime_run();
    application_end_frame(&app);
  }

  application_destroy(&app);
  assets_destroy(assets);

  return 0;
}
