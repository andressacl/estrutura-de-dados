#include <stdio.h>
#include <stdlib.h>
#include<string.h>


typedef struct _jogo{
	char nome[100];
	char empresa_prod[100];
	int ano_lan;
} Jogo;

Jogo *criar_jogo(char nome[100], char empresa_prod[100], int ano_lan){
	Jogo *novo_jogo = (Jogo*) calloc(1, sizeof(Jogo));
	strcpy(novo_jogo->nome, nome);
	strcpy(novo_jogo->empresa_prod, empresa_prod);
	novo_jogo->ano_lan=ano_lan;
	return novo_jogo;
}

void print_jogo(Jogo *jogo){
	printf("Nome do jogo: %s\n", jogo->nome);
	printf("Empresa produtora: %s\n", jogo->empresa_prod);
	printf("Ano de lançamento: %i\n", jogo->ano_lan);

}

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

int main(){
	
	int ano;

	char *nome = readLine();
	char *empresa = readLine();
	scanf("%i", &ano);

	Jogo *meu_jogo = criar_jogo(nome, empresa, ano);
	print_jogo(meu_jogo);

	return 0;
}