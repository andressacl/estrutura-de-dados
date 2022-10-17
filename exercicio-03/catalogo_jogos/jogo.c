#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"

struct _jogo{
	char nome[100];
	char empresa_prod[100];
	int ano_lan;
};

Jogo *create_jogo(char nome[100], char empresa_prod[100], int ano_lan){
	Jogo *novo_jogo = (Jogo*) calloc(1, sizeof(Jogo));
	strcpy(novo_jogo->nome, nome);
	strcpy(novo_jogo->empresa_prod, empresa_prod);
	novo_jogo->ano_lan = ano_lan;
	return novo_jogo;
}

int get_ano(Jogo *jogo){
	return jogo->ano_lan;
}

char *get_empresa(Jogo *jogo){
	return jogo->empresa_prod;
}

void print_jogo(Jogo *jogo){
	printf("Nome do jogo: %s\n", jogo->nome);
	printf("Empresa produtora: %s\n", jogo->empresa_prod);
	printf("Ano de lançamento: %i\n", jogo->ano_lan);
}

void print_name_jogo(Jogo *jogo){
	printf("%s\n", jogo->nome);
}

void delete_jogo(Jogo **jogo_ref){
	Jogo *jogo = *jogo_ref;
	free(jogo);
	*jogo_ref = NULL;
}