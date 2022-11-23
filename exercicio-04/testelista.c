#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <math.h>

#include "Lista.h"

struct lista_st {
	Node *start;
	int tam;
	int dig_node;
	//boolean sign;
};

Lista *lista_create(int dig_node){
	Lista *new_lista = (Lista*) calloc(1, sizeof(Lista));
	new_lista->dig_node = dig_node;
	new_lista->tam = 0;
	//new_lista->sign = NULL;

	return new_lista;
}

void lista_set_from_string(Lista *lista, char *big_number){ //organizar melhor depois e adicionar o negativo
	int n_char = strlen(big_number);
	boolean isNegative = FALSE;

	if (big_number[0] == '-'){
		isNegative = TRUE;

		n_char--;
		char *aux = (char*)calloc(n_char+1, sizeof(char));
		strncpy(aux, big_number+1, n_char);

		strncpy(big_number, aux, n_char);
		big_number[n_char] = '\0';


		free(aux);
	}

	int tam_item = lista->dig_node;

	int tam = (n_char/tam_item);
	if (n_char % tam_item != 0) tam++;

	char *str_aux = (char*) calloc(tam_item+1, sizeof(char));
	int ind_atual = n_char;
	int val;
	Node *node_atual = NULL;
	Node *node_ant;

	node_ant = node_create(isNegative);
	lista->start = node_ant;

	lista->tam++;

	for (int i = 1; i < tam; i++){
		ind_atual = ind_atual - tam_item;
		strncpy(str_aux, big_number+(ind_atual), tam_item);
		str_aux[tam_item] = '\0';

		val = atoi(str_aux);

		node_atual = node_create(val);
		node_set_next(node_ant, node_atual);

		node_ant = node_atual;
		lista->tam++;
	}

	strncpy(str_aux, big_number, ind_atual);
	str_aux[ind_atual] = '\0';

	val = atoi(str_aux);

	node_atual = node_create(val);
	node_set_next(node_ant, node_atual);

	lista->tam++;

	free(str_aux);
}

void lista_print(Lista *lista){
	Node *p = lista->start;

	while(p != NULL){
		printf("(%d)", node_val(p));
		printf("-->");
		p = node_prox(p);
	}	

	printf("NULL\n");
}

void lista_add_first_node(Lista *lista, int val){
	lista->start = node_create(val);
	lista->tam++;
}

void lista_insert_node(Lista *lista, Node *node){
	Node *p = lista->start;
	while(node_prox(p) != NULL){
		p = node_prox(p);
	}
	node_set_next(p, node);
	lista->tam++;
}


boolean isNegative(Lista *lista){
	if (node_val(lista->start) == 0) return FALSE;
	return TRUE;
}

static void soma_same_sign(Lista *lista1, Lista *lista2, Lista *l_soma, int sign){
	int ctrl = power(10, lista1->dig_node);
	int carry = 0;
	int total, sum;
	Node *node_p;

	lista_add_first_node(l_soma, sign);

	Node *p = node_prox(lista1->start);
	Node *q = node_prox(lista2->start);
	
	while(p != NULL && q != NULL){
		total = carry + node_val(p) + node_val(q);
		sum = total % ctrl;
		carry = total / ctrl;

		node_p = node_create(sum);
		lista_insert_node(l_soma, node_p);

		p = node_prox(p);
		q = node_prox(q);
	}

	while(p != NULL){
		total = carry + node_val(p);
		sum = total % ctrl;
		carry = total / ctrl;

		node_p = node_create(sum);
		lista_insert_node(l_soma, node_p);

		p = node_prox(p);
	}

	while(q != NULL){
		total = carry + node_val(q);
		sum = total % ctrl;
		carry = total / ctrl;

		node_p = node_create(sum);
		lista_insert_node(l_soma, node_p);

		q = node_prox(q);
	}

	return;
}

