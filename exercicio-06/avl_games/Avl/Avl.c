#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "Avl.h" 
#define COUNT 8

static Node *node_create(Game *game);
static Node *node_insert(Node *root, Game *game);

static boolean game_at_right(Node *root, Game *game);
static boolean game_at_left(Node *root, Game *game);

static Node *avl_insert_node_and_rotate(Node *root, Game *game);
static Node *select_and_execute_rotation(Node *root, Game *game);

static boolean desbalanceamento_positivo(Node *root);
static boolean desbalanceamento_negativo(Node *root);

static boolean avl_remove_aux(Node **root, Game *game, Game *og_game);

// Structs
struct node_st {
    Game *game;
    Node *right;
    Node *left;
};

struct avl_st {
    Node *root;
    int depth;
};

// Criação
static Node *node_create(Game *game){
  Node *new_node = (Node*) calloc(1, sizeof(Node));

  if (new_node != NULL){
      new_node->game = game;
      new_node->right = NULL;
      new_node->left = NULL;
  }

  return new_node;
}

Avl *avl_create(){
    Avl *new_avl = (Avl*) calloc(1, sizeof(Avl));

    if (new_avl != NULL) {
      new_avl->root = NULL; 
      new_avl->depth = -1;
    }

    return new_avl;
}

//Auxiliares de modularização
Node *avl_root(Avl *avl){
    return avl->root;
}

Game *get_game(Node *node){
    return node->game;
}

int node_height(Node *node){
    if (node == NULL) return 0;

    int nl = 0;
    int nr = 0;

    if(node->left != NULL) 
        nl = node_height(node->left);

    if(node->right != NULL) 
        nr = node_height(node->right);

    if (nl > nr) return (nl+1);
    else return (nr+1);
}

static boolean game_at_right(Node *root, Game *game) {
    return game_maior(game, root->game);
}

static boolean game_at_left(Node *root, Game *game) {
    return game_maior(root->game, game);
}

Node *node_max(Node *node){
    Node *p = node;

    while(p->right != NULL){
        p = p->right;
    }

    return p;
}

// Rotações
Node *right_rotation(Node *a) {
    Node *b = a->left;
    a->left = b->right;
    b->right = a;

    return b;
}

Node *left_rotation(Node *a) {
    Node *b = a->right;
    a->right = b->left;
    b->left = a;
    
    return b;
}

Node *left_right_rotation(Node *a) {
    a->left = left_rotation(a->left);
    return right_rotation(a);
}

Node *right_left_rotation(Node *a) {
    a->right = right_rotation(a->right);
    return left_rotation(a);
}


// Balanceamento
int node_get_balance(Node *node){
    if (node == NULL) return 0;
    return node_height(node->left)-node_height(node->right);
}

static boolean desbalanceamento_positivo(Node *root) {
    return node_height(root->left) - node_height(root->right) == 2;
}

static boolean desbalanceamento_negativo(Node *root) {
    return node_height(root->left) - node_height(root->right) == -2;
}

Node *avl_rebalance(Node **node){

    if (desbalanceamento_negativo(*node)){

        if (node_get_balance((*node)->right) > 0)
            return right_left_rotation(*node);
        else 
            return left_rotation(*node);
        
    } else if (desbalanceamento_positivo(*node)){
        
        if (node_get_balance((*node)->left) < 0)
            return left_right_rotation(*node);
        else 
            return right_rotation(*node);

    }
    return (*node);

}

// Inserção
boolean avl_insert(Avl *avl, Game *game){
    avl->root = avl_insert_node_and_rotate(avl->root, game);
    return avl->root != NULL;
}

static Node *avl_insert_node_and_rotate(Node *root, Game *game) {
    root = node_insert(root, game);

    root = select_and_execute_rotation(root, game);

    return root;
}

static Node *node_insert(Node *root, Game *game) {
    if (root == NULL) {
        root = node_create(game);
    } else if (game_at_right(root, game)) {
        root->right = avl_insert_node_and_rotate(root->right, game);
    } else if (game_at_left(root, game)) {
        root->left = avl_insert_node_and_rotate(root->left, game);
    }
    return root;
}

static Node *select_and_execute_rotation(Node *root, Game *game) {
    if (desbalanceamento_negativo(root)) {
        if (game_at_right(root->right, game))
            root = left_rotation(root);
        else  
            root = right_left_rotation(root);
    }

    if (desbalanceamento_positivo(root)) {
        if (game_at_left(root->left, game))
            root = right_rotation(root);
        else
            root = left_right_rotation(root);
    }
    return root;
}

// Busca
Game *avl_search_game(Node *root, int year){
    if (root == NULL) return NULL;
    if (get_year(root->game) == year) return root->game;

    if (get_year(root->game) < year) return avl_search_game(root->right, year);
    return avl_search_game(root->left, year);
}

// Remoção
boolean avl_remove_game(Avl *avl, Game *game){
    if (avl->root != NULL) return avl_remove_aux(&(avl->root), game, game);
    return FALSE;
} 

static boolean avl_remove_aux(Node **root, Game *game, Game *og_game){

    if((*root) == NULL) return FALSE;

    if (game_at_right((*root), game)){
            avl_remove_aux(&(*root)->right, game, og_game);
            (*root) = avl_rebalance(&(*root));
            return TRUE;
    } else if (game_at_left((*root), game)) {
            avl_remove_aux(&(*root)->left, game, og_game);
            (*root) = avl_rebalance(&(*root));
            return TRUE;
    }

    if ((*root)->left != NULL && (*root)->right != NULL){
        Node *max_left = node_max((*root)->left);

        Game *rm_game = (*root)->game; 
        (*root)->game = max_left->game;

        // printf("rm game 2 filho");game_print(rm_game);
        game_delete(&rm_game);

        avl_remove_aux(&((*root)->left), (*root)->game, og_game);
        return TRUE;
    }
  
    Node *p;

    if((*root)->left == NULL && (*root)->right == NULL) p = NULL;
    else if((*root)->left != NULL && (*root)->right == NULL) p = (*root)->left;
    else if((*root)->left == NULL && (*root)->right != NULL) p = (*root)->right;

    Node *q = (*root);
    (*root) = p;

    if (q->game == og_game) game_delete(&(q->game));
    free(q);
    
    return TRUE;
}

// Impressão
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

static void print2DUtil(Node *root, int space){
    if (root == NULL) return;
    space += COUNT;

    print2DUtil(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    game_print(root->game);

    print2DUtil(root->left, space);
}

void avl_imprimir(Avl *avl) {
    print2DUtil(avl->root, 0);
}

// Desalocar memória
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