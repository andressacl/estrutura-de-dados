#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
#include "jogo.h"
#include "catalogo.h"

char *readLine();

int main(){
	
	Catalogo *novo_catalogo = create_catalogo(10);

	bool ctrl = true;
	char cmd;

	while (ctrl == true){
		ctrl = register_jogo(novo_catalogo);
	}

	scanf("%c", &cmd);
	
	while (cmd != 'F'){

		if (cmd == 'A'){
			int ano;
			scanf("%i", &ano);
			search_by_year(novo_catalogo, ano);

		} else if (cmd == 'E'){
			scanf("%*c%*c"); //Optou-se por fazer o consumo de caracteres apenas para Windows
			
			char *empresa = readLine();
			search_by_company(novo_catalogo, empresa);
			free(empresa);
		}

		scanf("%c", &cmd);
	}

	delete_catalogo(&novo_catalogo);

	return 0;
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