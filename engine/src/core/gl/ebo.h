#ifndef CB_EBO_H
#define CB_EBO_H

#include <glad/glad.h>
#include "types.h"

typedef struct {
  GLuint id;
  GLenum usage;
} EBO;

EBO ebo_new(GLenum usage);
void ebo_free(EBO *ebo);

void ebo_bind(EBO ebo);
void ebo_unbind(void);

void ebo_data(EBO ebo, const u32 *indexes, u32 count);
void ebo_subdata(u32 offset, const void *data, u32 size);

#endif
