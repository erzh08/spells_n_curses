#include "core.h"
#include "monster.h"

Monster *create_monster(char symbol, int health, int attack, int defense, int experience, int path_finding, Monster_type type){
	Monster *new_monster = malloc(sizeof(Monster));
	
	if(new_monster == NULL){
		perror("Error on allocation of monster");
		exit(EXIT_FAILURE);
	}

	new_monster->symbol = symbol;
	new_monster->health = health;
	new_monster->attack = attack;
	new_monster->defense = defense;
	new_monster->experience = experience;
	new_monster->path_finding = path_finding;
	new_monster->stat_counter = 0;
	new_monster->alive = 1;
	new_monster->type = type;
	new_monster->stat = NORMAL_STT;

	switch (symbol)
	{
		case 'X': /* Spider: beast */
			strcpy(new_monster->name, "Spider");
			break;

		case 'G': /* Goblin: beast */
			strcpy(new_monster->name, "Goblin");
			break;

		case 'L': /* Lizardman: reptile */
			strcpy(new_monster->name, "Lizardman");
			break;

		case 'B': /* Bodak: spirit */
			strcpy(new_monster->name, "Bodak");
			break;

		case 'W': /* Wraith: spirit */
			strcpy(new_monster->name, "Wraith");
			break;

		case 'T': /* Troll: beast */
			strcpy(new_monster->name, "Troll");
			break;

		case 'S': /* Wyvern: reptile */
			strcpy(new_monster->name, "Wyvern");
			break;

		default:
			break;
	}

	return new_monster;
}

int is_monster(int ch){
	switch(ch){
		case SPIDER_SYMBOL:
		case SLEEPING_SPIDER_SYMBOL:
		case SLOWED_SPIDER_SYMBOL:
		case POISONED_SPIDER_SYMBOL:
		case GOBLIN_SYMBOL:
		case SLEEPING_GOBLIN_SYMBOL:
		case SLOWED_GOBLIN_SYMBOL:
		case POISONED_GOBLIN_SYMBOL:
		case TROLL_SYMBOL:
		case SLEEPING_TROLL_SYMBOL:
		case SLOWED_TROLL_SYMBOL:
		case POISONED_TROLL_SYMBOL:
		case LIZARDMAN_SYMBOL:
		case SLEEPING_LIZARDMAN_SYMBOL:
		case SLOWED_LIZARDMAN_SYMBOL:
		case POISONED_LIZARDMAN_SYMBOL:
		case BODAK_SYMBOL:
		case SLEEPING_BODAK_SYMBOL:
		case SLOWED_BODAK_SYMBOL:
		case POISONED_BODAK_SYMBOL:
		case WRAITH_SYMBOL:
		case SLEEPING_WRAITH_SYMBOL: 
		case SLOWED_WRAITH_SYMBOL:
		case POISONED_WRAITH_SYMBOL:
		case WYVERN_SYMBOL:
		case SLEEPING_WYVERN_SYMBOL:
		case SLOWED_WYVERN_SYMBOL:
		case POISONED_WYVERN_SYMBOL:
			return 1;

		default:
			break;
	}
	return 0;
}

void kill_monster(Monster *monster){
	monster->alive = 0;
}

