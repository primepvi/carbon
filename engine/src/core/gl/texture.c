#include "texture.h"
#include "core/logger.h"

#include <stb_image.h>

Texture texture_from_file(const char *path, b8 flip) {
  stbi_set_flip_vertically_on_load(flip);

  i32 width, height, channels;
  u8 *data = stbi_load(path, &width, &height, &channels, 0);
  if (data == NULL) {
    stbi_image_free(data);
    CB_ERROR("Cannot load texture from file: %s\n", path);
    return texture_white_1x1();
  }

  Texture tex = texture_from_buffer(data, width, height, channels);
  stbi_image_free(data);

  return tex;
}

Texture texture_from_buffer(const u8 *buffer, i32 width, i32 height,
                            i32 channels) {
  Texture tex;
  tex.width = width;
  tex.height = height;
  tex.channels = channels;

  GLint format = 0;
  if (channels == 1) {
    format = GL_RED;
  } else if (channels == 3) {
    format = GL_RGB;
  } else if (channels == 4) {
    format = GL_RGBA;
  }

  glGenTextures(1, &tex.id);
  glBindTexture(GL_TEXTURE_2D, tex.id);
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, buffer);

  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  return tex;
}

Texture texture_white_1x1(void) {
  return texture_from_buffer((u8[]){255, 255, 255, 255}, 1, 1, 4);
}

void texture_free(Texture *tex) {
  glDeleteTextures(1, &tex->id);
  tex->id = 0;
}

void texture_bind(Texture tex, u32 slot) {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, tex.id);
}

void texture_unbind(void) { glBindTexture(GL_TEXTURE_2D, 0); }
