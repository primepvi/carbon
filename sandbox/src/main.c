#include "core/logger.h"
#include <core/application.h>
#include <core/input.h>

#include <renderer/renderer.h>

Application app;
Vec2 player_pos = VEC2(400.0f, 0.0f);

void update(f64 delta_time) {
  Vec2 movement = VEC2_ZERO;

  if (input_key_down(INPUT_KEY_W))
    movement.y -= 1.0f;
  if (input_key_down(INPUT_KEY_S))
    movement.y += 1.0f;
  if (input_key_down(INPUT_KEY_D))
    movement.x += 1.0f;
  if (input_key_down(INPUT_KEY_A))
    movement.x -= 1.0f;

  movement = vec2_normalize(movement);
  
  float speed = 200.0f;
  player_pos.x += movement.x * speed * delta_time;
  player_pos.y += movement.y * speed * delta_time;

  if (input_key_pressed(INPUT_KEY_ESCAPE))
    application_quit(&app);
}

void draw(Renderer *renderer) {
  renderer_draw_sprite(renderer, player_pos, VEC2(100, 100), "mario");
  renderer_draw_quad(renderer, VEC2(200.0f, 0.0f), VEC2(25, 25), COLOR_RED);
}

int main(void) {
  ApplicationConfig app_config = {.window_width = 800,
                                  .window_height = 600,
                                  .window_title = "Carbon",
                                  .update = update,
                                  .draw = draw};

  app = application_new(app_config);
  application_init(&app);
  application_load_texture(&app, "assets/sprites/mario.png", "mario");

  application_run(&app);
  application_destroy(&app);

  return 0;
}
