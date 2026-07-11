#ifndef CB_RENDERER_CONTEXT_EGL_H
#define CB_RENDERER_CONTEXT_EGL_H

#include <EGL/egl.h>
#include <glad/glad.h>

typedef struct {
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;
  EGLNativeWindowType window;
} RendererContextEGL;

#endif
