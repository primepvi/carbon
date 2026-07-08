#include "renderer.h"
#include <stddef.h>
#include <stdlib.h>

Renderer *renderer_new(void) {
  RendererBatch *batch = calloc(1, sizeof(RendererBatch));
  batch->textures[batch->textures_count++] = texture_white_1x1();
  batch->vbo = vbo_new(GL_DYNAMIC_DRAW);
  batch->ebo = ebo_new(GL_DYNAMIC_DRAW);
  batch->vao = vao_new();
  
  vao_bind(batch->vao);
  
  vbo_bind(batch->vbo);
  vbo_data(batch->vbo, NULL,
           RENDERER_BATCH_MAX_VERTICES * sizeof(RendererVertex));

  ebo_bind(batch->ebo);
  ebo_data(batch->ebo, NULL, RENDERER_BATCH_MAX_INDICES * sizeof(u32));


  vao_attrib(batch->vao, 0, 2, GL_FLOAT, sizeof(RendererVertex), 0);
  vao_attrib(batch->vao, 1, 2, GL_FLOAT, sizeof(RendererVertex),
             offsetof(RendererVertex, texture_coords));
  vao_attrib(batch->vao, 2, 1, GL_FLOAT, sizeof(RendererVertex),
             offsetof(RendererVertex, texture_index));
  vao_attrib(batch->vao, 3, 4, GL_FLOAT, sizeof(RendererVertex),
             offsetof(RendererVertex, color));

  Renderer *renderer = malloc(sizeof(Renderer));
  renderer->batch = batch;
  return renderer;
}

void renderer_destroy(Renderer *renderer) {
  free(renderer->batch);
  free(renderer);
}

void renderer_begin(Renderer *renderer) {
  RendererBatch *batch = renderer->batch;
  batch->indices_count = 0;
  batch->vertices_count = 0;
  renderer->batch = batch;
}

void renderer_draw_quad(Renderer *renderer, Vec2 position, Vec2 size,
                        Color color) {
  RendererVertex top_left;
  top_left.position = position;
  top_left.texture_coords = VEC2(0.0f, 1.0f);
  top_left.texture_index = 0;
  top_left.color = color;

  RendererVertex top_right;
  top_right.position = VEC2(position.x + size.x, position.y);
  top_right.texture_coords = VEC2(1.0f, 1.0f);
  top_right.texture_index = 0;
  top_right.color = color;

  RendererVertex bottom_left;
  bottom_left.position = VEC2(position.x, position.y - size.y);
  bottom_left.texture_coords = VEC2(0.0f, 0.0f);
  bottom_left.texture_index = 0;
  bottom_left.color = color;

  RendererVertex bottom_right;
  bottom_right.position = VEC2(position.x + size.x, position.y - size.y);
  bottom_right.texture_coords = VEC2(1.0f, 0.0f);
  bottom_right.texture_index = 0;
  bottom_right.color = color;

  RendererBatch *batch = renderer->batch;

  u32 vertices_base = batch->vertices_count;
  batch->indices[batch->indices_count++] = vertices_base + 0;
  batch->indices[batch->indices_count++] = vertices_base + 1;
  batch->indices[batch->indices_count++] = vertices_base + 2;
  batch->indices[batch->indices_count++] = vertices_base + 0;
  batch->indices[batch->indices_count++] = vertices_base + 2;
  batch->indices[batch->indices_count++] = vertices_base + 3;

  batch->vertices[batch->vertices_count++] = top_left;
  batch->vertices[batch->vertices_count++] = top_right;
  batch->vertices[batch->vertices_count++] = bottom_right;
  batch->vertices[batch->vertices_count++] = bottom_left;
}

void renderer_end(Renderer *renderer) {
  RendererBatch *batch = renderer->batch;

  vbo_bind(batch->vbo);
  vbo_subdata(0, batch->vertices,
              batch->vertices_count * sizeof(RendererVertex));

  ebo_bind(batch->ebo);
  ebo_subdata(0, batch->indices, batch->indices_count * sizeof(u32));

  for (u32 i = 0; i < batch->textures_count; i++)
    texture_bind(batch->textures[i], i);

  vao_bind(batch->vao);
  
  glDrawElements(GL_TRIANGLES, batch->indices_count, GL_UNSIGNED_INT, NULL);
}
