#include "engine.h"
#include "core/logger.h"
#include "math/utils.h"
#include <stdlib.h>

Engine engine_new(EngineConfig config) {
  Platform *platform = platform_new(config.window_width, config.window_height,
                                    config.window_title);

  RendererContext *ctx = renderer_context_new();

  return (Engine){.config = config,
                  .ctx = ctx,
                  .platform = platform,
                  .running = false,
                  .renderer = NULL};
}

void engine_destroy(Engine *engine) {
  renderer_context_destroy(engine->ctx);
  platform_destroy(engine->platform);

  if (engine->renderer) {
    renderer_destroy(engine->renderer);
  }
}

b8 engine_init(Engine *engine) {
  platform_window_create(engine->platform);
  platform_window_attach_egl(engine->platform, engine->ctx);
  renderer_context_make_current(engine->ctx);
  renderer_context_viewport(engine->platform->width, engine->platform->height);

  return true;
}

void engine_run(Engine *engine, Shader shader) {
  engine->renderer = renderer_new(shader);
  engine->running = true;

  CB_INFO("Engine is now running.");

  while (engine->running) {
    if (!engine->platform->running) {
      engine_quit(engine);
      break;
    }

    platform_window_pool_events(engine->platform);
    renderer_context_clear(RGB(0, 0, 0.2f));

    engine->config.update_callback(engine);
    engine->config.draw_callback(engine);

    renderer_context_swap_buffers(engine->ctx);
  }
}

void engine_quit(Engine *engine) {
  engine->running = false;

  CB_INFO("Engine Shutdown.");
}
