#ifndef CB_PLATFORM_X11_H
#define CB_PLATFORM_X11_H

#include <X11/Xlib.h>
#include "../types.h"

typedef struct {
  Display *display;
  Window window;
  GC gc;
  Atom wm_delete;
  i32 screen;
} PlatformX11;

#endif
