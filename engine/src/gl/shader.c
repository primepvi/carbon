#include <stdio.h>
#include <stdlib.h>

#include <cb_engine/core/logger.h>
#include <cb_engine/gl/shader.h>

static const char *read_shader_file(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    CB_ERROR("Cannot open shader file at: '%s'", path);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  u32 len = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(len + 1);
  if (buffer == NULL) {
    CB_ERROR("Cannot allocate buffer to read shader source.");
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
    CB_FATAL("Cannot compile shader because invalid shader source has been "
             "provided.");
  }

  return shader_from_sources(vertex_source, frag_source);
}

Shader shader_from_sources(const char *vertex_source, const char *frag_source) {
  GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_id, 1, &vertex_source, NULL);
  glCompileShader(vertex_id);

  GLint vertex_compiled = 1;
  glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &vertex_compiled);
  if (!vertex_compiled) {
    GLint log_len = 0;
    glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &log_len);

    char *log_buf = malloc(log_len);
    glGetShaderInfoLog(vertex_id, log_len, NULL, log_buf);
    CB_FATAL("Cannot compile vertex shader.\nError: %s\nSource: %s",
             log_buf, vertex_source);
  }

  GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_id, 1, &frag_source, NULL);
  glCompileShader(frag_id);

  GLint frag_compiled = 1;
  glGetShaderiv(frag_id, GL_COMPILE_STATUS, &frag_compiled);
  if (!frag_compiled) {
    GLint log_len = 0;
    glGetShaderiv(frag_id, GL_INFO_LOG_LENGTH, &log_len);

    char *log_buf = malloc(log_len);
    glGetShaderInfoLog(frag_id, log_len, NULL, log_buf);
    CB_FATAL("Cannot compile fragment shader.\nError: %s\nSource: %s",
             log_buf, frag_source);
  }

  Shader shader = {.id = glCreateProgram()};
  glAttachShader(shader.id, vertex_id);
  glAttachShader(shader.id, frag_id);
  glLinkProgram(shader.id);

  GLint shader_linked = 1;
  glGetProgramiv(shader.id, GL_LINK_STATUS, &shader_linked);
  if (!shader_linked) {
    GLint log_len = 0;
    glGetProgramiv(shader.id, GL_INFO_LOG_LENGTH, &log_len);

    char *log_buf = malloc(log_len);
    glGetProgramInfoLog(shader.id, log_len, NULL, log_buf);
    CB_FATAL("Cannot link shader program.\nError: %s", log_buf);
  }

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
