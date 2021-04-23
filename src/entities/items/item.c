#include "core.h"
#include "item.h"

Item *get_item_at(Position *pos, Item **items, int item_number){
	int item_i;

	for(item_i = 0; item_i < item_number; item_i++){
		if(items[item_i] != NULL && items[item_i]->pos.y == pos->y && items[item_i]->pos.x == pos->x)
			return items[item_i];
	}

	return NULL;
}

int get_item_index(Item *item, Item **items, int item_number){
	int item_i;
	for(item_i = 0; item_i < item_number; item_i++)
		if(items[item_i] != NULL && items[item_i] == item)
			return item_i;
	return -1;
}

void draw_item(Item *item){
	if(item->stored == 0){
		attron(COLOR_PAIR(1));
		mvprintw(item->pos.y, item->pos.x, "%c", item->symbol);
		attroff(COLOR_PAIR(1));
	}
}

Item *select_item(int level){
	int item;

	switch(level){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			item = rand() % 5;
			break;

		default:
			break;
	}

	switch(item){
		case 0:
			return create_sword((rand() % 50), ((rand() % 4) + 1));

		case 1:
			return create_health_potion((rand() % 15));

		case 2:
			return create_scroll(10 + (rand() % 3));

		case 3:
			return create_spear((rand() % 100), (rand() % 4));

		case 4:
			return create_shield((rand() % 50));

		default:
			break;
	}

	return NULL;
}

