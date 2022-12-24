#ifndef AVL_H 
#define AVL_H

#include "../Util/Util.h"
#include "../Game/Game.h"

typedef struct node_st Node;
typedef struct avl_st Avl;

Avl *avl_create();

int node_height(Node *node);
int node_balance_factor(Node *node);

boolean avl_insert(Avl *avl, Game *game);
Node *avl_rebalance(Node **node);
boolean avl_is_empty(Avl *avl);
Node *avl_root(Avl *avl);

Node *right_rotation(Node *a);
Node *left_rotation(Node *a);
Node *left_right_rotation(Node *a);
Node *right_left_rotation(Node *a);

Game *get_game(Node *node);
Game *avl_search_game(Node *raiz, int year);
boolean avl_remove_game(Avl *avl, Game *game);

void avl_pre_order(Avl *avl);
void avl_in_order(Avl *avl);
void avl_post_order(Avl *avl);
void avl_imprimir(Avl *root);

void avl_delete(Avl **avl_ref); 

#endif