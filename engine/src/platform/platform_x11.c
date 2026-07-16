#include <cb_engine/platform/platform.h>
#include <cb_engine/platform/platform_x11.h>

#include <cb_engine/core/logger.h>
#include <cb_engine/core/input.h>
#include <cb_engine/renderer/renderer_context_egl.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>

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
               KeyPressMask | KeyReleaseMask | ButtonPressMask |
                   ButtonReleaseMask | PointerMotionMask | StructureNotifyMask);

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

static InputKey platform_input_key_from_x11(KeySym key) {
  switch (key) {
  // Letters
  case XK_A:
  case XK_a:
    return INPUT_KEY_A;
  case XK_B:
  case XK_b:
    return INPUT_KEY_B;
  case XK_C:
  case XK_c:
    return INPUT_KEY_C;
  case XK_D:
  case XK_d:
    return INPUT_KEY_D;
  case XK_E:
  case XK_e:
    return INPUT_KEY_E;
  case XK_F:
  case XK_f:
    return INPUT_KEY_F;
  case XK_G:
  case XK_g:
    return INPUT_KEY_G;
  case XK_H:
  case XK_h:
    return INPUT_KEY_H;
  case XK_I:
  case XK_i:
    return INPUT_KEY_I;
  case XK_J:
  case XK_j:
    return INPUT_KEY_J;
  case XK_K:
  case XK_k:
    return INPUT_KEY_K;
  case XK_L:
  case XK_l:
    return INPUT_KEY_L;
  case XK_M:
  case XK_m:
    return INPUT_KEY_M;
  case XK_N:
  case XK_n:
    return INPUT_KEY_N;
  case XK_O:
  case XK_o:
    return INPUT_KEY_O;
  case XK_P:
  case XK_p:
    return INPUT_KEY_P;
  case XK_Q:
  case XK_q:
    return INPUT_KEY_Q;
  case XK_R:
  case XK_r:
    return INPUT_KEY_R;
  case XK_S:
  case XK_s:
    return INPUT_KEY_S;
  case XK_T:
  case XK_t:
    return INPUT_KEY_T;
  case XK_U:
  case XK_u:
    return INPUT_KEY_U;
  case XK_V:
  case XK_v:
    return INPUT_KEY_V;
  case XK_W:
  case XK_w:
    return INPUT_KEY_W;
  case XK_X:
  case XK_x:
    return INPUT_KEY_X;
  case XK_Y:
  case XK_y:
    return INPUT_KEY_Y;
  case XK_Z:
  case XK_z:
    return INPUT_KEY_Z;

  // Numbers
  case XK_0:
    return INPUT_KEY_0;
  case XK_1:
    return INPUT_KEY_1;
  case XK_2:
    return INPUT_KEY_2;
  case XK_3:
    return INPUT_KEY_3;
  case XK_4:
    return INPUT_KEY_4;
  case XK_5:
    return INPUT_KEY_5;
  case XK_6:
    return INPUT_KEY_6;
  case XK_7:
    return INPUT_KEY_7;
  case XK_8:
    return INPUT_KEY_8;
  case XK_9:
    return INPUT_KEY_9;

  // Symbols
  case XK_grave:
    return INPUT_KEY_GRAVE;
  case XK_minus:
    return INPUT_KEY_MINUS;
  case XK_equal:
    return INPUT_KEY_EQUAL;
  case XK_bracketleft:
    return INPUT_KEY_LEFT_BRACKET;
  case XK_bracketright:
    return INPUT_KEY_RIGHT_BRACKET;
  case XK_backslash:
    return INPUT_KEY_BACKSLASH;
  case XK_semicolon:
    return INPUT_KEY_SEMICOLON;
  case XK_apostrophe:
    return INPUT_KEY_APOSTROPHE;
  case XK_comma:
    return INPUT_KEY_COMMA;
  case XK_period:
    return INPUT_KEY_PERIOD;
  case XK_slash:
    return INPUT_KEY_SLASH;

  // Control
  case XK_Escape:
    return INPUT_KEY_ESCAPE;
  case XK_Return:
    return INPUT_KEY_ENTER;
  case XK_Tab:
    return INPUT_KEY_TAB;
  case XK_BackSpace:
    return INPUT_KEY_BACKSPACE;
  case XK_Insert:
    return INPUT_KEY_INSERT;
  case XK_Delete:
    return INPUT_KEY_DELETE;
  case XK_Home:
    return INPUT_KEY_HOME;
  case XK_End:
    return INPUT_KEY_END;
  case XK_Page_Up:
    return INPUT_KEY_PAGE_UP;
  case XK_Page_Down:
    return INPUT_KEY_PAGE_DOWN;
  case XK_space:
    return INPUT_KEY_SPACE;

  // Arrow
  case XK_Left:
    return INPUT_KEY_LEFT;
  case XK_Right:
    return INPUT_KEY_RIGHT;
  case XK_Up:
    return INPUT_KEY_UP;
  case XK_Down:
    return INPUT_KEY_DOWN;

  // Mods
  case XK_Shift_L:
    return INPUT_KEY_LEFT_SHIFT;
  case XK_Shift_R:
    return INPUT_KEY_RIGHT_SHIFT;
  case XK_Control_L:
    return INPUT_KEY_LEFT_CONTROL;
  case XK_Control_R:
    return INPUT_KEY_RIGHT_CONTROL;
  case XK_Alt_L:
  case XK_Meta_L:
    return INPUT_KEY_LEFT_ALT;
  case XK_Alt_R:
  case XK_Meta_R:
    return INPUT_KEY_RIGHT_ALT;
  case XK_Super_L:
    return INPUT_KEY_LEFT_SUPER;
  case XK_Super_R:
    return INPUT_KEY_RIGHT_SUPER;
  case XK_Menu:
    return INPUT_KEY_MENU;

  // Locks
  case XK_Caps_Lock:
    return INPUT_KEY_CAPS_LOCK;
  case XK_Num_Lock:
    return INPUT_KEY_NUM_LOCK;
  case XK_Scroll_Lock:
    return INPUT_KEY_SCROLL_LOCK;

  // Functions
  case XK_F1:
    return INPUT_KEY_F1;
  case XK_F2:
    return INPUT_KEY_F2;
  case XK_F3:
    return INPUT_KEY_F3;
  case XK_F4:
    return INPUT_KEY_F4;
  case XK_F5:
    return INPUT_KEY_F5;
  case XK_F6:
    return INPUT_KEY_F6;
  case XK_F7:
    return INPUT_KEY_F7;
  case XK_F8:
    return INPUT_KEY_F8;
  case XK_F9:
    return INPUT_KEY_F9;
  case XK_F10:
    return INPUT_KEY_F10;
  case XK_F11:
    return INPUT_KEY_F11;
  case XK_F12:
    return INPUT_KEY_F12;

  // Numpad
  case XK_KP_0:
    return INPUT_KEY_KP_0;
  case XK_KP_1:
    return INPUT_KEY_KP_1;
  case XK_KP_2:
    return INPUT_KEY_KP_2;
  case XK_KP_3:
    return INPUT_KEY_KP_3;
  case XK_KP_4:
    return INPUT_KEY_KP_4;
  case XK_KP_5:
    return INPUT_KEY_KP_5;
  case XK_KP_6:
    return INPUT_KEY_KP_6;
  case XK_KP_7:
    return INPUT_KEY_KP_7;
  case XK_KP_8:
    return INPUT_KEY_KP_8;
  case XK_KP_9:
    return INPUT_KEY_KP_9;
  case XK_KP_Decimal:
    return INPUT_KEY_KP_DECIMAL;
  case XK_KP_Divide:
    return INPUT_KEY_KP_DIVIDE;
  case XK_KP_Multiply:
    return INPUT_KEY_KP_MULTIPLY;
  case XK_KP_Subtract:
    return INPUT_KEY_KP_SUBTRACT;
  case XK_KP_Add:
    return INPUT_KEY_KP_ADD;
  case XK_KP_Enter:
    return INPUT_KEY_KP_ENTER;
  case XK_KP_Equal:
    return INPUT_KEY_KP_EQUAL;

  default:
    return INPUT_KEY_UNKNOWN;
  }
}

