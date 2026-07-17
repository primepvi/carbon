#include <cb_engine/core/application.h>
#include <cb_engine/core/input.h>
#include <cb_engine/core/logger.h>
#include <cb_engine/math/utils.h>

#include <stdlib.h>
#include <time.h>

f64 application_time_now(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  return ts.tv_sec + ts.tv_nsec / 1000000000.0;
}

f64 application_delta_time(Application *app) {
  return app->delta_time;
}

Application application_new(ApplicationConfig config) {
  Platform *platform = platform_new(config.window_width, config.window_height,
                                    config.window_title);

  RendererContext *ctx = renderer_context_new();

  return (Application){.ctx = ctx,
                       .platform = platform,
                       .running = false,
                       .renderer = NULL,
                       .last_time = application_time_now(),
                       .delta_time = 0.0f};
}

Renderer *application_get_renderer(Application *application) {
  if (!application->running) {
    CB_FATAL("Cannot get application renderer if application isn't running.");
  }
  
  return application->renderer;
}

void application_destroy(Application *application) {
  renderer_context_destroy(application->ctx);
  platform_destroy(application->platform);

  if (application->renderer) {
    renderer_destroy(application->renderer);
  }
}

void application_init(Application *application) {
  platform_window_create(application->platform);
  platform_window_attach_egl(application->platform, application->ctx);
  renderer_context_make_current(application->ctx);
  renderer_context_viewport(application->platform->width,
                            application->platform->height);

  Shader shader =
      shader_from_files("assets/shaders/main.vert", "assets/shaders/main.frag");

  application->renderer = renderer_new(shader, application->platform);
  application->running = true;

  CB_DEBUG("Application is now running.");
}

void application_begin_frame(Application *application) {
  if (!application->platform->running)
    application_quit(application);

  f64 current_time = application_time_now();
  application->delta_time = current_time - application->last_time;
  application->last_time = current_time;

  input_begin_frame();
  platform_window_pool_events(application->platform);

  renderer_context_clear(RGB(0, 0, 0.1f));
  renderer_prepare(application->renderer);
}

void application_end_frame(Application *application) {
  if (!application->platform->running)
    application_quit(application);

  renderer_flush(application->renderer);
  renderer_context_swap_buffers(application->ctx);
}

b8 application_should_close(Application *application) {
  return !application->running;
}

void application_quit(Application *application) {
  application->running = false;
  CB_DEBUG("Application Shutdown.");
}
