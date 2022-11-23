#ifndef NODE_H
#define NODE_H

#include "../Util/Util.h"

typedef struct node_st Node;

Node *node_create(int val);

void node_set_next(Node *node, Node *node_next);
Node *node_next(Node *node);
int node_val(Node *node);

void node_delete(Node **node);

#endif //NODE_H