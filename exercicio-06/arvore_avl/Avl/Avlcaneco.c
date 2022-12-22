#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
// #include <stdboolean.h>

#include "Avl.h" 
#define COUNT 8

struct node_st {
    Game *game;
    Node *right;
    Node *left;
};

struct avl_st {
    Node *root;
    int depth;
};

static Node *node_create(Game *game){
  Node *new_node = (Node*) calloc(1, sizeof(Node));

  if (new_node != NULL){
      new_node->game = game;
      new_node->right = NULL;
      new_node->left = NULL;
  }

  return new_node;
}

static void node_delete(Node **node_ref){
    Node *node = *node_ref;
    game_delete(&(node->game));
    free(node->right);
    free(node->left);
    free(node);
    *node_ref = NULL;
}


Avl *avl_create(){
    Avl *new_avl = (Avl*) calloc(1, sizeof(Avl));

    if (new_avl != NULL) {
      new_avl->root = NULL; 
      new_avl->depth = -1;
    }

    return new_avl;
}

int node_height(Node *node){
    if (node == NULL) return 0;

    int left = 0;
    int right = 0;

    if(node->left != NULL) 
        left = node_height(node->left);

    if(node->right != NULL) 
        right = node_height(node->right);

    if (left > right) return (left+1);
    else return (right+1);
}

int node_balance_factor(Node *node){
    if (node == NULL) return 0;
    return node_height(node->right) - node_height(node->left);
}

Node *right_rotation(Node **a) {
    Node *b = (*a)->left;
    (*a)->left = b->right;
    b->right = (*a);
    
    return b;
}

Node *left_rotation(Node **a) {
    Node *b = (*a)->right;
    (*a)->right = b->left;
    b->left = (*a);
    
    return b;
}

Node *left_right_rotation(Node **a) {
    (*a)->left = left_rotation(&(*a)->left);
    (*a) = right_rotation(a);
    return (*a);
}

Node *right_left_rotation(Node **a) {
    (*a)->right = right_rotation(&(*a)->right);
    (*a) = left_rotation(a);
    return (*a);
}

Node *avl_rebalance(Node **node){
    int bal_factor = node_balance_factor((*node));

    if (bal_factor >= 2){
        if (node_balance_factor((*node)->right) < 0)
            (*node) = right_left_rotation(node);
        else 
            (*node) = right_rotation(node);
    } else if (bal_factor <= -2){
        if (node_balance_factor((*node)->left) > 0)
            (*node) = left_right_rotation(node);
        else 
            (*node) = left_rotation(node);
    }

    return (*node);
}

boolean avl_is_empty(Avl *avl){
    return (avl->root == NULL);
}

Node *node_max(Node *node){
    Node *p = node;

    while(p->right != NULL){
        p = p->right;
    }

    return p;
}


static void pre_order_recursion(Node *root) {
    if (root != NULL) {
        game_print(root->game);
        pre_order_recursion(root->left);
        pre_order_recursion(root->right);
    }
}

static void in_order_recursion(Node *root) {
    if (root != NULL) {
        in_order_recursion(root->left);
        game_print(root->game);
        in_order_recursion(root->right);
    }
}

static void post_order_recursion(Node *root) {
    if (root != NULL) {
        post_order_recursion(root->left);
        post_order_recursion(root->right);
        game_print(root->game);
    }
}

void avl_pre_order(Avl *avl){
    pre_order_recursion(avl->root);
}

void avl_in_order(Avl *avl){
    in_order_recursion(avl->root);
}

void avl_post_order(Avl *avl) {
    post_order_recursion(avl->root);
}

Node *avl_root(Avl *avl){
    return avl->root;
}

Game *get_game(Node *node){
    return node->game;
}

Game *game_search(Node *root, int year){
    if (root == NULL) return NULL;
    if (get_year(root->game) == year) return root->game;

    if (get_year(root->game) < year) return game_search(root->right, year);
    return game_search(root->left, year);
}


// static boolean game_at_right(Node *root, Game *game) {
//     return game_maior(game, root->game);
// }

// static boolean game_at_left(Node *root, Game *game) {
//     return game_maior(root->game, game);
// }

static boolean node_insert(Node **root, Game *game) {
    if ((*root) == NULL) {
        (*root) = node_create(game);
        return TRUE;
    }
    if (game == (*root)->game) return FALSE;
    
    // if (game_at_right((*root), game)) node_insert(&(*root)->right, game);
    // else if (game_at_left((*root), game)) node_insert(&(*root)->left, game);

    if (get_year(game) > get_year((*root)->game)) node_insert(&(*root)->right, game);
    else if (get_year(game) < get_year((*root)->game)) node_insert(&(*root)->left, game);
    
    (*root) = avl_rebalance(root);

    return TRUE;
}

boolean avl_insert(Avl *avl, Game *game){
    return node_insert(&(avl->root), game);
}

// Remoção

static boolean avl_remove_aux(Node **root, int year){

    if((*root) == NULL) return FALSE;

    if (year > get_year((*root)->game)) {
            avl_remove_aux(&(*root)->right, year);
            avl_rebalance(&(*root));
            return TRUE;
    } else if (year < get_year((*root)->game)) {
            avl_remove_aux(&(*root)->left, year);
            avl_rebalance(&(*root));
            return TRUE;
    }

    if ((*root)->left != NULL && (*root)->right != NULL){
        Node *max_left = node_max((*root)->left);

        Game *game_aux = ((*root)->left)->game;
        ((*root)->left)->game = max_left->game;

        game_delete(&game_aux);
        avl_remove_aux(&(*root)->left, get_year(((*root)->left)->game));
        return TRUE;
    }
  
    Node *p;

    if((*root)->left == NULL && (*root)->right == NULL) p = NULL;
    else if((*root)->left != NULL && (*root)->right == NULL) p = (*root)->left;
    else if((*root)->left != NULL && (*root)->right != NULL) p = (*root)->right;

    Node *q = (*root);
    (*root) = p;

    node_delete(&q);
    
    return TRUE;
}

boolean avl_remove_node(Avl *avl, int year){
    if (avl->root != NULL) return avl_remove_aux(&(avl->root), year);
    return FALSE;
} 

static void avl_delete_aux(Node **root) {
    if (*root != NULL) {
        avl_delete_aux(&((*root)->left));
        avl_delete_aux(&((*root)->right));
        game_delete(&(*root)->game);
        free(*root);
    }
}

void avl_delete(Avl **avl) {
    avl_delete_aux(&(*avl)->root);
    free(*avl);
    *avl = NULL;
}
static void print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    game_print(root->game);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void avl_imprimir(Avl *avl)
{
    // Pass initial space count as 0
    print2DUtil(avl->root, 0);
}

