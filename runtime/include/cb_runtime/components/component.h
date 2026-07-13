#ifndef CB_COMPONENT_H
#define CB_COMPONENT_H

#include <cb_engine/types.h>

typedef enum {
  COMPONENT_INVALID = -1,
  COMPONENT_SPRITE,
} ComponentKind;

typedef u32 ComponentHandle;

typedef struct {
  ComponentKind kind;
  ComponentHandle handle;
} Component;

#endif
