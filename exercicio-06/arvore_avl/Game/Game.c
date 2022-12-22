#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdbool.h>

#include "Game.h"

struct game_st {
	char *name;
	char *company;
	int year;
};

Game *game_create(char *name, int year, char *company){
	Game *new_game = (Game*) calloc(1, sizeof(Game));

	new_game->name = (char*) calloc(50, sizeof(char));
	strcpy(new_game->name, name);

	new_game->company = (char*) calloc(50, sizeof(char));
	strcpy(new_game->company, company);

	new_game->year = year;

	return new_game;
}

int get_year(Game *game){
	return game->year;
}

char *get_company(Game *game){
	return game->company;
}

static boolean alph_order(char *str1, char *str2){
	return strcmp(str1, str2) > 0;
}

boolean game_maior(Game *game1, Game *game2){
	if (game1->year != game2->year) 
		return game1->year > game2->year;

	return alph_order(game1->name, game2->name);
}

// void game_print(Game *game){
// 	printf("Nome do game: %s\n", game->name);
// 	printf("Empresa produtora: %s\n", game->company);
// 	printf("Ano de lançamento: %i\n", game->year);
// }

void game_print(Game *game){
	// printf("%d\n", game->year);
	printf("%s: %d\n", game->name, game->year);
}

void game_delete(Game **game_ref){
	Game *game = *game_ref;

	free(game->name);
	game->name = NULL;

	free(game->company);
	game->company = NULL;

	free(game);
	*game_ref = NULL;
}