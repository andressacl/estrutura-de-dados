#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Customer.h"

struct customer_st {
	char *name;
	// CPF *cpf;
	int idade;
	char *saldo;
};

Customer *customer_create(char *cpf, char *name, int idade, char *saldo){
	Customer *new_customer = (Customer*) calloc(1, sizeof(Customer));

	new_customer->name = name;
	new_customer->idade = idade;
	new_customer->saldo = saldo;

	return new_customer;
}

void customer_print(Customer *customer){
	printf("Conta :: %s\n", customer->name);
	// printf("CPF :: ") /// cpf_print(customer->cpf);
	printf("Idade :: %d\n", customer->idade);
	printf("Saldo :: R$ %s\n", customer->saldo);
}

void customer_delete(Customer **customer_ref){
	Customer *customer = *customer_ref;

	free(customer->name);
	customer->name = NULL;

	// delete_cpf(cpf);
	// customer->cpf = NULL;

	free(customer->saldo);
	customer->saldo = NULL;

	free(customer);
	*customer_ref = NULL;
}