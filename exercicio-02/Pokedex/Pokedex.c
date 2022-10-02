#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "Pokedex.h"

struct _pokedex{
	Pokemon **data;
	int size;
	int capacity;
};

Pokedex *create_pokedex(const int capacity){
	Pokedex *my_pokedex = (Pokedex*) calloc(1, sizeof(Pokedex));
	my_pokedex->size = 0;
	my_pokedex->capacity = capacity;
	my_pokedex->data = (Pokemon**) calloc(capacity, sizeof(Pokemon*));
	return my_pokedex;
}

void scan_pokemon(Pokedex *curr_pokedex){
	char name[50], p_type[20], s_type[20];
	int hp, attack, defense, s_attack, s_defense, speed;

	scanf("%s\n", name);
	scanf("%s\n", p_type);
	scanf("%s\n", s_type);
	scanf("%i\n", &hp);
	scanf("%i\n", &attack);	
	scanf("%i\n", &defense);
	scanf("%i\n", &s_attack);
	scanf("%i\n", &s_defense);
	scanf("%i\n", &speed);

    int size = curr_pokedex->size;
	curr_pokedex->data[size]= create_pokemon(name, p_type, s_type, hp, attack, defense, s_attack, s_defense, speed);
	curr_pokedex->size += 1;
}

Pokemon* get_pokemon(Pokedex *pokedex, int ind){
	return pokedex->data[ind];
}

void destroy_pokedex(Pokedex **pokedex_ref){
	Pokedex *pokedex = *pokedex_ref;
	for (int i = 0; i < (pokedex->size);i++){
		destroy_pokemon(&(pokedex->data[i]));
	}
	for (int i = pokedex->size; i < (pokedex->capacity);i++){
		free(pokedex->data[i]);
	}
	pokedex->size = 0;
	free(pokedex->data);
	free(pokedex);
	*pokedex_ref=NULL;
}

