#ifndef GAME_H
#define GAME_H

#include "level.h"

typedef struct Game {
	struct Level *levels[10];
	int current_level;
} Game;

int game_loop(Game *game);
void render(Game *game, WINDOW *log_win);

#endif

