#include <core/engine.h>
#include <core/logger.h>
#include <platform/platform.h>
#include <renderer/renderer_context.h>

void update(void) {}
void draw(void) {}

int main(void) {
  Platform *platform = platform_new(800, 600, "Carbon");
  RendererContext *ctx = renderer_context_new();

  engine_init(platform, ctx);
  engine_run(update, draw);

  renderer_context_destroy(ctx);
  platform_destroy(platform);

  CB_INFO("Engine Shutdown");

  return 0;
}
