#ifndef CATALOGO_H
#define CATALOGO_H

#include <stdbool.h>
#include "jogo.h"

typedef struct _catalogo Catalogo;

Catalogo *create_catalogo(int initial_capacity);

void resize_catalogo(Catalogo *catalogo, int size); 
int get_size(Catalogo *catalogo);

bool register_jogo(Catalogo *catalogo);
Jogo *get_jogo(Catalogo *catalogo, int pos);

void search_by_year(Catalogo *catalogo, int ano);
void search_by_company(Catalogo *catalogo, char *empresa);

void delete_catalogo(Catalogo **catalogo_ref);

#endif // CATALOGO_H