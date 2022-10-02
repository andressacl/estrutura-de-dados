#include <stdlib.h>
#include <stdio.h>

int main(){

    int *vet = calloc(1, sizeof(int));
    int i;
    scanf("%i", &i);
    vet[0]=i;

    printf("%i", vet[0]);

    free(vet);
    return 0;
}
