#ifndef CB_RENDERER_CONTEXT_H
#define CB_RENDERER_CONTEXT_H

#include "../types.h"
#include "core/math/color.h"

typedef struct {
  void *descriptor;
} RendererContext;

CB_API RendererContext *renderer_context_new(void);
CB_API void renderer_context_destroy(RendererContext *ctx);
void renderer_context_make_current(RendererContext *ctx);
b8 renderer_context_swap_buffers(RendererContext *ctx, Color color);
void renderer_context_viewport(RendererContext *ctx, u32 width, u32 height);

#endif
