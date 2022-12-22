#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cpf.h"

typedef struct cpfnode_st CPF_node;

struct cpfnode_st {
	int val;
	CPF_node *next;
};

struct cpflist_st {
	CPF_node *start;
};

static CPF_node *cpf_create_node(int val){

	CPF_node *new_node = (CPF_node*) malloc(sizeof(CPF_node));
	new_node->val = val;
	new_node->next = NULL;

	return new_node;
}
 
static void cpf_insert_nodes(CPF_list *cpf_p, char *cpf_s){
	int tam = strlen(cpf_s);
	char str_aux[4];

	int ind_atual = tam-2; 
	strncpy(str_aux, cpf_s+ind_atual, 2);
	str_aux[2] = '\0';

	int val = atoi(str_aux);
	cpf_p->start = cpf_create_node(val);

	for (int i = 0; i < 3; i++){
		ind_atual = ind_atual - 4;
		strncpy(str_aux, cpf_s+(ind_atual), 3);
		str_aux[3] = '\0';

		val = atoi(str_aux);

		CPF_node *p = cpf_p->start;
		while(p->next != NULL){
			p = p->next;
		}
		p->next = cpf_create_node(val);
	}
}

CPF_list *cpf_create(char *cpf){

	CPF_list *new_cpf = (CPF_list*) malloc(sizeof(CPF_list));
	
	cpf_insert_nodes(new_cpf, cpf);

	return new_cpf;
}

static void aux_print(CPF_list *cpf_list, CPF_node *node_atual){
	if (node_atual->next == NULL){
		printf("%.3d", node_atual->val);
		return;
	} else {
		aux_print(cpf_list, node_atual->next);

		if (node_atual == cpf_list->start) printf("%.2d", node_atual->val);
		else printf("%.3d", node_atual->val);
	}
}

static void aux_print_format(CPF_list *cpf_list, CPF_node *node_atual){
	if (node_atual->next == NULL){
		printf("%.3d", node_atual->val);
		return;
	} else {
		aux_print_format(cpf_list, node_atual->next);
		
		if (node_atual == cpf_list->start) printf("-%.2d", node_atual->val);
		else printf(".%.3d", node_atual->val);
	}
}

void CPF_print(CPF_list *cpf_list){
	aux_print(cpf_list, cpf_list->start);
	printf("\n");
}

void CPF_format_print(CPF_list *cpf_list){
	aux_print_format(cpf_list, cpf_list->start);
	printf("\n");
}

boolean maior(CPF_list *cpf1, CPF_list *cpf2){
	boolean ctrl = FALSE;

	CPF_node *p = cpf1->start;
	CPF_node *q = cpf2->start;

	while (p != NULL){

		if (p->val > q->val){
			ctrl = TRUE;
		}

		if (p->val < q->val) {
			ctrl = FALSE;
		}

		p = p->next;
		q = q->next;
	}

	return ctrl;
}

boolean igual(CPF_list *cpf1, CPF_list *cpf2){
	CPF_node *p = cpf1->start;
	CPF_node *q = cpf2->start;

	while (p != NULL){
		if (p->val != q->val){
			return FALSE;
		}

		p = p->next;
		q = q->next;
	}

	return TRUE;
}

static void cpf_node_delete(CPF_node **node_ref){
	CPF_node *node = *node_ref;

	node->next = NULL;

	free(node);
	*node_ref = NULL;
}

void cpf_delete(CPF_list **cpf_ref){
	CPF_list *cpf = *cpf_ref;

	CPF_node *p = cpf->start;
	CPF_node *q = p->next;

	while(q != NULL){
		cpf_node_delete(&p);
		p = q;
		q = q->next;
	}

	cpf_node_delete(&p);
	cpf->start = NULL;

	free(cpf);
	*cpf_ref = NULL;
}