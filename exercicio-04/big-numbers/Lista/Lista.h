#ifndef LISTA_H
#define LISTA_H

#include "../Util/Util.h"
#include "../Node/Node.h"

typedef struct lista_st Lista;

Lista *lista_create(int dig_node);
void lista_insert_node(Lista *lista, int val);
void lista_set_from_string(Lista *lista, char *big_number);

void num_print(Lista *lista);

Lista *soma(Lista *lista1, Lista *lista2);
boolean maior(Lista *lista1, Lista *lista2);
boolean menor(Lista *lista1, Lista *lista2);
boolean igual(Lista *lista1, Lista *lista2);

void lista_delete(Lista **lista_end);

#endif //LISTA_H