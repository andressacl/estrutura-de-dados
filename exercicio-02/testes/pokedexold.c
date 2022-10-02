#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _attributes {

	int HP;
	int attack;
	int defense;
	int special_attack;
	int special_defense;
	int speed;

} Attributes;

typedef struct _attack {

	char name[20];
	int base_power;
	float accuracy;
	char class;

} Attack;

typedef struct _pokemon {

	char name[50];
	char primary_type[20];
	char secondary_type[20];
	//Attributes *self_attributes;
	//Attack *self_attack;

} Pokemon;

typedef struct _pokedex {

	Pokemon **vet;
	int size;

} Pokedex;

//Attack *create_attack();

//Attributes *set_attributes();

Pokemon *create_pokemon(const char name[50], const char p_type[20], const char s_type[20]){
	Pokemon *pokemon = (Pokemon*) calloc(1, sizeof(Pokemon));

	strcpy(pokemon->name, name);
	strcpy(pokemon->primary_type, p_type);
	strcpy(pokemon->secondary_type, s_type);
	//pokemon->self_attack = create_attack(self_atks);
	//pokemon->self_attributes = set_attributes(self_atts);

	return pokemon;
}

void print_pokemon(const Pokemon *pokemon){
	printf("Nome: %s", pokemon->name);
	printf("Tipo primário: %s", pokemon->primary_type);
	printf("Tipo secundário: %s", pokemon->secondary_type);
}

//Pokedex update_pokedex();

void scan_pokemon(Pokemon *curr_pokedex);

int main(){

	int cmd;
	Pokemon *pokedex = (Pokemon*)calloc(10, sizeof(Pokemon));

	do {
		scanf("%i", &cmd);

		if (cmd == 1) {
			scan_pokemon(pokedex);
			print_pokemon(pokedex[0]);
		}

	} while (cmd != 0);


	return 0;
}


void scan_pokemon(Pokemon **curr_pokedex){
	char name[50], p_type[20], s_type[20];
	int hp, attack, defense, s_attack, s_defense, speed;

	scanf("%s\n", name);
	scanf("%s\n", p_type);
	scanf("%s\n", s_type);
	/*scanf("%i\n", &hp);
	scanf("%i\n", &attack);	
	scanf("%i\n", &defense);
	scanf("%i\n", &s_attack);
	scanf("%i\n", &s_defense);
	scanf("%i\n", &speed);
*/

//ver size do vetor de pokemons

	//curr_pokedex[0] = create_pokemon(name, p_type, s_type, hp, attack, defense, s_attack, s_defense, speed);

	curr_pokedex[0] = create_pokemon(name, p_type, s_type);
};