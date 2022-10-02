#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _attributes {

	int hp;
	int attack;
	int defense;
	int special_attack;
	int special_defense;
	int speed;

} Attributes;

typedef struct _pokemon {

	char name[50];
	char primary_type[20];
	char secondary_type[20];
	Attributes *self_attributes;
	//Attack *self_attack;

} Pokemon;

typedef struct _pokedex{

	Pokemon **pokedex;
	int size;

} Pokedex;

Attributes *set_attributes(int hp, int attack, int defense, int s_attack, int s_defense, int speed){
	Attributes *self_attributes = (Attributes*) calloc(1, sizeof(Attributes));
	self_attributes->hp = hp;
	self_attributes->attack = attack;
	self_attributes->defense = defense;
	self_attributes->special_attack = s_attack;
	self_attributes->special_defense = s_defense;
	self_attributes->speed = speed;

	return self_attributes;
}

Pokemon *create_pokemon(const char name[50], const char p_type[20], const char s_type[20], 
	int hp, int attack, int defense, int s_attack, int s_defense, int speed){
	Pokemon *pokemon = (Pokemon*) calloc(1, sizeof(Pokemon));

	strcpy(pokemon->name, name);
	strcpy(pokemon->primary_type, p_type);
	strcpy(pokemon->secondary_type, s_type);
	//pokemon->self_attack = create_attack(self_atks);
	pokemon->self_attributes = set_attributes(hp, attack, defense, s_attack, s_defense, speed);

	return pokemon;
}

void print_attributes(const Attributes *attributes){
	printf("Status:\n");
	printf("\tHP: %d\n", attributes->hp);
	printf("\tAtaque: %d\n", attributes->attack);
	printf("\tDefesa: %d\n", attributes->defense);
	printf("\tAtaque Especial: %d\n", attributes->special_attack);
	printf("\tDefesa Especial: %d\n", attributes->special_defense);
	printf("\tVelocidade: %d\n\n", attributes->speed);
}

void print_pokemon(const Pokemon *pokemon){
	printf("Nome: %s\n", pokemon->name);
	printf("Tipo primário: %s\n", pokemon->primary_type);
	printf("Tipo secundário: %s\n", pokemon->secondary_type);
	print_attributes(pokemon->self_attributes);
}

void scan_pokemon(Pokemon **curr_pokedex);

int main(){

	int cmd;
	Pokemon **my_pokedex = (Pokemon**) calloc(10, sizeof(Pokemon));

	do {
		scanf("%i", &cmd);

		if (cmd == 1) {
			scan_pokemon(my_pokedex);
		} else if (cmd == 3){
			int pos;
			scanf("%i", &pos);
			print_pokemon(my_pokedex[pos]);
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
	scanf("%i\n", &hp);
	scanf("%i\n", &attack);	
	scanf("%i\n", &defense);
	scanf("%i\n", &s_attack);
	scanf("%i\n", &s_defense);
	scanf("%i\n", &speed);
    

    //ver size do vetor de pokemons
	curr_pokedex[0] = create_pokemon(name, p_type, s_type, hp, attack, defense, s_attack, s_defense, speed);
};