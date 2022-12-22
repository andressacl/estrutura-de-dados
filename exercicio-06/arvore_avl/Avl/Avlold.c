#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "Avl.h" 
#define COUNT 8

static Node *node_create(Game *game);
static Node *node_insert(Node *root, Game *game);

static boolean node_maior(Node *root, Game *game);
static boolean node_menor(Node *root, Game *game);

static Node *avl_insert_node_and_rotate(Node *root, Game *game);
static Node *select_and_execute_rotation(Node *root, Game *game);

static boolean desbalanceamento_positivo(Node *root);
static boolean desbalanceamento_negativo(Node *root);

static Node *troca_max_left(Node *troca, Node *root, Node *ant);

struct node_st {
	Game *game;
	Node *right;
	Node *left;
    int height;
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
      new_node->height = 0;
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

int node_height(Node* root) {
    if (root == NULL) 
        return -1;
    else 
        return root->height;
}

int node_get_balance(Node *node){
    if (node == NULL) return 0;
    return node_height(node->left)-node_height(node->right);
}

boolean avl_insert(Avl *avl, Game *game){
    avl->root = avl_insert_node_and_rotate(avl->root, game);
    return avl->root != NULL;
}

static Node *avl_insert_node_and_rotate(Node *root, Game *game) {
    root = node_insert(root, game);

    root->height = max(node_height(root->left),
                       node_height(root->right)) + 1;

    root = select_and_execute_rotation(root, game);

    return root;
}

static Node *node_insert(Node *root, Game *game) {
    if (root == NULL) {
        root = node_create(game);
    } else if (node_maior(root, game)) {
        root->right = avl_insert_node_and_rotate(root->right, game);
    } else if (node_menor(root, game)) {
        root->left = avl_insert_node_and_rotate(root->left, game);
    }
    return root;
}

static Node *select_and_execute_rotation(Node *root, Game *game) {
    if (desbalanceamento_negativo(root)) {
        if (node_maior(root->right, game))
            root = left_rotation(root);
        else  
            root = right_left_rotation(root);
    }

    if (desbalanceamento_positivo(root)) {
        if (node_menor(root->left, game))
            root = right_rotation(root);
        else
            root = left_right_rotation(root);
    }
    return root;
}

static boolean node_maior(Node *root, Game *game) {
    return game_maior(game, root->game);
}

static boolean node_menor(Node *root, Game *game) {
    return game_maior(root->game, game);
}

static boolean desbalanceamento_positivo(Node *root) {
    return node_height(root->left) - node_height(root->right) == 2;
}

static boolean desbalanceamento_negativo(Node *root) {
    return node_height(root->left) - node_height(root->right) == -2;
}

Node *right_rotation(Node *a) {
    Node *b = a->left;
    a->left = b->right;
    b->right = a;

    a->height = max(node_height(a->left), node_height(a->right)) + 1;
    b->height = max(node_height(b->left), a->height) + 1;
    
    return b;
}

Node *left_rotation(Node *a) {
    Node *b = a->right;
    a->right = b->left;
    b->left = a;

    a->height = max(node_height(a->left), node_height(a->right)) + 1;
    b->height = max(node_height(b->right), a->height) + 1;
    
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

// Falta implementar função de busca e função de remoção
Game *game_search(Node *root, int year){
    if (root == NULL) return NULL;
    if (get_year(root->game) == year) return root->game;

    if (get_year(root->game) < year) return game_search(root->right, year);
    return game_search(root->left, year);
}

void node_delete(Node **node_ref){
    Node *node = *node_ref;
    game_delete(&(node->game));
    free(node->right);
    free(node->left);
    free(node);
    *node_ref = NULL;
}

static Node *avl_remove_aux(Node **root, int year){
    // Node *rm_node;

    if(*root == NULL) return NULL;
  
    if (get_year((*root)->game) == year) {

        if ((*root)->left == NULL || (*root)->right == NULL){

            Node *temp = (*root)->left ? (*root)->left : (*root)->right;

            if (temp == NULL){
                temp = (*root);
                (*root) = NULL;
            }

            **root = *temp;
            free(temp);

        } else {
            Node *temp = troca_max_left((*root)->left, (*root), (*root));
            // game_delete(&temp);
            return temp;
        }

    } else {
        if(year > get_year((*root)->game))
            return avl_remove_aux(&(*root)->right, year);
        else
            return avl_remove_aux(&(*root)->left, year);
    }

    if ((*root) == NULL) return (*root);

    (*root)->height = 1 + max(node_height((*root)->left),
                              node_height((*root)->right));

    if (desbalanceamento_positivo((*root)) && 
        node_get_balance((*root)->left) >= 0)
        return right_rotation((*root));

    if (desbalanceamento_positivo((*root)) && 
        node_get_balance((*root)->left) < 0)
        return left_right_rotation((*root));

    if (desbalanceamento_negativo((*root)) && 
        node_get_balance((*root)->right) <= 0)
        return left_rotation((*root));

    if (desbalanceamento_negativo((*root)) && 
        node_get_balance((*root)->right) > 0)
        return right_left_rotation((*root));

    return (*root);
}


static Node *troca_max_left(Node *troca, Node *root, Node *ant) {
    if(troca->right != NULL) return troca_max_left(troca->right, root, troca);
    
    if(root == ant) {
        ant->right = troca->right;
    } else {
        ant->right = troca->left;
    }

    // Game *game_p = root->game;
    // root->game = troca->game;
    // free(troca);

    return root;
} 

Node *avl_remove_node(Avl *avl, int year){
    if (avl != NULL) return avl_remove_aux(&avl->root, year);
    return NULL;
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

