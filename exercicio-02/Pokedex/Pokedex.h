#ifndef POKEDEX_H
#define POKEDEX_H
#include "Pokemon.h"

typedef struct _pokedex Pokedex;

Pokedex *create_pokedex(const int capacity);

void scan_pokemon(Pokedex *curr_pokedex);
Pokemon* get_pokemon(Pokedex *pokedex, int ind);
void destroy_pokedex(Pokedex **pokedex_ref);

#endif //POKEDEX_H