#ifndef CB_RENDERER_H
#define CB_RENDERER_H

#include "../gl/ebo.h"
#include "../gl/shader.h"
#include "../gl/texture.h"
#include "../gl/vao.h"
#include "../gl/vbo.h"

#include "../math/color.h"
#include "../math/vec2.h"

#include "../platform/platform.h"

#include "../types.h"

#define RENDERER_BATCH_MAX_VERTICES 128
#define RENDERER_BATCH_MAX_INDICES 64

typedef struct {
  Vec2 position;
  Vec2 texture_coords;
  f32 texture_index;
  Color color;
} RendererVertex;

typedef struct {
  RendererVertex vertices[RENDERER_BATCH_MAX_VERTICES];
  u32 vertices_count;

  u32 indices[RENDERER_BATCH_MAX_INDICES];
  u32 indices_count;

  Texture textures[16];
  u32 textures_count;

  VBO vbo;
  VAO vao;
  EBO ebo;
} RendererBatch;

typedef struct {
  RendererBatch *batch;
  Shader shader;
  
  Mat4 projection;
  Mat4 view;
} Renderer;

CB_API Renderer *renderer_new(Shader shader, Platform *platform);
CB_API void renderer_destroy(Renderer *renderer);

b8 renderer_should_flush(Renderer *renderer);

CB_API void renderer_set_projection(Renderer *renderer, Mat4 projection);
CB_API void renderer_set_view(Renderer *renderer, Mat4 view);

CB_API void renderer_prepare(Renderer *renderer);
CB_API void renderer_flush(Renderer *renderer);
CB_API void renderer_draw_texture(Renderer *renderer, Vec2 position, Vec2 size,
				  Texture *texture, Color color);

#endif
