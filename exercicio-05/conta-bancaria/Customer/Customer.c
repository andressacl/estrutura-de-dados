#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Customer.h"

struct customer_st {
	char *name;
	CPF_list *cpf;
	int idade;
	char *saldo;
};

Customer *customer_create(char *cpf, char *name, int idade, char *saldo){
	Customer *new_customer = (Customer*) calloc(1, sizeof(Customer));

	new_customer->name = name;
	new_customer->idade = idade;
	new_customer->saldo = saldo;
	new_customer->cpf = cpf_create(cpf); 
	free(cpf);

	return new_customer;
}

CPF_list *get_cpf(Customer *customer){
	return customer->cpf;
}

Customer *maior_cpf(Customer *customer1, Customer *customer2){
	if (maior(customer1->cpf, customer2->cpf)) return customer1;
	return customer2;
}

void customer_print(Customer *customer){
	printf("Conta :: %s\n", customer->name);
	printf("CPF :: ");
	CPF_format_print(customer->cpf);
	printf("Idade :: %d\n", customer->idade);
	printf("Saldo atual :: R$ %s\n", customer->saldo);
}

void customer_delete(Customer **customer_ref){
	Customer *customer = *customer_ref;

	free(customer->name);
	customer->name = NULL;

	cpf_delete(&(customer->cpf));
	customer->cpf = NULL;

	free(customer->saldo);
	customer->saldo = NULL;

	free(customer);
	*customer_ref = NULL;
}