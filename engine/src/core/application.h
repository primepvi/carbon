#ifndef CB_APPLICATION_H
#define CB_APPLICATION_H

#include "core/assets.h"
#include "platform/platform.h"
#include "renderer/renderer.h"
#include "renderer/renderer_context.h"
#include "types.h"

typedef struct Application Application;

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
  Assets *assets;
  b8 running;

  f64 last_time;
} Application;

CB_API Application application_new(ApplicationConfig config);
CB_API b8 application_init(Application *app);
CB_API void application_run(Application *app);
CB_API void application_quit(Application *app);
CB_API void application_destroy(Application *app);
CB_API void application_load_texture(Application *app, const char *path,
                                     const char *name);

CB_API f64 application_time_now(void);

#endif
