#ifndef CB_APPLICATION_H
#define CB_APPLICATION_H

#include "../platform/platform.h"
#include "../renderer/renderer.h"
#include "../renderer/renderer_context.h"
#include "../types.h"

typedef struct {
  const char *window_title;
  u32 window_width;
  u32 window_height;
} ApplicationConfig;

typedef struct Application {
  Platform *platform;
  Renderer *renderer;
  RendererContext *ctx;
  b8 running;
  f64 delta_time, last_time;
} Application;

CB_API Application application_new(ApplicationConfig config);
CB_API Renderer *application_get_renderer(Application *app);

CB_API void application_init(Application *app);
CB_API void application_begin_frame(Application *app);
CB_API void application_end_frame(Application *app);

CB_API b8 application_should_close(Application *app);

CB_API void application_quit(Application *app);
CB_API void application_destroy(Application *app);

CB_API f64 application_delta_time(Application *app);
CB_API f64 application_time_now(void);

#endif
