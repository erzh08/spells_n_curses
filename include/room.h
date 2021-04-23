#ifndef ROOM_H
#define ROOM_H

#include "door.h"
#include "monster.h"
#include "player.h"
#include "position.h"
#include "stairs.h"

typedef struct Room {
	struct Position pos;
	int height;
	int width;
	int door_number;
	struct Door **doors;
} Room;

Room *create_room(int grid, int door_number);
void draw_room(Room *room);
void draw_stairs(Stairs *stairs);
void place_player(Room *room, Player *player);
void close_doors(Room *room);

void set_monster_starting_pos(Monster *monster, Room *room);
void set_item_starting_pos(Item *item, Room *room);
void set_stairs_starting_pos(Room *room, Stairs *stairs);

#endif

