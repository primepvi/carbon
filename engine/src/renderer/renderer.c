#include "renderer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Renderer *renderer_new(Shader shader) {
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
  renderer->shader = shader;

  return renderer;
}

void renderer_destroy(Renderer *renderer) {
  free(renderer->batch);
  free(renderer);
}

void renderer_prepare(Renderer *renderer) {
  RendererBatch *batch = renderer->batch;
  batch->textures_count = 1;
  batch->indices_count = 0;
  batch->vertices_count = 0;
}

void renderer_draw_quad(Renderer *renderer, Vec2 position, Vec2 size,
                        Color color) {
  if (renderer_should_flush(renderer)) {
    renderer_flush(renderer);
  }

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
  bottom_left.position = VEC2(position.x, position.y + size.y);
  bottom_left.texture_coords = VEC2(0.0f, 0.0f);
  bottom_left.texture_index = 0;
  bottom_left.color = color;

  RendererVertex bottom_right;
  bottom_right.position = VEC2(position.x + size.x, position.y + size.y);
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

void renderer_flush(Renderer *renderer) {
  RendererBatch *batch = renderer->batch;

  shader_bind(renderer->shader);

  vbo_bind(batch->vbo);
  vbo_subdata(0, batch->vertices,
              batch->vertices_count * sizeof(RendererVertex));

  ebo_bind(batch->ebo);
  ebo_subdata(0, batch->indices, batch->indices_count * sizeof(u32));

  i32 textures[16];
  for (u32 i = 0; i < 16; i++) {
    textures[i] = i;
  }

  for (u32 i = 0; i < batch->textures_count; i++) {
    texture_bind(batch->textures[i], i);
  }

  shader_uniform_int_array(renderer->shader, "u_textures", 16, textures);
  shader_uniform_mat4(renderer->shader, "u_proj", mat4_ortho(0, 800, 600, 0));
  shader_uniform_mat4(renderer->shader, "u_view",
                      mat4_view(VEC2(0.0f, 0.0f), 1.0f));

  vao_bind(batch->vao);
  glDrawElements(GL_TRIANGLES, batch->indices_count, GL_UNSIGNED_INT, NULL);

  renderer_prepare(renderer);
}

b8 renderer_should_flush(Renderer *renderer) {
  RendererBatch *batch = renderer->batch;
  return batch->textures_count >= 16 ||
         batch->vertices_count >= RENDERER_BATCH_MAX_VERTICES ||
         batch->indices_count >= RENDERER_BATCH_MAX_INDICES;
}
