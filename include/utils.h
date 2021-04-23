#ifndef UTILS_H
#define UTILS_H

#include "level.h"
#include "monster.h"
#include "player.h"
#include "position.h"

void start_ncurses(void);
void print_game_hub(Level *level);
void info_screen(void);
void thanks_scr(void);
void combat(Player *player, Monster *monster, int order);

int check_position(int y, int x);
void free_arrays(int **frontier, int ***came_from);
void path_find(Position *start, Position *end);
void add_position_yx(int **frontier, int count, int y, int x);
int add_neighbors(int **frontier, int ***came_from, int count, int y, int x);

#endif