static InputMouseButton platform_input_mouse_button_from_x11(u32 button) {
  switch (button) {
  case Button1:
    return INPUT_MOUSE_BUTTON_LEFT;
  case Button2:
    return INPUT_MOUSE_BUTTON_MIDDLE;
  case Button3:
    return INPUT_MOUSE_BUTTON_RIGHT;
  default:
    return INPUT_MOUSE_BUTTON_COUNT;
  }
}

void platform_input_event(Platform *platform, XEvent *event) {
  PlatformX11 *descriptor = platform->descriptor;
  Input *input = input_get_instance();

  switch (event->type) {
  case KeyPress: {
    InputKey key = platform_input_key_from_x11(XLookupKeysym(&event->xkey, 0));

    if (key != INPUT_KEY_UNKNOWN)
      input->keys[key].current = true;

    break;
  }

  case KeyRelease: {
    if (XEventsQueued(descriptor->display, QueuedAfterReading)) {
      XEvent next;
      XPeekEvent(descriptor->display, &next);

      if (next.type == KeyPress && next.xkey.time == event->xkey.time &&
          next.xkey.keycode == event->xkey.keycode)
        break;
    }

    InputKey key = platform_input_key_from_x11(XLookupKeysym(&event->xkey, 0));
    if (key != INPUT_KEY_UNKNOWN) {
      input->keys[key].current = false;
    }

    break;
  }

  case ButtonPress:
    switch (event->xbutton.button) {
    case Button4:
      input->mouse_wheel += 1.0f;
      break;

    case Button5:
      input->mouse_wheel -= 1.0f;
      break;

    default: {
      InputMouseButton button =
          platform_input_mouse_button_from_x11(event->xbutton.button);

      if (button != INPUT_MOUSE_BUTTON_COUNT)
        input->mouse[button].current = true;

      break;
    }
    }
    break;

  case ButtonRelease: {
    InputMouseButton button =
        platform_input_mouse_button_from_x11(event->xbutton.button);

    if (button != INPUT_MOUSE_BUTTON_COUNT)
      input->mouse[button].current = false;

    break;
  }

  case MotionNotify: {
    int new_x = event->xmotion.x;
    int new_y = event->xmotion.y;

    input->mouse_delta.x += new_x - input->mouse_pos.x;
    input->mouse_delta.y += new_y - input->mouse_pos.y;

    input->mouse_pos.x = new_x;
    input->mouse_pos.y = new_y;

    break;
  }

  default:
    break;
  }
}

void platform_window_pool_events(Platform *platform) {
  PlatformX11 *descriptor = platform->descriptor;
  while (platform->running && XPending(descriptor->display)) {
    XEvent event;
    XNextEvent(descriptor->display, &event);

    switch (event.type) {
    case ClientMessage: {
      Atom atom = (Atom)event.xclient.data.l[0];
      if (atom == descriptor->wm_delete) {
        platform_window_close(platform);
      }
      break;
    }
    case ConfigureNotify: {
      u32 width = event.xconfigure.width;
      u32 height = event.xconfigure.height;

      platform->width = width;
      platform->height = height;
      renderer_context_viewport(width, height);

      break;
    }
    default:
      platform_input_event(platform, &event);
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
