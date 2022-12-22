#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "../Util/Util.h"
#include "../CPF/Cpf.h"

typedef struct customer_st Customer;

Customer *customer_create(char *cpf, char *name, int idade, char *saldo);

void customer_print(Customer *customer);
Customer *maior_cpf(Customer *customer1, Customer *customer2);
CPF_list *get_cpf(Customer *customer);

void customer_delete(Customer **customer);

#endif //CUSTOMER_H