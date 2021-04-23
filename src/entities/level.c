#include "core.h"
#include "level.h"
#include "utils.h"
#include "log.h"

Level *create_level(int level){
	Level *new_level = malloc(sizeof(Level));
	Room * go_to;
	
	if(new_level == NULL){
		perror("Error on level generation");
		exit(EXIT_FAILURE);
	}


	new_level->level = level;
	new_level->room_number = (rand() % 4) + 3;
	new_level->rooms = start_rooms(new_level->room_number);
	new_level->stairs = (Stairs *) malloc(sizeof(Stairs));

	if(new_level->stairs == NULL){
		perror("Error on allocation of stairs");
		exit(EXIT_FAILURE);
	}

	connect_doors(new_level);

	go_to = select_room(new_level);

	set_stairs_starting_pos(go_to, new_level->stairs);
	new_level->tiles = save_level_pos();
	new_level->player = start_player();

	add_items(new_level);
	add_monsters(new_level);

	go_to = select_room(new_level);

	place_player(go_to, new_level->player);

	return new_level;
}

Room *select_room(Level* level){
	Room * go_to;
	int i, alone_doors;

	while(1){
		alone_doors = 0;
		go_to = level->rooms[(rand() % level->room_number)];
		for(i = 0; i < go_to->door_number; i++){
			if(go_to->doors[i]->connected == 0)
				alone_doors++;
		}
		if(alone_doors != go_to->door_number)
			break;
	}

	return go_to;
}

Room **start_rooms(int room_number){
	int room_i = 0, i;
	int rooms_i[6] = {0};
	Room **rooms = (Room **) malloc(sizeof(Room) * room_number);

	if(rooms == NULL){
		perror("Error on allocation of rooms");
		exit(EXIT_FAILURE);
	}

	/* creates the rooms */
	while(1){
		i = (rand() % 6);

		if(rooms_i[i] != 0)
			continue;

		rooms_i[i]++;
		rooms[room_i] = create_room(i, 4);
		draw_room(rooms[room_i]);
		room_i++;
		if(room_i == room_number)
			break;
	}

	return rooms;
}

void add_monsters(Level *level){
	int i, room_num, monster_num, monsters_to_level, min_monsters;

	switch (level->level){
		case 1:
			min_monsters = 3;
			monsters_to_level = 1;
			break;

		case 2:
			min_monsters = 4;
			monsters_to_level = 2;
			break;

		case 3:
			min_monsters = 4;
			monsters_to_level = 4;
			break;

		case 4:
			min_monsters = 5;
			monsters_to_level = 3;
			break;

		case 5:
			min_monsters = 5;
			monsters_to_level = 4;
			break;

		case 6:
			min_monsters = 6;
			monsters_to_level = 4;
			break;

		case 7:
			min_monsters = 7;
			monsters_to_level = 3;
			break;

		case 8:
			min_monsters = 8;
			monsters_to_level = 4;
			break;

		case 9:
			min_monsters = 8;
			monsters_to_level = 6;
			break;

		case 10:
			min_monsters = 1;
			monsters_to_level = 0;
			break;

		default:
			break;
	}

	monster_num = (rand() % (monsters_to_level + 1)) + min_monsters;
	level->monsters = calloc(monster_num, sizeof(Monster *));

	if(level->monsters == NULL){
		perror("Error on allocation of monsters");
		exit(EXIT_FAILURE);
	}

	level->monster_number = 0;

	if(level->level == 10){
		level->monsters[level->monster_number] = select_monster(level->level);

		if(level->monsters[level->monster_number] == NULL){
			perror("Error on selection of Wyvern");
			exit(EXIT_FAILURE);
		}

		set_monster_starting_pos(level->monsters[level->monster_number], level->rooms[rand() % level->room_number]);
		level->monster_number++;
		return;
	}

	for(room_num = 0; (room_num < level->room_number) && (level->monster_number < monster_num); room_num++){
		for(i = 0; (i < 4) && (level->monster_number < monster_num); i++){
			level->monsters[level->monster_number] = select_monster(level->level);

			if(level->monsters[level->monster_number] == NULL){
				perror("Error on selection of monster");
				exit(EXIT_FAILURE);
			}

			set_monster_starting_pos(level->monsters[level->monster_number], level->rooms[room_num]);
			level->monster_number++;
		}
	}
}

