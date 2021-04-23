#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "item.h"
#define MAX_ITEMS 12

typedef struct Player {
	struct Position pos;
	Status stat;
	struct Item **items;
	struct Item *equipped_weapon;
	struct Item *equipped_shield;
	int stat_counter;
	int item_quant;
	int level;
	int health;
	int attack;
	int defense;
	int max_health;
	int exp;
} Player;

Player *start_player(void);
Position *handle_input(int input, Player * player);
void player_move(Position *new_pos, Player *player);
void draw_player(Player *player);
void free_player(Player *player);
void check_level(Player *player);
void player_dies(Player *player);

#endif

