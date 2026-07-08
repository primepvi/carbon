#ifndef CB_ENGINE_H
#define CB_ENGINE_H

#include "types.h"
#include "platform/platform.h"
#include "renderer/renderer_context.h"

typedef void (*EngineUpdateCallback)(void);
typedef void (*EngineDrawCallback)(void);

CB_API b8 engine_init(Platform *platform, RendererContext *ctx);
CB_API void engine_run(EngineUpdateCallback update, EngineDrawCallback draw);
CB_API void engine_quit(void);

#endif
