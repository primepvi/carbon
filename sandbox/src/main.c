#include <core/engine.h>
#include <core/gl/shader.h>
#include <core/logger.h>

#include <platform/platform.h>
#include <renderer/renderer.h>
#include <renderer/renderer_context.h>

Renderer *renderer;

void update(void) {}

void draw(void) {
  renderer_begin(renderer);
  renderer_draw_quad(renderer, VEC2_ZERO, VEC2(30, 30), COLOR_RED);
  renderer_end(renderer);
}

int main(void) {
  Platform *platform = platform_new(800, 600, "Carbon");
  RendererContext *ctx = renderer_context_new();

  engine_init(platform, ctx);

  renderer = renderer_new();

  Shader shader =
      shader_from_files("assets/shaders/main.vert", "assets/shaders/main.frag");
  shader_bind(shader);
  shader_uniform_mat4(shader, "u_model", mat4_identity());
  shader_uniform_mat4(shader, "u_view", mat4_identity());
  shader_uniform_mat4(shader, "u_proj", mat4_ortho(0, 800, 600, 0));

  engine_run(update, draw);

  renderer_context_destroy(ctx);
  platform_destroy(platform);

  CB_INFO("Engine Shutdown");

  return 0;
}
