#ifndef CB_NODE_H
#define CB_NODE_H

#include <cb_engine/core/array_list.h>
#include <cb_engine/types.h>
#include <cb_runtime/components/component.h>

typedef i32 NodeHandle;

typedef struct Node {
  char *name;

  NodeHandle parent;

  ArrayList *childrens;
  ArrayList *components;
} Node;


Node *node_new(NodeHandle parent, const char *name);
void node_destroy(Node *node);

void node_push_children(Node *node, NodeHandle children);
void node_push_component(Node *node, Component component);

#endif
