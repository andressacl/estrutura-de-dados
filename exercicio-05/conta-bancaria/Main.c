#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Customer/Customer.h"
#include "Util/Util.h"

void register_customer(Customer *customer);

int main(){
	
	int n;
	Customer *new_customer;

	scanf("%d\n", &n);

	for (int i = 0; i < n; i++){
		register_customer(new_customer);
		new_customer = NULL;
	}

	// char *op;

	// if (op == 'I') {
	// 	register_customer(new_customer);
	// } else if (op == 'R'){
	// 	cpf = readLine();
	// 	remove_node(cpf);
	// } else if (op == 'B'){
	// 	cpf = readLine();
	// 	busca(cpf);
	// }

	return 0;
}

void register_customer(Customer *new_customer){
		char *cpf, *nome, *idade_char, *saldo;
		int idade;

		cpf = readLine();
		nome = readLine();
		idade_char = readLine();
		idade = atoi(idade_char);
		saldo = readLine();


		// printf("------");
		// printf("CPF: %s\n", cpf);
		// printf("Nome: %s\n", nome);
		// printf("Idade: %d\n", idade);
		// printf("Saldo: %s\n", saldo);

		new_customer = customer_create(cpf, nome, idade, saldo);
		customer_print(new_customer);
		// if (new_customer != NULL) tree_insert_customer(new_customer);
}