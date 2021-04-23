#ifndef LEVEL_H
#define LEVEL_H

#include "monster.h"
#include "player.h"
#include "position.h"
#include "room.h"
#include "item.h"
#include "stairs.h"

typedef struct Level {
	char **tiles;
	int level;
	int room_number;
	int monster_number;
	int item_number;
	struct Stairs *stairs;
	struct Player *player;
	struct Room **rooms;
	struct Monster **monsters;
	struct Item **items;
} Level;

/* level/map functions */
Room **start_rooms(int room_number);
Room *select_room(Level* level);
Level *create_level(int level);
char **save_level_pos();
void free_level(Level *level);
void connect_doors(Level *level);
void draw_level(Level *level);
void check_pos(Position *new_pos, Level *level);

/* entities functions */
void add_items(Level *level);
void add_monsters(Level *level);
void move_monster(Level *level);
void equip_item(Player *player, struct Item *item);
void unequip_item(Player *player, Item_type type);
void discard_item(Player *player, struct Item *item);
void use_item(Level *level, struct Item *item);
int store_item(Player *player, struct Item *item);
int is_same_pos(Position *pos1, Position *pos2);

#endif

