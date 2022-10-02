#include <stdio.h>
#include <stdlib.h>
#include "pokemon.h"

struct ataque_ {
    char nome_ataque[20];
    int poder_base;
    float acuracia;
    char classe[1];
};
struct _atributos {
    int HP;
    int ataque;
    int defesa;
    int ataque_especial;
    int defesa_especial;
    int velocidade;
};

struct pokemon_ {
    char nome[50];
    char tipo_primario[20];
    char tipo_secundario[20];
    struct _atributos atributos;
    ATAQUE ataques[4];
};


int main(){
    int a,i,j;
    int cont = 0;
    POKEMON *pokedex;

   pokedex = (POKEMON *)malloc(10 * sizeof(POKEMON));

    while(scanf("%d",&a) && a != 0){
        switch(a){
            case 1:{
                cadastro_poke(pokedex,cont);
                cont++;
                break;
            }
            case 2:{
                scanf("%d",&i);
                scanf("%d",&j);
                cadastro_ataque(pokedex,i,j);
                break;
            }
            case 3:{
                scanf("%d",&i);
                imprimir_poke(pokedex,i);
                break;
            }
            case 4:{
                scanf("%d",&i);
                scanf("%d",&j);
                imprimir_ataque(pokedex,i,j);
                break;
            }

            }
        }


    return 0;
}