static void soma_dif_sign(Lista *lista1, Lista *lista2, Lista *l_soma){
	int sum;
	Node *node_p;

	if ((maior(lista1, lista2) == TRUE && isNegative(lista1) == FALSE) ||
		(maior(lista2, lista1) == TRUE && isNegative(lista2) == FALSE)){
		lista_add_first_node(l_soma, 0);
	} else {
		lista_add_first_node(l_soma, 1);
	}

	Node *p = node_prox(lista1->start);
	Node *q = node_prox(lista2->start);
	
	while(p != NULL && q != NULL){
		sum = abs(node_val(p)-node_val(q));

		node_p = node_create(sum);
		lista_insert_node(l_soma, node_p);

		p = node_prox(p);
		q = node_prox(q);
	}

	while(p != NULL){
		sum = node_val(p);

		node_p = node_create(sum);
		lista_insert_node(l_soma, node_p);

		p = node_prox(p);
	}

	while(q != NULL){
		sum = node_val(q);

		node_p = node_create(sum);
		lista_insert_node(l_soma, node_p);

		q = node_prox(q);
	}

	return;
}

Lista *soma(Lista *lista1, Lista *lista2){
	Lista *soma = lista_create(lista1->dig_node);

	if (node_val(lista1->start) == node_val(lista2->start)){
		if (node_val(lista1->start) == 0){			//2 positivos
			soma_same_sign(lista1, lista2, soma, 0);
		} else {									//2 negativos
			soma_same_sign(lista1, lista2, soma, 1);
		}
	} else {
		soma_dif_sign(lista1, lista2, soma);
	}

	return soma;
}

static boolean comparar_numeros(Lista *lista1, Lista *lista2){
	boolean ctrl = FALSE;

	Node *p = node_prox(lista1->start);
	Node *q = node_prox(lista2->start);

	while (p != NULL){

		if (node_val(p) > node_val(q)) {
			ctrl = TRUE;
		}

		if (node_val(p) < node_val(q)) {
			ctrl = FALSE;
		}

		p = node_prox(p);
		q = node_prox(q);
	}

	return ctrl;
}

boolean maior(Lista *lista1, Lista *lista2){
	if (node_val(lista1->start) != node_val(lista2->start)) 
		return node_val(lista1->start) < node_val(lista2->start);

	
	if (lista1->tam != lista2->tam){
		if (node_val(lista1->start) == 0){
			return (lista1->tam > lista2->tam);
		} else {
			return (lista1->tam < lista2->tam);
		} 
	}

	return comparar_numeros(lista1, lista2);
}

boolean menor(Lista *lista1, Lista *lista2){
	if (maior(lista1, lista2) == FALSE && igual(lista1, lista2) == FALSE) return TRUE;
	return FALSE;
}

boolean igual(Lista *lista1, Lista *lista2){
	if (lista1->tam != lista2->tam) return FALSE;

	Node *p = node_prox(lista1->start);
	Node *q = node_prox(lista2->start);

	int i = 0;

	while (i < lista1->tam){
		if (node_val(p) != node_val(q)) return FALSE;
		p = node_prox(p);
		q = node_prox(q);
		i++;
	}
	return TRUE;

	return FALSE;
}


static void aux_print(Lista *lista, Node *node_atual){

	if (node_prox(node_atual) == NULL){
		if (node_val(lista->start) == 1){
			printf("-");
		}

		printf("%d", node_val(node_atual));

		return;
	} else {
		aux_print(lista, node_prox(node_atual));
		printf("%.4d", node_val(node_atual));
	}
}

void num_print(Lista *lista){
	aux_print(lista, node_prox(lista->start));
	printf("\n");
}

void lista_delete(Lista **lista_ref){
	Lista *lista = *lista_ref;

	Node *p = lista->start;
	Node *q = node_prox(lista->start);

	while(q != NULL){
		node_delete(&p);
		p = q;
		q = node_prox(q);
	}

	node_delete(&p);
	lista->start = NULL;

	free(lista);
	*lista_ref = NULL;
}