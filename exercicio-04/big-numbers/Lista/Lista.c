#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Lista.h"

static void soma_same_sign(Lista *lista1, Lista *lista2, Lista *l_soma);
static void soma_dif_sign(Lista *lista1, Lista *lista2, Lista *l_soma);

struct lista_st {
	Node *start;
	int tam;
	int dig_node;
	boolean sign;
};

Lista *lista_create(int dig_node){
	Lista *new_lista = (Lista*) calloc(1, sizeof(Lista));
	new_lista->dig_node = dig_node;
	new_lista->tam = 0;
	new_lista->sign = FALSE;

	return new_lista;
}

void lista_insert_node(Lista *lista, int val){
	Node *new_node = node_create(val);

	if (lista->start == NULL) {
		lista->start = new_node;
	} else {
		Node *p = lista->start;

		while(node_next(p) != NULL){
			p = node_next(p);
		}
		node_set_next(p, new_node);
	}
	lista->tam++;
}

void lista_set_from_string(Lista *lista, char *big_number){ 
	int n_char = strlen(big_number);

	if (big_number[0] == '-'){
		lista->sign = TRUE;

		n_char--;
		char *aux = (char*)calloc(n_char+1, sizeof(char));
		strncpy(aux, big_number+1, n_char);

		strncpy(big_number, aux, n_char);
		big_number[n_char] = '\0';

		free(aux);
	}

	int tam_item = lista->dig_node;

	int tam_lista = (n_char/tam_item);
	if (n_char % tam_item != 0) tam_lista++;

	char *str_aux = (char*) calloc(tam_item+1, sizeof(char));
	int ind_atual = n_char;
	int val;

	for (int i = 1; i < tam_lista; i++){
		ind_atual = ind_atual - tam_item;
		strncpy(str_aux, big_number+(ind_atual), tam_item);
		str_aux[tam_item] = '\0';

		val = atoi(str_aux);

		lista_insert_node(lista, val);
	}

	strncpy(str_aux, big_number, ind_atual);
	str_aux[ind_atual] = '\0';

	val = atoi(str_aux);

	lista_insert_node(lista, val);

	free(str_aux);
}

boolean isNegative(Lista *lista){
	return lista->sign;
}

Lista *soma(Lista *lista1, Lista *lista2){
	Lista *soma = lista_create(lista1->dig_node);

	if (isNegative(lista1) == isNegative(lista2)){
		if (isNegative(lista1) == FALSE){	
			soma_same_sign(lista1, lista2, soma);
		} else {						
			soma_same_sign(lista1, lista2, soma);
		}
	} else {
		soma_dif_sign(lista1, lista2, soma);
	}

	return soma;
}

static void soma_same_sign(Lista *lista1, Lista *lista2, Lista *l_soma){
	int ctrl = power(10, lista1->dig_node);
	int carry = 0;
	int total, sum;

	l_soma->sign = lista1->sign;

	Node *p = lista1->start;
	Node *q = lista2->start;
	
	while(p != NULL && q != NULL){
		total = carry + node_val(p) + node_val(q);
		sum = total % ctrl;
		carry = total / ctrl;

		lista_insert_node(l_soma, sum);

		p = node_next(p);
		q = node_next(q);
	}

	while(p != NULL){
		total = carry + node_val(p);
		sum = total % ctrl;
		carry = total / ctrl;

		lista_insert_node(l_soma, sum);

		p = node_next(p);
	}

	while(q != NULL){
		total = carry + node_val(q);
		sum = total % ctrl;
		carry = total / ctrl;

		lista_insert_node(l_soma, sum);

		q = node_next(q);
	}

	if (carry != 0){
		lista_insert_node(l_soma, carry);
	}

	return;
}

static void soma_dif_sign(Lista *lista1, Lista *lista2, Lista *l_soma){
	int sum;

	if ((maior(lista1, lista2) == TRUE && isNegative(lista1) == FALSE) ||
		(maior(lista2, lista1) == TRUE && isNegative(lista2) == FALSE)){
		l_soma->sign = FALSE;
	} else {
		l_soma->sign = TRUE;
	}

	Node *p = lista1->start;
	Node *q = lista2->start;
	
	while(p != NULL && q != NULL){
		sum = abs(node_val(p)-node_val(q));

		lista_insert_node(l_soma, sum);

		p = node_next(p);
		q = node_next(q);
	}

	while(p != NULL){
		sum = node_val(p);

		lista_insert_node(l_soma, sum);

		p = node_next(p);
	}

	while(q != NULL){
		sum = node_val(q);

		lista_insert_node(l_soma, sum);

		q = node_next(q);
	}

	return;
}

static boolean comparar_numeros(Lista *lista1, Lista *lista2){
	boolean ctrl = FALSE;

	Node *p = lista1->start;
	Node *q = lista2->start;

	while (p != NULL){

		if (node_val(p) > node_val(q)) {
			ctrl = TRUE;
		}

		if (node_val(p) < node_val(q)) {
			ctrl = FALSE;
		}

		p = node_next(p);
		q = node_next(q);
	}

	return ctrl;
}

boolean maior(Lista *lista1, Lista *lista2){
	if (isNegative(lista1) != isNegative(lista2)) 
		return isNegative(lista1) < isNegative(lista2);

	
	if (lista1->tam != lista2->tam){
		if (isNegative(lista1) == FALSE){
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
	if (lista1->tam != lista2->tam ||
		isNegative(lista1) != isNegative(lista2)) return FALSE;

	Node *p = lista1->start;
	Node *q = lista2->start;

	int i = 0;

	while (i < lista1->tam){
		if (node_val(p) != node_val(q)) return FALSE;
		p = node_next(p);
		q = node_next(q);
		i++;
	}
	return TRUE;
}

static void aux_print(Lista *lista, Node *node_atual){
	if (node_next(node_atual) == NULL){
		if (isNegative(lista)){
			printf("-");
		}

		printf("%d", node_val(node_atual));
		return;
	} else {
		aux_print(lista, node_next(node_atual));
		printf("%.4d", node_val(node_atual));
	}
}

void num_print(Lista *lista){
	aux_print(lista, lista->start);
	printf("\n");
}

void lista_delete(Lista **lista_ref){
	Lista *lista = *lista_ref;

	Node *p = lista->start;
	Node *q = node_next(lista->start);

	while(q != NULL){
		node_delete(&p);
		p = q;
		q = node_next(q);
	}

	node_delete(&p);
	lista->start = NULL;

	free(lista);
	*lista_ref = NULL;
}