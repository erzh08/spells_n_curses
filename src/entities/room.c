#include "core.h"
#include "room.h"

Room *create_room(int grid, int door_number){
	int i;
	Room *new_room = (Room *) malloc(sizeof(Room));

	if(new_room == NULL){
		perror("Error on allocation of room");
		exit(EXIT_FAILURE);
	}

	new_room->door_number = door_number;

	switch(grid){
		case 0:
			new_room->pos.x = 0;
			new_room->pos.y = 6;
			break;
		case 1:
			new_room->pos.x = 33;
			new_room->pos.y = 6;
			break;
		case 2:
			new_room->pos.x = 66;
			new_room->pos.y = 6;
			break;
		case 3:
			new_room->pos.x = 0;
			new_room->pos.y = 20;
			break;
		case 4:
			new_room->pos.x = 33;
			new_room->pos.y = 20;
			break;
		case 5:
			new_room->pos.x = 66;
			new_room->pos.y = 20;
			break;
	}

	new_room->height = rand() % 6 + 4;	/* max size: 9 */
	new_room->width = rand() % 14 + 4;	/* max size: 17 */

	/* offset */
	new_room->pos.x += rand() % (30 - new_room->width) + 1;
	new_room->pos.y += rand() % (10 - new_room->height) + 1;

	new_room->doors = (Door**) malloc(sizeof(Door*) * door_number);

	if(new_room->doors == NULL){
		perror("Error on allocation of doors");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < door_number; i++){
		new_room->doors[i] = (Door *) malloc(sizeof(Door));

		if(new_room->doors[i] == NULL){
			perror("Error on allocation of door");
			exit(EXIT_FAILURE);
		}

		new_room->doors[i]->connected = 0;

	}

	/* top door */
	new_room->doors[0]->pos.x = rand() % (new_room->width - 2) + new_room->pos.x + 1;
	new_room->doors[0]->pos.y = new_room->pos.y;

	/* left door */
	new_room->doors[1]->pos.y = rand() % (new_room->height - 2) + new_room->pos.y + 1;
	new_room->doors[1]->pos.x = new_room->pos.x;

	/* bottom door */
	new_room->doors[2]->pos.x = rand() % (new_room->width - 2) + new_room->pos.x + 1;
	new_room->doors[2]->pos.y = new_room->pos.y + new_room->height - 1;

	/* right door */
	new_room->doors[3]->pos.y = rand() % (new_room->height - 2) + new_room->pos.y + 1;
	new_room->doors[3]->pos.x = new_room->pos.x + new_room->width - 1;

	return new_room;
}

void set_monster_starting_pos(Monster *monster, Room *room){
	monster->pos.x = (rand() % (room->width - 2)) + room->pos.x + 1;
	monster->pos.y = (rand() % (room->height - 2)) + room->pos.y + 1;
}

void set_item_starting_pos(Item *item, Room *room){
	item->pos.x = (rand() % (room->width - 2)) + room->pos.x + 1;
	item->pos.y = (rand() % (room->height - 2)) + room->pos.y + 1;
}

void place_player(Room *room, Player *player){
	player->pos.x = room->pos.x + (rand() % (room->width - 2)) + 1;
	player->pos.y = room->pos.y + (rand() % (room->height - 2)) + 1;
}

void set_stairs_starting_pos(Room *room, Stairs *stairs){
	stairs->pos.x = room->pos.x + (rand() % (room->width - 2)) + 1;
	stairs->pos.y = room->pos.y + (rand() % (room->height - 2)) + 1;
}

void draw_stairs(Stairs *stairs){
	attron(COLOR_PAIR(6));
	mvprintw(stairs->pos.y, stairs->pos.x, "%%");
	attroff(COLOR_PAIR(6));
}

void draw_room(Room *room){
	int x, y, door_num;

	/* draw top and bottom */
	for(x = room->pos.x; x < room->pos.x + room->width; x++){
		mvprintw(room->pos.y, x, "-");	/* top */
		mvprintw(room->pos.y + room->height - 1, x, "-");  /* bottom */
	}

	/* floors and side walls */
	for(y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++){
		/* draw side walls */
		mvprintw(y, room->pos.x, "|");	/* left walls */

		/* draw floors */
		for(x = room->pos.x + 1; x < room->pos.x + room->width - 1; x++){
			mvprintw(y, x, ".");
		}

		mvprintw(y, room->pos.x + room->width - 1, "|"); /* right walls */
	}

	/* draw doors */
	for(door_num = 0; door_num < 4; door_num++)
		mvprintw(room->doors[door_num]->pos.y, room->doors[door_num]->pos.x, "+");
}

void close_doors(Room *room){
	int door_i;

	for(door_i = 0; door_i < 4; door_i++){
		if(room->doors[door_i]->connected == 0){
			if(door_i % 2)
				mvprintw(room->doors[door_i]->pos.y, room->doors[door_i]->pos.x, "|");
			else
				mvprintw(room->doors[door_i]->pos.y, room->doors[door_i]->pos.x, "-");
		}
	}
}

