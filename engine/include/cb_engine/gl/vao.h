#ifndef CB_VAO_H
#define CB_VAO_H

#include <glad/glad.h>
#include "../types.h"

typedef struct {
  GLuint id;
} VAO;

VAO vao_new(void);
void vao_free(VAO *vao);

void vao_bind(VAO vao);
void vao_unbind(void);

void vao_attrib(u32 index, u32 count, GLenum type, u32 stride, u64 offset);

#endif