Monster *select_monster(int level){
	int monster;

	switch(level){
		case 1:
		case 2:
		case 3:
			monster = rand() % 2;
			break;

		case 4:
			monster = (rand() % 2) + 1;
			break;
		case 5:
		case 6:
			monster = (rand() % 3) + 1;
			break;

		case 7:
			monster = (rand() % 3) + 2;
			break;

		case 8:
			monster = (rand() % 3) + 3;
			break;

		case 9:
			monster = (rand() % 2) + 4;
			break;

		case 10:
			monster = 6;
			break;

		default:
			break;
	}

	/* create_monster(Symbol, HP, ATK, DEF, XP, PT, type) */
	switch(monster){
		case 0:	/* Spider */
			return create_monster('X', 10, 3, 10, 1, 1, BEAST_TP);

		case 1:	/* Goblin */
			return create_monster('G', 15, 7, 10, 2, 2, BEAST_TP);

		case 2:	/* Lizardman */
			return create_monster('L', 25, 11, 20, 7, 2, REPTILE_TP);

		case 3: /* Bodak */
			return create_monster('B', 35, 18, 20, 8, 1, SPIRIT_TP);

		case 4: /* Wraith */
			return create_monster('W', 57, 26, 30, 10, 2, SPIRIT_TP);

		case 5: /* Troll */
			return create_monster('T', 80, 45, 50, 30, 1, BEAST_TP);

		case 6: /* Wyvern */
			return create_monster('S', 150, 70, 100, 100, 2, REPTILE_TP);

		default:
			break;
	}

	return NULL;
}

void path_finding_seek(Position *start, Position *dest){
	if((abs((start->x - 1) - dest->x) < abs(start->x - dest->x)) && (mvinch(start->y, start->x - 1) == '.' || mvinch(start->y, start->x - 1) == '@'
				|| mvinch(start->y, start->x - 1) == '#'))
		start->x = start->x - 1; /* move left */

	else if((abs((start->x + 1) - dest->x) < abs(start->x - dest->x)) && (mvinch(start->y, start->x + 1) == '.' || mvinch(start->y, start->x + 1) == '@'
				|| mvinch(start->y, start->x + 1) == '#'))
		start->x = start->x + 1; /* move right */

	else if((abs((start->y - 1) - dest->y) < abs(start->y - dest->y)) && (mvinch(start->y - 1, start->x) == '.' || mvinch(start->y - 1, start->x) == '@'
				|| mvinch(start->y - 1, start->x) == '#'))
		start->y = start->y - 1; /* move up */

	else if((abs((start->y + 1) - dest->y) < abs(start->y - dest->y)) && (mvinch(start->y + 1, start->x) == '.' || mvinch(start->y + 1, start->x) == '@'
				|| mvinch(start->y + 1, start->x) == '#'))
		start->y = start->y + 1; /* move down */
	else{/* do nothing */}
}

void path_finding_random(Position *monster_pos){
	int random = rand() % 5;

	switch(random){
		case 0:	/* up */
			if(mvinch(monster_pos->y - 1, monster_pos->x) == '.' || mvinch(monster_pos->y - 1, monster_pos->x) == '@')
				monster_pos->y--;
			break;
		case 1:	/* down */
			if(mvinch(monster_pos->y + 1, monster_pos->x) == '.' || mvinch(monster_pos->y + 1, monster_pos->x) == '@')
				monster_pos->y++;
			break;
		case 2:	/* right */
			if(mvinch(monster_pos->y, monster_pos->x + 1) == '.' || mvinch(monster_pos->y, monster_pos->x + 1) == '@')
				monster_pos->x++;
			break;
		case 3:	/* left */
			if(mvinch(monster_pos->y, monster_pos->x - 1) == '.' || mvinch(monster_pos->y, monster_pos->x - 1) == '@')
				monster_pos->x--;
			break;
		case 4:	/* nothing */
			break;
	}
}

Monster *get_monster_at(Position *pos, Monster **monsters, int monster_num){
	int monster_i = 0;

	for(monster_i = 0; monster_i < monster_num; monster_i++){
		if(monsters[monster_i] != NULL){
			if(monsters[monster_i]->pos.y == pos->y
					&& monsters[monster_i]->pos.x == pos->x)
				return monsters[monster_i];
		}
	}

	return NULL;
}

void draw_monster(Monster *monster){
	if(monster->alive){
		if(monster->stat == NORMAL_STT)
			attron(COLOR_PAIR(monster->type));
		else
			attron(COLOR_PAIR(monster->stat));		
		mvprintw(monster->pos.y, monster->pos.x, "%c", monster->symbol);
		attroff(COLOR_PAIR(monster->type));
		attroff(COLOR_PAIR(monster->stat));
	}
}

