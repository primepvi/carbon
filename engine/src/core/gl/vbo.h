#ifndef CB_VBO_H
#define CB_VBO_H

#include <glad/glad.h>
#include "types.h"

typedef struct {
  GLuint id;
  GLenum usage;
} VBO;

VBO vbo_new(GLenum usage);
void vbo_free(VBO *vbo);

void vbo_bind(VBO vbo);
void vbo_unbind(void);
void vbo_data(VBO vbo, const void *data, u32 size);
void vbo_subdata(u32 offset, const void *data, u32 size);

#endif