void add_items(Level *level){
	int i, room_i, item_num, items_to_level, min_items;

	switch(level->level){
		case 1:
		case 2:
		case 3:
			min_items = 4;
			items_to_level = 1;
			break;

		case 4:
		case 5:
			min_items = 4;
			items_to_level = 2;
			break;

		case 6:
			min_items = 4;
			items_to_level = 4;
			break;

		case 7:
			min_items = 5;
			items_to_level = 2;
			break;

		case 8:
			min_items = 3;
			items_to_level = 2;
			break;

		case 9:
			min_items = 2;
			items_to_level = 1;
			break;

		case 10:
			min_items = 1;
			items_to_level = 0;
			break;

		default:
			break;
	}

	item_num = (rand() % (items_to_level + 1)) + min_items;
	level->items = calloc(item_num, sizeof(Item *));

	if(level->items == NULL){
		perror("Error on allocation of items");
		exit(EXIT_FAILURE);
	}

	level->item_number = 0;

	for(room_i = 0; (room_i < level->room_number) && (level->item_number < item_num); room_i++){
		for(i = 0; (i < 3) && (level->item_number < item_num); i++){
			level->items[level->item_number] = select_item(level->level);

			if(level->items[level->item_number] == NULL){
				perror("Error on selection of item");
				exit(EXIT_FAILURE);
			}

			set_item_starting_pos(level->items[level->item_number], level->rooms[room_i]);
			level->item_number++;
		}
	}
}

void move_monster(Level *level){
	int monster_num;
	Position old_pos;

	for(monster_num = 0; monster_num < level->monster_number; monster_num++){
		if(level->monsters[monster_num]->health <= 0)
			level->monsters[monster_num]->alive = 0;

		if(level->monsters[monster_num]->alive == 0)
			continue;

		if(level->monsters[monster_num]->stat_counter == 0)
			level->monsters[monster_num]->stat = NORMAL_STT;

		if(level->monsters[monster_num]->stat == SLEEP_STT){
			level->monsters[monster_num]->stat_counter--;
			continue;
		}

		if(level->monsters[monster_num]->stat == SLOW_STT){
			if(level->monsters[monster_num]->stat_counter % 3 != 0){
				level->monsters[monster_num]->stat_counter--;
				continue;
			}
			level->monsters[monster_num]->stat_counter--;
		}

		if(level->monsters[monster_num]->stat == POISON_STT){
			if(level->monsters[monster_num]->stat_counter % 3 == 0)
				level->monsters[monster_num]->health--;
			level->monsters[monster_num]->stat_counter--;
		}

		old_pos = level->monsters[monster_num]->pos;

		if(level->monsters[monster_num]->path_finding == 1){	/* random */
			path_finding_random(&(level->monsters[monster_num]->pos));
		}
		else{	/* seek */
			path_finding_seek(&(level->monsters[monster_num]->pos), &(level->player->pos));
		}

		if(is_same_pos(&level->monsters[monster_num]->pos, &level->player->pos)/*(level->monsters[monster_num]->pos.y == level->player->pos.y) && (level->monsters[monster_num]->pos.x == level->player->pos.x)*/){
			combat(level->player, level->monsters[monster_num], 1);
			level->monsters[monster_num]->pos = old_pos;
		}
	}
}

int store_item(Player *player, Item *item){
	if(player->item_quant < MAX_ITEMS){
		item->stored = 1;
		player->items[player->item_quant] = item;

		if(item->type == WEAPON_TYPE || item->type == SHIELD_TYPE)
			equip_item(player, item);

		player->item_quant++;

		event_log(PICK_EV, item->name);

		return 0;
	}
	return -1;
}

