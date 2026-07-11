#ifndef CB_APPLICATION_H
#define CB_APPLICATION_H

#include <cb_engine/platform/platform.h>
#include <cb_engine/renderer/renderer.h>
#include <cb_engine/renderer/renderer_context.h>
#include <cb_engine/types.h>

typedef struct {
  const char *window_title;
  u32 window_width;
  u32 window_height;

  void (*draw)(Renderer *);
  void (*update)(f64 delta_time);
} ApplicationConfig;

typedef struct Application {
  ApplicationConfig config;
  Platform *platform;
  Renderer *renderer;
  RendererContext *ctx;
  b8 running;
  f64 last_time;
} Application;

CB_API Application application_new(ApplicationConfig config);
CB_API b8 application_init(Application *app);
CB_API void application_run(Application *app);
CB_API void application_quit(Application *app);
CB_API void application_destroy(Application *app);
CB_API f64 application_time_now(void);

#endif
