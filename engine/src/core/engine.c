#include "engine.h"
#include "math/utils.h"

static struct {
  Platform *platform;
  RendererContext *ctx;
  b8 running;
} _state;

b8 engine_init(Platform *platform, RendererContext *ctx) {
  _state.running = false;
  _state.platform = platform;
  _state.ctx = ctx;

  platform_window_create(platform);
  platform_window_attach_egl(platform, ctx);
  renderer_context_make_current(ctx);
  renderer_context_viewport(platform->width, platform->height);

  return true;
}

void engine_run(EngineUpdateCallback update, EngineDrawCallback draw) {
  _state.running = true;

  while (_state.running) {
    if (!_state.platform->running) {
      engine_quit();
      break;
    }

    platform_window_pool_events(_state.platform);
    renderer_context_clear(RGB(0, 0, 0.2f));
    update();
    draw();
    renderer_context_swap_buffers(_state.ctx);
  }
}

void engine_quit(void) { _state.running = false; }
