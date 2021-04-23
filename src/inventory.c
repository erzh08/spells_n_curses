#include "core.h"
#include "inventory.h"
#include "log.h"

void inventory(Level *level){
	int i, choice, highlight = 0;
	WINDOW *invent_win = newwin(17, 31, 0, 105);
	box(invent_win, 0, 0);
	mvwprintw(invent_win, 1, 2, "Inventory");
	keypad(invent_win, TRUE);

	while(1){
		for(i = 0; i < level->player->item_quant; i++){
			if(i == highlight)
				wattron(invent_win, A_REVERSE);
			if(level->player->items[i]->equipped)
				wattron(invent_win, COLOR_PAIR(1));
			mvwprintw(invent_win, (3 + i), 2, level->player->items[i]->name);
			wattroff(invent_win, A_REVERSE);
			wattroff(invent_win, COLOR_PAIR(1));
		}

		choice = wgetch(invent_win);

		switch(choice){
			case KEY_UP:
				if(highlight > 0)
					highlight--;
				break;

			case KEY_DOWN:
				if(highlight < level->player->item_quant - 1)
					highlight++;
				break;
			default:
				break;
		}

		if(choice == 10 && level->player->item_quant > 0){
			item_options(level, level->player->items[highlight]);
			break;
		}

		if(choice == 'e')
			break;
	}

	clear_inventory(invent_win);
}

void clear_inventory(WINDOW *invent_win){
	int i, j;
	wborder(invent_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	for(i = 0; i < 31; i++)
		for(j = 0; j < 17; j++)
			mvwaddch(invent_win, j, i, ' ');

	wrefresh(invent_win);

	delwin(invent_win);
}

void item_options(Level *level, Item *item){
	WINDOW *options_win = newwin(3, 31, 19, 105);
	int choice, i, highlight = 0, dist;
	char **choices = malloc(sizeof(char*) * 3);

	if(choices == NULL){
		perror("Error on allocation of choices");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < 3; i++){
		choices[i] = malloc(8);

		if(choices[i] == NULL){
			perror("Error on allocation of a choice");
			exit(EXIT_FAILURE);
		}
	}

	box(options_win, 0, 0);

	if((item->type == WEAPON_TYPE || item->type == SHIELD_TYPE) && item->equipped == 0)
		strcpy(choices[0], "Equip");
	else if((item->type == WEAPON_TYPE || item->type == SHIELD_TYPE) && item->equipped)
		strcpy(choices[0], "Unequip");
	else if(item->type == POTION_TYPE || item->type == SCROLL_TYPE)
		strcpy(choices[0], "Use");

	strcpy(choices[1], "Discard");
	strcpy(choices[2], "Close");
	keypad(options_win, TRUE);

	while(1){
		dist = 2;

		for(i = 0; i < 3; i++){
			if(i == highlight)
				wattron(options_win, A_REVERSE);

			mvwprintw(options_win, 1, dist, choices[i]);
			wattroff(options_win, A_REVERSE);
			dist += 10;
		}

		choice = wgetch(options_win);

		switch(choice){
			case KEY_LEFT:
				if(highlight > 0)
					highlight--;
				break;

			case KEY_RIGHT:
				if(highlight < 2)
					highlight++;
				break;

			default:
				break;
		}

		if(choice == 10){
			break;
		}

		if(choice == 27){    /* ESC_KEY */
			clear_options(options_win);
			return;
		}
	}

	switch(highlight){
		case 0:
			if((item->type == WEAPON_TYPE || item->type == SHIELD_TYPE) && item->equipped == 0)
				equip_item(level->player, item);

			else if(item->type == WEAPON_TYPE && item->equipped)
				unequip_item(level->player, WEAPON_TYPE);

			else if(item->type == SHIELD_TYPE && item->equipped)
				unequip_item(level->player, SHIELD_TYPE);

			else{
				event_log(USE_EV, item->name);
				use_item(level, item);
			}

			break;

		case 1:
			if(item->equipped){
				if(item->type == WEAPON_TYPE)
					unequip_item(level->player, WEAPON_TYPE);
				else
					unequip_item(level->player, SHIELD_TYPE);
			}

			event_log(DISCARD_EV, item->name);
			discard_item(level->player, item);

			break;

		default:
			break;
	}

	for(i = 0; i < 3; i++)
		free(choices[i]);
	free(choices);

	clear_options(options_win);
}

void clear_options(WINDOW *win){
	int i;
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	for(i = 0; i < 31; i++)
		mvwaddch(win, 1, i, ' ');
	wrefresh(win);
	delwin(win);
}

