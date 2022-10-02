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
	Attributes *self_attributes;
	Attack **self_attack;

} Pokemon;

typedef struct _pokedex{
	Pokemon **data;
	int size;
} Pokedex;

Attack *create_attack(char name[20], int base_power, float accuracy, char class){
	Attack *new_attack = (Attack*) calloc(1, sizeof(Attack));

	strcpy(new_attack->name, name);
	new_attack->base_power=base_power;
	new_attack->accuracy=accuracy;
	new_attack->class=class;

	return new_attack;
};

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
	Attack **l_attack = (Attack**) calloc(3, sizeof(Attack));

	strcpy(pokemon->name, name);
	strcpy(pokemon->primary_type, p_type);
	strcpy(pokemon->secondary_type, s_type);
	pokemon->self_attack = l_attack;
	pokemon->self_attributes = set_attributes(hp, attack, defense, s_attack, s_defense, speed);

	return pokemon;
}

Pokedex *create_pokedex(const int capacity){
	Pokedex *my_pokedex = (Pokedex*) calloc(1, sizeof(Pokedex));
	my_pokedex->size = 0;
	my_pokedex->data = (Pokemon**) calloc(capacity, sizeof(Pokemon*));
	return my_pokedex;
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
};

void set_attacks(const Pokemon *pokemon, int ind){
	char name[20], class;
	int base_power;
	float accuracy;

	scanf("%s\n", name);
	scanf("%i\n", &base_power);	
	scanf("%f\n", &accuracy);
	scanf("%c\n", &class);

	pokemon->self_attack[ind] = create_attack(name, base_power, accuracy, class);

};

void print_attack(Pokemon *pokemon, int ind){
	printf("Nome do Ataque: %s\n", pokemon->self_attack[ind]->name);
	printf("Poder base: %d\n", pokemon->self_attack[ind]->base_power);
	printf("Acuracia: %f\n", pokemon->self_attack[ind]->accuracy);
	printf("Classe: %c\n\n", pokemon->self_attack[ind]->class);
};

void destroy_pokemon(Pokemon **pokemon_ref){

	Pokemon *pokemon = *pokemon_ref;

		for (int j=0; j < 3;j++){
			free(pokemon->self_attack[j]);
		}
		free(pokemon->self_attack);
		free(pokemon->self_attributes);
		free(pokemon);
		*pokemon_ref = NULL;
}

void destroy_pokedex(Pokedex **pokedex_ref){
	Pokedex *pokedex = *pokedex_ref;
	for (int i = 0; i < pokedex->size;i++){
		destroy_pokemon(&(pokedex->data[i]));
	}
	pokedex->size = 0;
	free(pokedex->data);
	free(pokedex);
	*pokedex_ref=NULL;
}

int main(){

	int cmd, poke_pos, att_pos;
	Pokedex *my_pokedex = create_pokedex(10);

	while (1){
		scanf("%i", &cmd);

		if (cmd == 1) {
			scan_pokemon(my_pokedex);
		} else if (cmd==2){
			scanf("%i", &poke_pos);
			scanf("%i", &att_pos);
			set_attacks(my_pokedex->data[poke_pos], att_pos);
	    } else if (cmd == 3){
			scanf("%i", &poke_pos);
			print_pokemon(my_pokedex->data[poke_pos]);
		} else if (cmd==4){
			scanf("%i", &poke_pos);
			scanf("%i", &att_pos);
			print_attack(my_pokedex->data[poke_pos], att_pos);
		}

		if (cmd ==0) break;
	}

	destroy_pokedex(&my_pokedex);

	return 0;
}

