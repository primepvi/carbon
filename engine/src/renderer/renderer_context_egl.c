#include <cb_engine/renderer/renderer_context_egl.h>
#include <cb_engine/renderer/renderer_context.h>
#include <cb_engine/core/logger.h>
#include <stdlib.h>

static EGLint EGL_CONFIG_ATTRIBS[] = {EGL_SURFACE_TYPE,
                                      EGL_WINDOW_BIT,
                                      EGL_RENDERABLE_TYPE,
                                      EGL_OPENGL_BIT,
                                      EGL_RED_SIZE,
                                      8,
                                      EGL_GREEN_SIZE,
                                      8,
                                      EGL_BLUE_SIZE,
                                      8,
                                      EGL_DEPTH_SIZE,
                                      24,
                                      EGL_NONE};

static EGLint EGL_CONTEXT_ATTRIBS[] = {EGL_CONTEXT_MAJOR_VERSION,
                                       4,
                                       EGL_CONTEXT_MINOR_VERSION,
                                       6,
                                       EGL_CONTEXT_OPENGL_PROFILE_MASK,
                                       EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
                                       EGL_NONE};

RendererContext *renderer_context_new(void) {
  RendererContext *ctx = malloc(sizeof(RendererContext));
  ctx->descriptor = malloc(sizeof(RendererContextEGL));
  return ctx;
}

void renderer_context_destroy(RendererContext *ctx) {
  RendererContextEGL *descriptor = ctx->descriptor;
  eglMakeCurrent(descriptor->display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                 EGL_NO_CONTEXT);
  eglDestroyContext(descriptor->display, descriptor->context);
  eglDestroySurface(descriptor->display, descriptor->surface);
  eglTerminate(descriptor->display);

  free(descriptor);
  free(ctx);
}

void renderer_context_make_current(RendererContext *ctx) {
  RendererContextEGL *descriptor = ctx->descriptor;

  if (descriptor->display == EGL_NO_DISPLAY) {
    CB_FATAL("Egl display must be attached.\nEGL error: 0x%x", eglGetError());
  }

  if (!eglInitialize(descriptor->display, NULL, NULL)) {
    CB_FATAL("Cannot initialize egl.\nEGL error: 0x%x", eglGetError());
  }

  EGLConfig config;
  EGLint config_size;

  if (!eglChooseConfig(descriptor->display, EGL_CONFIG_ATTRIBS, &config, 1,
                       &config_size)) {
    CB_FATAL("Cannot choose egl config.\nEGL error: 0x%x", eglGetError());
  }

  descriptor->surface = eglCreateWindowSurface(descriptor->display, config,
                                               descriptor->window, NULL);

  if (descriptor->surface == EGL_NO_SURFACE) {
    CB_FATAL("Cannot create egl window surface.\nEGL error: 0x%x",
             eglGetError());
  }

  if (!eglBindAPI(EGL_OPENGL_API)) {
    CB_FATAL("Cannot bind OpenGL API.\nEGL error: 0x%x", eglGetError());
  }

  descriptor->context = eglCreateContext(descriptor->display, config,
                                         EGL_NO_CONTEXT, EGL_CONTEXT_ATTRIBS);

  if (descriptor->context == EGL_NO_CONTEXT) {
    CB_FATAL("Cannot create egl context.\nEGL error: 0x%x", eglGetError());
  }

  if (!eglMakeCurrent(descriptor->display, descriptor->surface,
                      descriptor->surface, descriptor->context)) {
    CB_FATAL("Cannot make egl context current.\nEGL error: 0x%x",
             eglGetError());
  }

  gladLoadGLLoader((GLADloadproc)eglGetProcAddress);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void renderer_context_swap_buffers(RendererContext *ctx) {
  RendererContextEGL *descriptor = ctx->descriptor;
  eglSwapBuffers(descriptor->display, descriptor->surface);
}

void renderer_context_clear(Color color) {
  glClearColor(color.red, color.green, color.blue, color.alpha);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_context_viewport(u32 width, u32 height) {
  glViewport(0, 0, width, height);
}
