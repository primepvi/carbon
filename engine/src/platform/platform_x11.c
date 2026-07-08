#include "platform_x11.h"
#include "core/logger.h"
#include "platform.h"
#include "renderer/renderer_context_egl.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

Platform *platform_new(u32 width, u32 height, const char *title) {
  Platform *platform = malloc(sizeof(Platform));
  platform->title = title;
  platform->width = width;
  platform->height = height;
  platform->descriptor = NULL;

  return platform;
}

void platform_destroy(Platform *platform) {
  if (platform->running) {
    platform_window_close(platform);
  }

  free(platform->descriptor);
  free(platform);
}

void platform_window_create(Platform *platform) {
  Display *display = XOpenDisplay(NULL);
  if (display == NULL) {
    CB_FATAL("Cannot open X11 display.");
  }

  int screen = XDefaultScreen(display);
  Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 10,
                                      10, platform->width, platform->height, 1,
                                      BlackPixel(display, screen),
                                      WhitePixel(display, screen));

  XStoreName(display, window, platform->title);
  XSelectInput(display, window,
               ExposureMask | KeyPressMask | ButtonPressMask |
                   StructureNotifyMask);

  PlatformX11 *descriptor = malloc(sizeof(PlatformX11));
  descriptor->display = display;
  descriptor->screen = screen;
  descriptor->window = window;
  descriptor->wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", False);

  XSetWMProtocols(display, window, &descriptor->wm_delete, 1);
  XMapWindow(display, window);

  platform->descriptor = descriptor;
  platform->running = true;
}

void platform_window_close(Platform *platform) {
  PlatformX11 *descriptor = platform->descriptor;
  XDestroyWindow(descriptor->display, descriptor->window);
  XCloseDisplay(descriptor->display);
  platform->running = false;
}

void platform_window_pool_events(Platform *platform) {
  PlatformX11 *descriptor = platform->descriptor;
  XEvent event;
  XNextEvent(descriptor->display, &event);

  switch (event.type) {
  case ClientMessage: {
    Atom atom = (Atom)event.xclient.data.l[0];
    if (atom == descriptor->wm_delete) {
      platform_window_close(platform);
    }
  }
  }
}

void platform_window_attach_egl(Platform *platform, RendererContext *ctx) {
  PlatformX11 *platform_descriptor = platform->descriptor;
  RendererContextEGL *ctx_descriptor = ctx->descriptor;

  PFNEGLGETPLATFORMDISPLAYPROC eglGetPlatformDisplay =
      (PFNEGLGETPLATFORMDISPLAYPROC)eglGetProcAddress("eglGetPlatformDisplay");

  ctx_descriptor->display = eglGetPlatformDisplay(
      EGL_PLATFORM_X11_KHR, (void *)platform_descriptor->display, NULL);

  ctx_descriptor->display =
      eglGetDisplay((EGLNativeDisplayType)platform_descriptor->display);

  ctx_descriptor->window = platform_descriptor->window;
}
