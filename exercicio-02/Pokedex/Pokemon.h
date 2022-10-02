#ifndef POKEMON_H
#define POKEMON_H

typedef struct _attributes Attributes;
typedef struct _attack Attack;
typedef struct _pokemon Pokemon;

Attack *create_attack(char name[20], int base_power, float accuracy, char class);
Attributes *set_attributes(int hp, int attack, int defense, int s_attack, int s_defense, int speed);
Pokemon *create_pokemon(const char name[50], const char p_type[20], const char s_type[20], 
	int hp, int attack, int defense, int s_attack, int s_defense, int speed);

void print_attributes(const Attributes *attributes);
void print_pokemon(const Pokemon *pokemon);
void set_attacks(const Pokemon *pokemon, int ind);
void print_attack(Pokemon *pokemon, int ind);
void destroy_pokemon(Pokemon **pokemon_ref);


#endif //POKEMON_H