void equip_item(Player *player, Item *item){
	if(item->type == WEAPON_TYPE){
		if(player->equipped_weapon != NULL)
			unequip_item(player, WEAPON_TYPE);
		player->equipped_weapon = item;
	}
	else{
		if(player->equipped_shield != NULL)
			unequip_item(player, SHIELD_TYPE);
		player->equipped_shield = item;
	}

	item->equipped = 1;
}

void unequip_item(Player *player, Item_type type){
	if(type == WEAPON_TYPE){
		player->equipped_weapon->equipped = 0;
		player->equipped_weapon = NULL;
	}
	else{
		player->equipped_shield->equipped = 0;
		player->equipped_shield = NULL;
	}
}

void discard_item(Player *player, Item *item){
	int i;
	Item swap;
	for(i = 0; i < player->item_quant; i++)
		if(player->items[i] == item)
			break;

	for(; i < player->item_quant - 1; i++){
		swap = *(player->items[i]);
		player->items[i] = player->items[i+1];
		player->items[i+1] = &swap; 
	}

	player->items[player->item_quant--] = NULL;

	if(item->type == WEAPON_TYPE)
		free(item->item.weapon);
	else if(item->type == SHIELD_TYPE)
		free(item->item.shield);
	else if(item->type == SCROLL_TYPE)
		free(item->item.scroll);
	else if(item->type == POTION_TYPE)
		free(item->item.potion);
	free(item);
}

void use_item(Level *level, Item *item){
	if(item->type == POTION_TYPE){
		level->player->health += item->item.potion->effect;
		if(level->player->health > level->player->max_health)
			level->player->health = level->player->max_health;
	}
	if(item->type == SCROLL_TYPE){
		int monster_i;
		for(monster_i = 0; monster_i < level->monster_number; monster_i++){
			if(level->monsters[monster_i] != NULL && level->monsters[monster_i]->alive){
				level->monsters[monster_i]->stat = item->item.scroll->effect;

				switch(item->item.scroll->effect){
					case POISON_STT:
						if(level->monsters[monster_i]->type == SPIRIT_TP)
							break;
						__attribute__((fallthrough));
					case SLOW_STT:
						level->monsters[monster_i]->stat_counter = 15;
						break;

					case SLEEP_STT:
						level->monsters[monster_i]->stat_counter = 6;
						break;

					default:
						break;
				}
			}
		}
	}

	discard_item(level->player, item);
}

void check_pos(Position *new_pos, Level *level){
	/* mvinch(y, x) checks the character on the position */
	int stored = -1;
	Item *item_to_store;
	int ch = mvinch(new_pos->y, new_pos->x);
	switch(ch){
		case '.':
		case '+':
		case '#':
			player_move(new_pos, level->player);
			break;
		case SWORD_SYMBOL:
		case POTION_SYMBOL:
		case SCROLL_SYMBOL:
		case SPEAR_SYMBOL:
		case SHIELD_SYMBOL:
			item_to_store = get_item_at(new_pos, level->items, level->item_number);
			
			if(item_to_store == NULL){
				perror("Error when getting item to store");
				exit(EXIT_FAILURE);
			}

			stored = store_item(level->player, item_to_store);
			
			if(stored == 0){	/* Succeeded */
				int stored_item_index = get_item_index(item_to_store, level->items, level->item_number);
				
				if(stored_item_index == -1){
					perror("Error when getting stored item index");
					exit(EXIT_FAILURE);
				}

				level->items[stored_item_index] = NULL;
			}
			
			player_move(new_pos, level->player);
			break;
		default :
			if(is_monster(ch))
				combat(level->player, get_monster_at(new_pos, level->monsters, level->monster_number), 0);
			break;
	}
}

