//
// Created by ada on 18/09/22.
//
#include <stdio.h>
#include "pokemon.h"
#include <stdlib.h>

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

void cadastro_ataque(POKEMON *pokedex, int i, int j) {
    scanf("%s", pokedex[i].ataques[j].nome_ataque);
    scanf("%d", &pokedex[i].ataques[j].poder_base);
    scanf("%f", &pokedex[i].ataques[j].acuracia);
    scanf("%s", pokedex[i].ataques[j].classe);
}

void imprimir_ataque(POKEMON *pokedex, int i, int j){
    printf("Nome do Ataque: %s\n", pokedex[i].ataques[j].nome_ataque);
    printf("Poder base: %d\n", pokedex[i].ataques[j].poder_base);
    printf("Acuracia: %f\n", pokedex[i].ataques[j].acuracia);
    printf("Classe: %s\n\n", pokedex[i].ataques[j].classe);
}

//Pokemon listapokemon = malloc(10 * sizeof(Pokemon));

void cadastro_poke(POKEMON *pokedex, int i){
    //POKEMON pokedex = malloc(10 *sizeof(POKEMON));
    scanf("%s", pokedex[i].nome);
    scanf("%s", pokedex[i].tipo_primario);
    scanf("%s", pokedex[i].tipo_secundario);
    scanf("%d", &pokedex[i].atributos.HP);
    scanf("%d", &pokedex[i].atributos.ataque);
    scanf("%d", &pokedex[i].atributos.defesa);
    scanf("%d", &pokedex[i].atributos.ataque_especial);
    scanf("%d", &pokedex[i].atributos.defesa_especial);
    scanf("%d", &pokedex[i].atributos.velocidade);
}

void imprimir_poke(POKEMON *pokedex,int i){
    //POKEMON pokedex = malloc(10 * sizeof(POKEMON));
    printf("Nome do Pokemon: %s\n", pokedex[i].nome);
    printf("Tipo primario: %s\n", pokedex[i].tipo_primario);
    printf("Tipo secundario: %s\n", pokedex[i].tipo_secundario);
    printf("Status:\n");
    printf("\tHP: %d\n", pokedex[i].atributos.HP);
    printf("\tAtaque: %d\n", pokedex[i].atributos.ataque);
    printf("\tDefesa: %d\n", pokedex[i].atributos.defesa);
    printf("\tAtaque Especial: %d\n", pokedex[i].atributos.ataque_especial);
    printf("\tDefesa Especial: %d\n",pokedex[i].atributos.defesa_especial);
    printf("\tVelocidade: %d\n\n", pokedex[i].atributos.velocidade);
}