#include "vbo.h"

VBO vbo_new(GLenum usage) {
  VBO vbo = {0, usage};
  glGenBuffers(1, &vbo.id);

  return vbo;
}

void vbo_free(VBO *vbo) {
  glDeleteBuffers(1, &vbo->id);
  vbo->id = 0;
}

void vbo_bind(VBO vbo) {
  glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
}

void vbo_unbind(void) {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_data(VBO vbo, const void *data, u32 size) {
  glBufferData(GL_ARRAY_BUFFER, size, data, vbo.usage);
}

void vbo_subdata(u32 offset, const void *data, u32 size) {
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
