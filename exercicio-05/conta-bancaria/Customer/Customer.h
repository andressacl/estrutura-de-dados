#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "../Util/Util.h"

typedef struct customer_st Customer;

Customer *customer_create(char *cpf, char *name, int idade, char *saldo);

void customer_print(Customer *customer);

void customer_delete(Customer **customer);

#endif //CUSTOMER_H