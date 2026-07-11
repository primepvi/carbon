#include <core/application.h>
#include <renderer/renderer.h>

void update(void) {}
void draw(Renderer *renderer) {
  renderer_draw_sprite(renderer, VEC2(400.0f, 0.0f), VEC2(100, 100), "mario");
  renderer_draw_quad(renderer, VEC2(200.0f, 0.0f), VEC2(25, 25), COLOR_RED);
}

int main(void) {
  ApplicationConfig app_config = {.window_width = 800,
                                  .window_height = 600,
                                  .window_title = "Carbon",
                                  .update = update,
                                  .draw = draw};

  Application app = application_new(app_config);
  application_init(&app);
  application_load_texture(&app, "assets/sprites/mario.png", "mario");
  
  application_run(&app);
  application_destroy(&app);

  return 0;
}
