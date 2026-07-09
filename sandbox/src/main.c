#include <core/engine.h>
#include <core/gl/shader.h>
#include <core/logger.h>

#include <platform/platform.h>
#include <renderer/renderer.h>
#include <renderer/renderer_context.h>

void update(Engine *engine) {}
void draw(Engine *engine) {
  renderer_prepare(engine->renderer);

  renderer_draw_quad(engine->renderer, VEC2(400.0f, 0.0f), VEC2(100, 100),
                     COLOR_RED);
  renderer_draw_quad(engine->renderer, VEC2(100.0f, 0.0f), VEC2(100, 100),
                     COLOR_GREEN);

  renderer_flush(engine->renderer);
}

int main(void) {
  Engine engine = engine_new((EngineConfig){.window_width = 800,
                                            .window_height = 600,
                                            .window_title = "Carbon",
                                            .update_callback = update,
                                            .draw_callback = draw});

  engine_init(&engine);

  Shader shader =
      shader_from_files("assets/shaders/main.vert", "assets/shaders/main.frag");

  engine_run(&engine, shader);
  engine_destroy(&engine);

  return 0;
}
