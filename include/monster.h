#ifndef MONSTER_H
#define MONSTER_H

#include "position.h"

enum {
	SPIDER_SYMBOL = 600,
	SLEEPING_SPIDER_SYMBOL = 2904,
	SLOWED_SPIDER_SYMBOL = 3160,
	POISONED_SPIDER_SYMBOL = 2648,
	GOBLIN_SYMBOL = 583,
	SLEEPING_GOBLIN_SYMBOL = 2887,
	SLOWED_GOBLIN_SYMBOL = 3143,
	POISONED_GOBLIN_SYMBOL = 2631,
	TROLL_SYMBOL = 596,
	SLEEPING_TROLL_SYMBOL = 2900,
	SLOWED_TROLL_SYMBOL = 3156,
	POISONED_TROLL_SYMBOL = 2644,
	LIZARDMAN_SYMBOL = 844,
	SLEEPING_LIZARDMAN_SYMBOL = 2892,
	SLOWED_LIZARDMAN_SYMBOL = 3148,
	POISONED_LIZARDMAN_SYMBOL = 2636,
	BODAK_SYMBOL = 1090,
	SLEEPING_BODAK_SYMBOL = 2882,
	SLOWED_BODAK_SYMBOL = 3138,
	POISONED_BODAK_SYMBOL = 2626,
	WRAITH_SYMBOL = 1111,
	SLEEPING_WRAITH_SYMBOL = 2903, 
	SLOWED_WRAITH_SYMBOL = 3159,
	POISONED_WRAITH_SYMBOL = 2647,
	WYVERN_SYMBOL = 851,
	SLEEPING_WYVERN_SYMBOL = 2899,
	SLOWED_WYVERN_SYMBOL = 3155,
	POISONED_WYVERN_SYMBOL = 2643
};

typedef enum {
	NONE_TP = 1	/* used for weapon affinity */,
	BEAST_TP = 2,
	REPTILE_TP = 3,
	SPIRIT_TP = 4
} Monster_type;

typedef struct Monster {
	struct Position pos;
	Monster_type type;
	Status stat;
	char symbol;
	char name[32];
	int stat_counter;
	int health;
	int attack;
	int experience;
	int defense;
	int path_finding;
	int alive;
} Monster;

Monster *create_monster(char symbol, int health, int attack, int defense, int experience, int path_finding, Monster_type type);
Monster *select_monster(int level);
void path_finding_seek(Position *start, Position *dest);
void path_finding_random(Position *monster_pos);
Monster *get_monster_at(Position *pos, Monster **monsters, int monster_num);
void kill_monster(Monster *monster);
void draw_monster(Monster *monster);
int is_monster(int ch);

#endif

