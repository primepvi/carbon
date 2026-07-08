#ifndef CB_PLATFORM_H
#define CB_PLATFORM_H

#include "../renderer/renderer_context.h"
#include "../types.h"

typedef struct {
  u32 width, height;
  const char *title;
  void *descriptor;
  b8 running;
} Platform;

CB_API Platform *platform_new(u32 width, u32 height, const char *title);
CB_API void platform_destroy(Platform *platform);

void platform_window_create(Platform *platform);
void platform_window_close(Platform *platform);
void platform_window_pool_events(Platform *platform);
void platform_window_attach_egl(Platform *platform, RendererContext *ctx);

#endif
