#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Customer/Customer.h"
#include "Util/Util.h"
#include "Tree/Tree.h"

boolean register_customer(Tree *tree, Customer *customer);

int main(){
	
	int n;
	Customer *new_customer = NULL;
	Tree *bank_tree = tree_create();

	scanf("%d\n", &n);

	for (int i = 0; i < n; i++){
		if (register_customer(bank_tree, new_customer)) new_customer = NULL;
	}

	char op;   
	scanf("%c", &op);      
	scanf("%*c");                                                                                                                                    

	if (op == 'I') {

		if (register_customer(bank_tree, new_customer)) new_customer = NULL;
		tree_print_pre_order(bank_tree);

	} else if (op == 'B'){

		char *cpf_s = readLine();
		CPF_list *cpf_p = cpf_create(cpf_s); 

		Customer *p = customer_search(raiz(bank_tree), cpf_p); 

		if (p != NULL) customer_print(p);
		else printf("Pessoa nao encontrada.\n");
		printf("\n");

		free(cpf_s);
		cpf_delete(&cpf_p);

	} else if (op == 'R'){

		char *cpf_s = readLine();
		CPF_list *cpf_p = cpf_create(cpf_s); 

		Customer *rem_customer = tree_remove_node(bank_tree, cpf_p);

		if (rem_customer != NULL) {
			customer_print(rem_customer);
			customer_delete(&rem_customer);
			tree_print_pre_order(bank_tree);
		}

		free(cpf_s);
		cpf_delete(&cpf_p);
	}

	tree_delete(&bank_tree);

	return 0;
}

boolean register_customer(Tree *tree, Customer *new_customer){
		char *cpf, *nome, *idade_char, *saldo;
		int idade;

		cpf = readLine();
		nome = readLine();

		idade_char = readLine();
		idade = atoi(idade_char);
		free(idade_char);

		saldo = readLine();

		new_customer = customer_create(cpf, nome, idade, saldo);
		
		if (new_customer != NULL) return tree_insert_customer(tree, new_customer);
		return FALSE;
}