#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
#include "jogo.h"
#include "catalogo.h"

int main(){
	
	Catalogo *novo_catalogo = create_catalogo(10);

	bool ctrl = true;
	char cmd;

	while (ctrl == true){
		ctrl = cadastrar_jogo(novo_catalogo);
	}
	
	while (cmd != 'F'){
		scanf("%c", &cmd);

		if (cmd == 'A'){
			int ano;
			scanf("%i", &ano);
			busca_por_ano(novo_catalogo, ano);

		} else if (cmd == 'E'){
			scanf("%*c");
			scanf("%*c");
			
			char *empresa = readLine();
			busca_por_empresa(novo_catalogo, empresa);
			free(empresa);
		}
	}

	apagar_catalogo(&novo_catalogo);

	return 0;
}