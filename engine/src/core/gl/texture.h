#ifndef CB_TEXTURE_H
#define CB_TEXTURE_H

#include <glad/glad.h>
#include "types.h"

typedef struct {
  GLuint id;
  u32 width, height, channels;
} Texture;

Texture texture_from_file(const char *path, b8 flip);
Texture texture_from_buffer(const u8 *buffer, i32 width,
                            i32 height, i32 channels);
Texture texture_white_1x1(void);

void texture_free(Texture *tex);
void texture_bind(Texture tex, u32 slot);
void texture_unbind(void);

#endif
