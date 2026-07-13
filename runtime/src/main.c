#include <cb_engine/core/application.h>
#include <stdlib.h>

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

  Texture *player_texture =
      assets_load_texture(assets, "assets/sprites/mario.png", "player");
  Sprite *player_sprite =
      sprite_with_texture(player_texture, VEC2(100, 100), VEC2(100, 100));

  Scene *scene = scene_new("Main");
  ComponentHandle player_sprite_handle =
      scene_register_sprite(scene, player_sprite);

  Node *player_node = node_new(NULL, "player");
  node_push_component(player_node, COMPONENT_SPRITE, player_sprite_handle);
  scene_append_node(scene, player_node);

  while (!application_should_close(&app)) {
    application_begin_frame(&app);
    scene_render(scene, application_get_renderer(&app));
    application_end_frame(&app);
  }

  application_destroy(&app);

  return 0;
}
