#include "application.h"
#include "core/input.h"
#include "core/logger.h"
#include "math/utils.h"
#include <stdlib.h>
#include <time.h>

f64 application_time_now(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

Application application_new(ApplicationConfig config) {
  Platform *platform = platform_new(config.window_width, config.window_height,
                                    config.window_title);

  RendererContext *ctx = renderer_context_new();

  return (Application){.config = config,
                       .ctx = ctx,
                       .platform = platform,
                       .running = false,
                       .renderer = NULL,
                       .assets = assets_new(),
                       .last_time = application_time_now()};
}

void application_destroy(Application *application) {
  renderer_context_destroy(application->ctx);
  platform_destroy(application->platform);

  if (application->renderer) {
    renderer_destroy(application->renderer);
  }
}

b8 application_init(Application *application) {
  platform_window_create(application->platform);
  platform_window_attach_egl(application->platform, application->ctx);
  renderer_context_make_current(application->ctx);
  renderer_context_viewport(application->platform->width,
                            application->platform->height);

  return true;
}

void application_run(Application *application) {
  Shader shader =
      shader_from_files("assets/shaders/main.vert", "assets/shaders/main.frag");

  application->renderer = renderer_new(shader, application->assets);
  application->running = true;

  CB_INFO("Application is now running.");

  while (application->running) {
    if (!application->platform->running) {
      application_quit(application);
      break;
    }

    f64 current_time = application_time_now();
    f64 delta_time = current_time - application->last_time;
    application->last_time = current_time;

    input_begin_frame();
    platform_window_pool_events(application->platform);

    renderer_context_clear(RGB(0, 0, 0.1f));
    renderer_prepare(application->renderer);

    application->config.update(delta_time);
    application->config.draw(application->renderer);

    renderer_flush(application->renderer);
    renderer_context_swap_buffers(application->ctx);
  }
}

void application_quit(Application *application) {
  application->running = false;

  CB_INFO("Application Shutdown.");
}

void application_load_texture(Application *application, const char *path,
                              const char *name) {
  Assets *assets = application->assets;

  if (assets_has_texture(assets, name))
    return;

  assets_load_texture(assets, path, name);
}