void draw_level(Level *level){
	int x, y, monster_i, item_i;

	/* printing tiles */
	/* when dealing with tiles, y-6 will be used because of the INIT_HEIGHT offset */
	for(y = INIT_HEIGHT; y < MAX_HEIGHT; y++){
		for(x = 0; x < MAX_WIDTH; x++){
			mvaddch(y, x, level->tiles[y-6][x]);
		}
	}

	/* printing monsters */
	for(monster_i = 0; monster_i < level->monster_number; monster_i++){
		draw_monster(level->monsters[monster_i]);
	}

	for(item_i = 0; item_i < level->item_number; item_i++){
		if(level->items[item_i] != NULL)
			draw_item(level->items[item_i]);
	}

	if((level->level == 10 && level->monsters[0]->alive == 0) || level->level != 10)
		draw_stairs(level->stairs);

	draw_player(level->player);
}

void connect_doors(Level *level){
	int door_i, room_i, random_room, random_door, tries;

	for(room_i = 0; room_i < level->room_number; room_i++){
		for(door_i = 0; door_i < level->rooms[room_i]->door_number; door_i++){
			if(level->rooms[room_i]->doors[door_i]->connected == 1)
				continue;

			tries = 0;

			while(tries < 10){
				random_room = rand() % level->room_number;
				random_door = rand() % level->rooms[random_room]->door_number;

				if(level->rooms[random_room]->doors[random_door]->connected == 1 || random_room == room_i){
					tries++;
					continue;
				}
				path_find(&level->rooms[random_room]->doors[random_door]->pos, &level->rooms[room_i]->doors[door_i]->pos);

				level->rooms[room_i]->doors[door_i]->connected = 1;
				level->rooms[random_room]->doors[random_door]->connected = 1;
				break;
			}
		}
	}

	for(room_i = 0; room_i < level->room_number; room_i++)
		close_doors(level->rooms[room_i]);
}

char **save_level_pos(){
	int x, y;
	char **positions = malloc(sizeof(char *) * 25);

	if(positions == NULL){
		perror("Error on allocation of level positions");
		exit(EXIT_FAILURE);
	}

	/* y-6 used because of the offset */
	for(y = INIT_HEIGHT; y < MAX_HEIGHT; y++){
		positions[y-6] = malloc(sizeof(char) * 100);

		if(positions[y-6] == NULL){
			perror("Error on allocation of level position");
			exit(EXIT_FAILURE);
		}

		for(x = 0; x < MAX_WIDTH; x++){
			positions[y-6][x] = mvinch(y, x);
		}
	}

	return positions;
}

void free_level(Level *level){
	int i, j;
	/* free monsters */
	for(i = 0; i < level->monster_number; i++){
		if(level->monsters[i] != NULL)
			free(level->monsters[i]);
	}

	/* free items */
	for(i = 0; i < level->item_number; i++){
		if(level->items[i] != NULL){
			if(level->items[i]->type == WEAPON_TYPE)
				free(level->items[i]->item.weapon);
			else if(level->items[i]->type == SHIELD_TYPE)
				free(level->items[i]->item.shield);
			else if(level->items[i]->type == SCROLL_TYPE)
				free(level->items[i]->item.scroll);
			else if(level->items[i]->type == POTION_TYPE)
				free(level->items[i]->item.potion);

			free(level->items[i]);
		}
	}

	/* free doors and rooms */
	for(i = 0; i < level->room_number; i++){
		for(j = 0; j < level->rooms[i]->door_number; j++){
			free(level->rooms[i]->doors[j]);
		}
		free(level->rooms[i]->doors);
		free(level->rooms[i]);
	}

	/* free tiles */
	/* i-6 used because of the offset */
	for(i = INIT_HEIGHT; i < MAX_HEIGHT; i++){
		free(level->tiles[i-6]);
	}

	/* free the other things */
	free(level->monsters);
	free(level->items);
	free(level->tiles);
	free(level->rooms);
	free(level->stairs);
	free(level);
}

int is_same_pos(Position *pos1, Position *pos2){
	if(pos1->x == pos2->x && pos1->y == pos2->y)
		return 1;
	return 0;
}

