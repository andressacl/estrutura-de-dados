#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#include "Tree.h" 

static Customer *troca_min_dir(Node *troca, Node *raiz, Node *ant);

struct node_st {
	Customer *customer;
	Node *direita;
	Node *esquerda;
};

struct tree_st{
	Node *raiz;
	int profundidade;
};

static Node *node_create(Customer *customer){
	Node *new_node = (Node*) malloc(sizeof(Node));

	new_node->customer = customer;
	new_node->direita = NULL;
	new_node->esquerda = NULL;

	return new_node;
}

Tree *tree_create(){
	Tree *new_tree = (Tree*) malloc(sizeof(Tree));

	if (new_tree != NULL){
		new_tree->raiz = NULL;
		new_tree->profundidade = -1;
	}

	return new_tree;
}

static Node *tree_insertion(Node *raiz, Customer *customer) {
    if (raiz != NULL) {

    	if (maior_cpf(customer, raiz->customer) == customer){
    		if (raiz->direita == NULL){
    			raiz->direita = node_create(customer);
    			return raiz->direita;
    		} else {
    			tree_insertion(raiz->direita, customer);
    		}

    	} else {
    		if (raiz->esquerda == NULL){
    			raiz->esquerda = node_create(customer);
    			return raiz->esquerda;
    		} else {
    			tree_insertion(raiz->esquerda, customer);
    		}
    	}
    	
	}
	return NULL;
}

boolean tree_insert_customer(Tree *tree, Customer *customer){
	if (tree->raiz == NULL)
        return((tree->raiz = node_create(customer)) != NULL);
    else
        return(tree_insertion(tree->raiz, customer) != NULL);
}

static void pre_order_recursion(Node *raiz) {
    if (raiz != NULL) {
       	CPF_print(get_cpf(raiz->customer));
        pre_order_recursion(raiz->esquerda);
        pre_order_recursion(raiz->direita);
    } 
}

void tree_print_pre_order(Tree *tree){
	printf("Preorder\n");
    pre_order_recursion(tree->raiz);
    printf("\n");
}

Node *raiz(Tree *tree){
    return tree->raiz;
}

Customer *get_customer(Node *node){
	return node->customer;
}

Customer *customer_search(Node *raiz, CPF_list *cpf){
	if (raiz == NULL) return NULL;
	if (igual(cpf, get_cpf(raiz->customer))) return raiz->customer;

	if (maior(cpf, get_cpf(raiz->customer))) return customer_search(raiz->direita, cpf);
	return customer_search(raiz->esquerda, cpf);
}

static Customer *tree_remove_aux(Node **raiz, CPF_list *cpf){
    Node *noRemovido;

    if(*raiz == NULL) return NULL;
  
    if(igual(cpf, get_cpf((*raiz)->customer))) {

        if ((*raiz)->esquerda == NULL || (*raiz)->direita == NULL){

            noRemovido = *raiz;

            if((*raiz)->esquerda == NULL) {
                *raiz = (*raiz)->direita;
            } else {
                *raiz = (*raiz)->esquerda;
            }

            Customer *customer_p = noRemovido->customer;
            free(noRemovido);
            return customer_p;

        } else {
            return troca_min_dir((*raiz)->direita, (*raiz), (*raiz));
        }

    } else {
        if(maior(cpf, get_cpf((*raiz)->customer)))
            return tree_remove_aux(&(*raiz)->direita, cpf);
        else
            return tree_remove_aux(&(*raiz)->esquerda, cpf);
    }
}


static Customer *troca_min_dir(Node *troca, Node *raiz, Node *ant) {
    if(troca->esquerda != NULL) return troca_min_dir(troca->esquerda, raiz, troca);
    
    if(raiz == ant) {
        ant->direita = troca->direita;
    } else {
        ant->esquerda = troca->direita;
    }

    Customer *customer_p = raiz->customer;
    raiz->customer = troca->customer;
    free(troca);

    return customer_p;
}

Customer *tree_remove_node(Tree *tree, CPF_list *cpf){
    if (tree != NULL) return tree_remove_aux(&tree->raiz, cpf);
    return NULL;
}

static void tree_node_delete(Node **raiz) {
    if (*raiz != NULL) {
        tree_node_delete(&(*raiz)->esquerda);
        tree_node_delete(&(*raiz)->direita);
        customer_delete(&(*raiz)->customer);
        free(*raiz);
        *raiz = NULL;
    }
}

void tree_delete(Tree **tree_ref){
	Tree *tree = *tree_ref;
	tree_node_delete(&tree->raiz);

	free(tree);
	tree_ref = NULL;
}