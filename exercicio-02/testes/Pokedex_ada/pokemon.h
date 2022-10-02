//
// Created by ada on 18/09/22.
//

#ifndef POKEDEX_C_POKEMON_H
#define POKEDEX_C_POKEMON_H
typedef struct ataque_ ATAQUE;
typedef struct pokemon_ POKEMON;

void cadastro_ataque(POKEMON *pokedex, int i, int j);
void imprimir_ataque(POKEMON *pokedex, int i, int j);
void cadastro_poke(POKEMON *pokedex, int i);
void imprimir_poke(POKEMON *pokedex,int i);


#endif //POKEDEX_C_POKEMON_H
