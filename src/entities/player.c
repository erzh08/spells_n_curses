#include "core.h"
#include "player.h"

Player *start_player(void){
	int i;
	Player *new_player = (Player *) malloc(sizeof(Player));

	if(new_player == NULL){
		perror("Error on allocation of player");
		exit(EXIT_FAILURE);
	}

	new_player->items = (Item **) malloc(sizeof(Item *) * MAX_ITEMS);
	
	if(new_player->items == NULL){
		perror("Error on allocation of player items");
		exit(EXIT_FAILURE);
	}

	new_player->equipped_weapon = NULL;
	new_player->equipped_shield = NULL;

	for(i = 0; i < MAX_ITEMS; i++)
		new_player->items[i] = NULL;

	new_player->health = 20;
	new_player->attack = 6;
	new_player->defense = 5;
	new_player->max_health = 20;
	new_player->exp = 0;
	new_player->level = 1;
	new_player->item_quant = 0;
	new_player->stat = NORMAL_STT;
	new_player->stat_counter = 0;

	return new_player;
}

Position *handle_input(int input, Player *player){
	Position *new_pos = (Position *) malloc(sizeof(Position));

	if(new_pos == NULL){
		perror("Error on allocation of player position");
		exit(EXIT_FAILURE);
	}

	switch(input){
		/* move up */
		case 'w':
		case 'W':
			new_pos->y = player->pos.y - 1;
			new_pos->x = player->pos.x;
			break;

			/* move down */
		case 's':
		case 'S':
			new_pos->y = player->pos.y + 1;
			new_pos->x = player->pos.x;
			break;

			/* move left */
		case 'a':
		case 'A':
			new_pos->y = player->pos.y;
			new_pos->x = player->pos.x - 1;
			break;

			/* move right */
		case 'd':
		case 'D':
			new_pos->y = player->pos.y;
			new_pos->x = player->pos.x + 1;
			break;

		default:
			break;
	}

	return new_pos;
}

void check_level(Player *player){
	if(player->exp >= (player->level * 2)){
		player->exp -= (player->level * 2);
		player->level++;
		player->defense += (rand() % 3) + 1;
		player->attack += (rand() % 3) + 1;
		player->max_health += (rand() % 3) + 4;
	}
}

void player_move(Position *new_pos, Player *player){
	player->pos.x = new_pos->x;
	player->pos.y = new_pos->y;
}

void draw_player(Player *player){
	mvprintw(player->pos.y, player->pos.x, "@");
	move(player->pos.y, player->pos.x);
}

void player_dies(Player *player){
	attron(COLOR_PAIR(5));
	mvprintw(player->pos.y, player->pos.x, "@");
	attroff(COLOR_PAIR(5));
}

void free_player(Player *player){
	int i;

	/* free items */
	for(i = 0; i < player->item_quant; i++){
		if(player->items[i] != NULL){
			if(player->items[i]->type == WEAPON_TYPE)
				free(player->items[i]->item.weapon);
			else if(player->items[i]->type == SHIELD_TYPE)
				free(player->items[i]->item.shield);
			else if(player->items[i]->type == SCROLL_TYPE)
				free(player->items[i]->item.scroll);
			else if(player->items[i]->type == POTION_TYPE)
				free(player->items[i]->item.potion);

			free(player->items[i]);
		}
	}

	free(player->items);
	free(player);
}

