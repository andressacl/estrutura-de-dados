#ifndef TREE_H 
#define TREE_H

#include "../Util/Util.h"
#include "../Customer/Customer.h"

typedef struct node_st Node;
typedef struct tree_st Tree;

Tree *tree_create();

boolean tree_insert_customer(Tree *tree, Customer *customer);
Customer *customer_search(Node *raiz, CPF_list *cpf);

void tree_print_pre_order(Tree *tree);

Node *raiz(Tree *tree);
Customer *get_customer(Node *node);
Customer *tree_remove_node(Tree *tree, CPF_list *cpf);

void tree_delete(Tree **tree_ref);

#endif