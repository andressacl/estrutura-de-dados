#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"

struct _attributes {

	int hp;
	int attack;
	int defense;
	int special_attack;
	int special_defense;
	int speed;

};

struct _attack {

	char name[20];
	int base_power;
	float accuracy;
	char class;

};

struct _pokemon {

	char name[50];
	char primary_type[20];
	char secondary_type[20];
	Attributes *self_attributes;
	Attack **self_attack;

};

Attack *create_attack(char name[20], int base_power, float accuracy, char class){
	Attack *new_attack = (Attack*) calloc(1, sizeof(Attack));

	strcpy(new_attack->name, name);
	new_attack->base_power=base_power;
	new_attack->accuracy=accuracy;
	new_attack->class=class;

	return new_attack;
}

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
	Attack **l_attack = (Attack**) calloc(3, sizeof(Attack*));

	strcpy(pokemon->name, name);
	strcpy(pokemon->primary_type, p_type);
	strcpy(pokemon->secondary_type, s_type);
	pokemon->self_attack = l_attack;
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
	printf("Nome do Pokemon: %s\n", pokemon->name);
	printf("Tipo primario: %s\n", pokemon->primary_type);
	printf("Tipo secundario: %s\n", pokemon->secondary_type);
	print_attributes(pokemon->self_attributes);
}

void set_attacks(const Pokemon *pokemon, int ind){
	char name[20], class;
	int base_power;
	float accuracy;

	scanf("%s\n", name);
	scanf("%i\n", &base_power);	
	scanf("%f\n", &accuracy);
	scanf("%c\n", &class);

	pokemon->self_attack[ind] = create_attack(name, base_power, accuracy, class);

}

void print_attack(Pokemon *pokemon, int ind){
	printf("Nome do Ataque: %s\n", pokemon->self_attack[ind]->name);
	printf("Poder base: %d\n", pokemon->self_attack[ind]->base_power);
	printf("Acuracia: %f\n", pokemon->self_attack[ind]->accuracy);
	printf("Classe: %c\n\n", pokemon->self_attack[ind]->class);
}

void destroy_pokemon(Pokemon **pokemon_ref){
	Pokemon *pokemon = *pokemon_ref;

		for (int j=0; j < 3;j++){
			free(pokemon->self_attack[j]);
		}
		free(pokemon->self_attack);
		free(pokemon->self_attributes);
		free(pokemon);
}