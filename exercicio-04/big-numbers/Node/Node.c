#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Node.h"

struct node_st {
	int val;
	Node *next;
};

Node *node_create(int val){
	Node *new_node = (Node*) calloc(1, sizeof(Node));
	new_node->val = val;
	new_node->next = NULL;
	return new_node;
}

void node_set_next(Node *node, Node *node_next){
	if (node != NULL){
		node->next = node_next;
	}
}

Node *node_next(Node *node){
	return node->next;
}

int node_val(Node *node){
	return node->val;
}

void node_delete(Node **node_ref){
	Node *node = *node_ref;

	node->next = NULL;

	free(node);
	*node_ref = NULL;
}