#include <stdio.h>

void contarTroco(int val, int *vetor);


int main(){

	int mval, moedas[6];

	scanf("%i", &mval);

	contarTroco(mval, moedas);

	printf("O valor consiste em %d moedas de 1 real\n", moedas[0]);
	printf("O valor consiste em %d moedas de 50 centavos\n", moedas[1]);
	printf("O valor consiste em %d moedas de 25 centavos\n", moedas[2]);
	printf("O valor consiste em %d moedas de 10 centavos\n", moedas[3]);
	printf("O valor consiste em %d moedas de 5 centavos\n", moedas[4]);
	printf("O valor consiste em %d moedas de 1 centavo\n", moedas[5]);


return 0;
}

void contarTroco(int val, int *vetor){
	
	int i, valMoedas[6] = {100, 50, 25, 10, 5, 1};

	for (i = 0; i < 6; i++){
		vetor[i] = val / valMoedas[i];
		val = val % valMoedas[i];
	}
}






