#ifndef CB_COMPONENT_H
#define CB_COMPONENT_H

#include <cb_engine/types.h>

#define CB_INVALID_HANDLE -1

typedef enum {
  COMPONENT_INVALID = -1,
  COMPONENT_TRANSFORM,
  COMPONENT_TEXTURE,
  COMPONENT_SPRITE,
  COMPONENT_SCRIPT,
  COMPONENT_COLLIDER
} ComponentKind;

typedef i32 ComponentHandle;

typedef struct {
  ComponentKind kind;
  ComponentHandle handle;
} Component;

#endif
