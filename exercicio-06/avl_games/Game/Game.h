#ifndef GAME_H
#define GAME_H

#include "../Util/Util.h"

typedef struct game_st Game;

Game *game_create(char *name, int year, char *company);

int get_year(Game *game);
char *get_company(Game *game);

boolean game_maior(Game *game1, Game *game2);

void game_print(Game *game);

void game_delete(Game **game_ref);

#endif //GAME_H