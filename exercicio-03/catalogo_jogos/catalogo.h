#ifndef CATALOGO_H
#define CATALOGO_H

#include <stdbool.h>
#include "jogo.h"

typedef struct _catalogo Catalogo;

Catalogo *create_catalogo(int initial_capacity);

void resize_catalogo(Catalogo *catalogo, int size); 
int get_size(Catalogo *catalogo);

char *readLine();
bool cadastrar_jogo(Catalogo *catalogo);
Jogo *get_jogo(Catalogo *catalogo, int pos);

void busca_por_ano(Catalogo *catalogo, int ano);
void busca_por_empresa(Catalogo *catalogo, char *empresa);

void apagar_catalogo(Catalogo **catalogo_ref);

#endif // CATALOGO_H