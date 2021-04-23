#ifndef ITEM_H
#define ITEM_H

#include "weapon.h"
#include "player.h"
#include "position.h"
#include "potion.h"
#include "scroll.h"
#include "shield.h"

typedef enum {
	WEAPON_TYPE,
	POTION_TYPE,
	SCROLL_TYPE,
	SHIELD_TYPE
} Item_type;

enum {
	SWORD_SYMBOL = 289,
	SCROLL_SYMBOL = 317,
	POTION_SYMBOL = 319,
	SPEAR_SYMBOL = 303,
	SHIELD_SYMBOL = 349
};

typedef struct Item {
	Item_type type;
	struct Position pos;
	char symbol;
	char name[64];
	int stored;
	int equipped;

	union {
		Weapon *weapon;
		Potion *potion;
		Scroll *scroll;
		Shield *shield;
	} item;
} Item;

Item *get_item_at(Position *pos, Item **items, int item_number);
int get_item_index(Item *item, Item **items, int item_number);
Item *create_sword(int attack, Monster_type affinity);
Item *create_spear(int attack, int effect);
Item *create_health_potion(int effect);
Item *create_scroll(Status effect);
Item *create_shield(int defense);
Item *select_item(int level);
void draw_item(Item *item);

#endif

