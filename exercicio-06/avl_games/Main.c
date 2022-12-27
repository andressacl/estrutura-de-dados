#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Util/Util.h"
#include "Game/Game.h"
#include "Avl/Avl.h"

void read_and_register_avl(FILE *file, Avl *avl);
void avl_print_format(Avl *avl, int n);

int main(){ 
	FILE *file;
	char filename[50] = "CSV.csv";

	file = fopen(filename, "r");
	if (file == NULL){
		perror("fopen failed");
		exit(1);
	}

	fseek(file, 3, SEEK_SET);

	Avl *avl_games = avl_create();
	read_and_register_avl(file, avl_games);

	int print_format;
	scanf("%d\n", &print_format);
	
	int search_year;	
	char ctrl[2] = "F";
	char *line = readLine();

	while(strcmp(line, ctrl) != 0){
		search_year = atoi(line);
		
		Game *s_game = avl_search_game(avl_root(avl_games), search_year);

		while (s_game != NULL){
			
			avl_remove_game(avl_games, s_game);
			s_game = avl_search_game(avl_root(avl_games), search_year);

		}

		char *line_aux = line;
		line = readLine();
		free(line_aux);
	}

	avl_print_format(avl_games, print_format);

	free(line);
	avl_delete(&avl_games);
	fclose(file);
}

void read_and_register_avl(FILE *file, Avl *avl){
	char linha[100], *token;
	char name[50], company[50];
	int year;
	Game *game;

	while (feof(file) != TRUE){

		if (fgets(linha, 100, file) != NULL){

			token = strtok(linha, ";");
			strcpy(name, token);

			token = strtok(NULL, ";");
			year = atoi(token);

			token = strtok(NULL, "\n");
			strcpy(company, token);

			game = game_create(name, year, company);
			if (game != NULL){
	
			 	if (avl_insert(avl, game) == FALSE) game_delete(&game); 			 	
			 	game = NULL;
			}

		}
	}
	
	return;
}

void avl_print_format(Avl *avl, int n){
	if (n == 1) avl_pre_order(avl);
	if (n == 2) avl_in_order(avl);
	if (n == 3) avl_post_order(avl);
}