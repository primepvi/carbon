#include <core/engine.h>
#include <core/gl/shader.h>
#include <core/logger.h>

#include <platform/platform.h>
#include <renderer/renderer.h>
#include <renderer/renderer_context.h>

Renderer *renderer;

void update(void) {}

void draw(void) {
  renderer_prepare(renderer);

  renderer_draw_quad(renderer, VEC2(400.0f, 0.0f), VEC2(100, 100), COLOR_RED);
  renderer_draw_quad(renderer, VEC2(100.0f, 0.0f), VEC2(100, 100), COLOR_GREEN);
  
  renderer_flush(renderer);
}

int main(void) {
  Platform *platform = platform_new(800, 600, "Carbon");
  RendererContext *ctx = renderer_context_new();

  engine_init(platform, ctx);

  Shader shader =
      shader_from_files("assets/shaders/main.vert", "assets/shaders/main.frag");
  
  renderer = renderer_new(shader);
  engine_run(update, draw);

  renderer_context_destroy(ctx);
  platform_destroy(platform);

  CB_INFO("Engine Shutdown");

  return 0;
}
