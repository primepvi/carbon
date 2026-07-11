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
  void (*update)(void);
} ApplicationConfig;

typedef struct Application {
  ApplicationConfig config;
  Platform *platform;
  Renderer *renderer;
  RendererContext *ctx;
  Assets *assets;
  b8 running;
} Application;

CB_API Application application_new(ApplicationConfig config);
CB_API b8 application_init(Application *app);
CB_API void application_run(Application *app);
CB_API void application_quit(Application *app);
CB_API void application_destroy(Application *app);
CB_API void application_load_texture(Application *app, const char *path,
                                     const char *name);

#endif
