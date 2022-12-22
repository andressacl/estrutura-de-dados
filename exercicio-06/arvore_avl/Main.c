#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdbool.h>

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

	Avl *avl_games = avl_create();
	read_and_register_avl(file, avl_games);

	int print_format;
	scanf("%d", &print_format);
	
	int search_year;	
	char ctrl[2] = "F";
	char *line = readLine();

	while(strcmp(line, ctrl) != 0){
		search_year = atoi(line);

		Game *rm_game = avl_remove_node(avl_games, search_year);
		while (rm_game != NULL){
			printf("Deletado: ");
			game_print(rm_game);
			game_delete(&rm_game);
			rm_game = avl_remove_node(avl_games, search_year);
		}

		line = readLine();
	}

	avl_print_format(avl_games, print_format);

	// avl_imprimir(avl_games);
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
			 	// avl_imprimir(avl);
			 	// printf("\n--------------------------\n");
			 	
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