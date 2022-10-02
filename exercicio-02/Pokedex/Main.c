#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "Pokedex.h"


int main(){

	int cmd, poke_pos, att_pos;
	Pokedex *my_pokedex = create_pokedex(10);

	do {
		scanf("%i", &cmd);

		switch(cmd) {
			case 1: {
				scan_pokemon(my_pokedex);
				break;
			} 
			case 2: {
				scanf("%i", &poke_pos);
				scanf("%i", &att_pos);
				set_attacks(get_pokemon(my_pokedex, poke_pos), att_pos);
				break;
		    } 
		    case 3: {
				scanf("%i", &poke_pos);
				print_pokemon(get_pokemon(my_pokedex, poke_pos));
				break;
			}
			case 4: {
				scanf("%i", &poke_pos);
				scanf("%i", &att_pos);
				print_attack(get_pokemon(my_pokedex, poke_pos), att_pos);
				break;
			}
		}
	} while (cmd != 0);

	destroy_pokedex(&my_pokedex);

	return 0;
}