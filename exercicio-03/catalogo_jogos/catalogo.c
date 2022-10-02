#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogo.h"
#include "jogo.h"

char *readLine() {
    char *string = NULL;
    char currentInput;
    int index = 0;
    do {
        currentInput = (char)getchar();
        string = (char *) realloc(string, sizeof(char) * (index + 1));
        string[index] = currentInput;
        index++;
        if(currentInput == '\r')
        {
            currentInput = (char)getchar();
        }
    } while((currentInput != '\n') && (currentInput != EOF));
    string[index - 1] = '\0';
    return string;
}

typedef struct _catalogo {
	Jogo **data;
	int size;
	int capacity;
} Catalogo;

Catalogo *create_catalogo(int initial_capacity){
	Catalogo *new_catalogo = (Catalogo*) calloc(1, sizeof(Catalogo));
	new_catalogo->size = 0;
	new_catalogo->capacity = initial_capacity;
	new_catalogo->data = (Jogo**) calloc(initial_capacity, sizeof(Jogo*));
	return new_catalogo;
}

void resize_catalogo(Catalogo *catalogo, int size){
	int new_size = (size+1)*sizeof(Jogo*);
	catalogo->data = (Jogo**) realloc(catalogo->data, new_size);
	catalogo->capacity++;
}

bool cadastrar_jogo(Catalogo *catalogo){
	
	char *nome = readLine();
	if (*nome == 'F') {
		free(nome);
		return false;
	}

	char *empresa = readLine();

	int ano;
	scanf("%i\n", &ano);

	if (catalogo->size == catalogo->capacity){
		resize_catalogo(catalogo, catalogo->size);
	}

	int size = catalogo->size;
	catalogo->data[size] = criar_jogo(nome, empresa, ano);
	catalogo->size++;

	free(nome);
	free(empresa);

	return true;
	
};

Jogo *get_jogo(Catalogo *catalogo, int pos){
	return catalogo->data[pos];
}

int get_size(Catalogo *catalogo){
	return catalogo->size+1;
}

void busca_por_ano(Catalogo *catalogo, int ano_chave){
	int matches = 0;
	
	for (int i = 0; i < catalogo->size; i++){
		int ano_buscado = get_ano(catalogo->data[i]);
		if (ano_buscado == ano_chave){
			print_nome_jogo(catalogo->data[i]);
			matches++;
		}
	}

	if (matches == 0) printf("Nada encontrado\n");
}

void busca_por_empresa(Catalogo *catalogo, char *empresa_chave){
	int matches = 0;

	for (int i=0; i < catalogo->size; i++){
		char *empresa_buscada = get_empresa(catalogo->data[i]);
		if (strcmp(empresa_buscada, empresa_chave) == 0){
			print_nome_jogo(catalogo->data[i]);
			matches++;
		}
	}

	if (matches == 0) printf("Nada encontrado\n");
}

void apagar_catalogo(Catalogo **catalogo_ref){
	Catalogo *catalogo = *catalogo_ref;

	for (int i=0; i < catalogo->size; i++){
		apagar_jogo(&(catalogo->data[i]));
	}

	for (int j = catalogo->size; j < catalogo->capacity; j++){
		free(catalogo->data[j]);
	}

	free(catalogo->data);
	free(catalogo);
	*catalogo_ref = NULL;
}