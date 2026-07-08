#include <stdio.h>
#include <stdlib.h>

#include "shader.h"

static const char *read_shader_file(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "dust -> cannot open shader file at: '%s'", path);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  u32 len = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(len + 1);
  if (buffer == NULL) {
    fprintf(stderr, "dust -> cannot allocate buffer to read shader source.");
    return NULL;
  }

  fread(buffer, 1, len, file);
  fclose(file);

  buffer[len] = '\0';

  return buffer;
}

Shader shader_from_files(const char *vertex_path, const char *frag_path) {
  const char *vertex_source = read_shader_file(vertex_path);
  const char *frag_source = read_shader_file(frag_path);

  if (vertex_source == NULL || frag_source == NULL) {
    fprintf(stderr, "dust -> cannot compile shader because invalid shader "
                    "source has been provided.");
    return (Shader){0};
  }

  return shader_from_sources(vertex_source, frag_source);
}

Shader shader_from_sources(const char *vertex_source, const char *frag_source) {
  GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_id, 1, &vertex_source, NULL);
  glCompileShader(vertex_id);

  GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_id, 1, &frag_source, NULL);
  glCompileShader(frag_id);

  Shader shader = {.id = glCreateProgram()};
  glAttachShader(shader.id, vertex_id);
  glAttachShader(shader.id, frag_id);
  glLinkProgram(shader.id);

  glDeleteShader(vertex_id);
  glDeleteShader(frag_id);

  return shader;
}

void shader_free(Shader *shader) {
  glDeleteProgram(shader->id);
  shader->id = 0;
}

void shader_bind(Shader shader) { glUseProgram(shader.id); }
void shader_unbind(void) { glUseProgram(0); }

void shader_uniform_mat4(Shader shader, const char *uniform, Mat4 mat) {
  GLint loc_uniform = glGetUniformLocation(shader.id, uniform);
  glUniformMatrix4fv(loc_uniform, 1, GL_FALSE, mat4_ptr(&mat));
}

void shader_uniform_int(Shader shader, const char *uniform, i32 val) {
  GLint loc_uniform = glGetUniformLocation(shader.id, uniform);
  glUniform1i(loc_uniform, val);
}

void shader_uniform_int_array(Shader shader, const char *uniform, u32 size,
                              i32 *val) {
  GLint loc_uniform = glGetUniformLocation(shader.id, uniform);
  glUniform1iv(loc_uniform, size, val);
}
