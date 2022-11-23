#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Util/Util.h"
#include "Node/Node.h"
#include "Lista/Lista.h"

#define TAM_NODE 4

int get_op_id_by_string(char *op_name);

int main(){
	
	int num_op, op_id;
	char op[30], num1[30], num2[30];

	scanf("%d", &num_op);

	for (int i = 0; i < num_op; i++){

		scanf("%s %s %s", op, num1, num2);

		op_id = get_op_id_by_string(op); 
		
		Lista *lista_num1 = lista_create(TAM_NODE);
		lista_set_from_string(lista_num1, num1);

		Lista *lista_num2 = lista_create(TAM_NODE);
		lista_set_from_string(lista_num2, num2);

		printf("Resultado :: ");

		switch(op_id) {
			case 1: {
				Lista *lista_soma = soma(lista_num1, lista_num2);
				num_print(lista_soma);
				lista_delete(&lista_soma);
				break;
			} 
			case 2: {
				boolean_print(maior(lista_num1, lista_num2));
				break;
		    } 
		    case 3: {
				boolean_print(menor(lista_num1, lista_num2));
				break;
			}
			case 4: {
				boolean_print(igual(lista_num1, lista_num2));
			}
		}

		lista_delete(&lista_num1);
		lista_delete(&lista_num2);
	}

	return 0;
}

int get_op_id_by_string(char *op_name){
	if (strcmp(op_name, "soma") == 0) return 1; 
	if (strcmp(op_name, "maior") == 0) return 2;
	if (strcmp(op_name, "menor") == 0) return 3;
	if (strcmp(op_name, "igual") == 0) return 4;
	return -1;
}