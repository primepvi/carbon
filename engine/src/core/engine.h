#ifndef CB_ENGINE_H
#define CB_ENGINE_H

#include "platform/platform.h"
#include "renderer/renderer.h"
#include "renderer/renderer_context.h"
#include "types.h"

typedef struct Engine Engine;

typedef struct {
  const char *window_title;
  u32 window_width;
  u32 window_height;

  void (*draw_callback)(Engine *);
  void (*update_callback)(Engine *);
} EngineConfig;

typedef struct Engine {
  EngineConfig config;
  Platform *platform;
  Renderer *renderer;
  RendererContext *ctx;
  b8 running;
} Engine;

CB_API Engine engine_new(EngineConfig config);
CB_API b8 engine_init(Engine *engine);
CB_API void engine_run(Engine *engine, Shader shader);
CB_API void engine_quit(Engine *engine);
CB_API void engine_destroy(Engine *engine);

#endif
