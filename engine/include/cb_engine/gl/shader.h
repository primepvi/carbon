#ifndef CB_SHADER_H
#define CB_SHADER_H

#include <glad/glad.h>
#include "../math/mat4.h"
#include "../types.h"

typedef struct {
  GLuint id;
} Shader;

CB_API Shader shader_from_files(const char *vertex_path, const char *frag_path);
CB_API Shader shader_from_sources(const char *vertex_source, const char *frag_source);

CB_API void shader_free(Shader *shader);
CB_API void shader_bind(Shader shader);
CB_API void shader_unbind(void);

CB_API void shader_uniform_mat4(Shader shader, const char *uniform, Mat4 mat);
void shader_uniform_int(Shader shader, const char *uniform, i32 val);
void shader_uniform_int_array(Shader shader, const char *uniform, u32 count, i32 *val);

#endif
