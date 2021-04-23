#include "core.h"
#include "main_menu.h"

int main_menu(int number_of_items, char *choices[]){
	int item_i, ch, value;
	WINDOW *main_menu_win;
	MENU *menu;
	ITEM *current;
	ITEM **items = (ITEM**) malloc(sizeof(**items) * number_of_items);

	if(items == NULL){
		perror("Error on allocation of main menu items");
		exit(EXIT_FAILURE);
	}

	print_title();
	main_menu_win = newwin(3, 14, 27, 78);
	keypad(main_menu_win, TRUE);

	for(item_i = 0; item_i < number_of_items; item_i++){
		/* This function gets the choice and a description */
		items[item_i] = new_item(choices[item_i], "");
	}
	items[item_i] = (ITEM*)NULL;

	menu = new_menu(items);
	set_menu_win(menu, main_menu_win);
	set_menu_sub(menu, derwin(main_menu_win, 3, 14, 0, 0));
	post_menu(menu);
	refresh();
	wrefresh(main_menu_win);

	/* Menu loop */
	while(1){
		ch = wgetch(main_menu_win);

		switch(ch){
			case KEY_DOWN:
				menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
			case 10: /* ENTER key */
				current = current_item(menu);
				value = item_index(current);
				if(number_of_items == 3){
					if(value == 0) value = 2;
					else if(value == 1) value = 0;
					else if(value == 2) value = 1;
				}
				close_menu(number_of_items, menu, items, main_menu_win);
				return value;
			default:
				break;
		}
	}

	return 0;
}

void close_menu(int number_of_items, MENU *menu, ITEM **items, WINDOW* menu_win){
	int i;
	/* Removes the menu from the screen */
	unpost_menu(menu);
	free_menu(menu);

	for(i = 0; i < number_of_items; i++){
		free_item(items[i]);
	}

	free(items);
	delwin(menu_win);
	clear();
}

void print_title(void){
	mvprintw(20,50," ____             _ _       _        _    ____");
	mvprintw(21,50,"/ ___| _ __   ___| | |___  |_| _ __ |_|  / ___|   _ _ __ ___  ___  ___  ");
	mvprintw(22,50,"\\___ \\| '_ \\ / _ \\ | / __|    | '_ \\    | |  | | | | '__/ __|/ _ \\/ __|");
	mvprintw(23,50," ___) | |_) |  __/ | \\__ \\    | | | |   | |__| |_| | |  \\__ \\  __/\\__ \\");
	mvprintw(24,50,"|____/| .__/ \\___|_|_|___/    |_| |_|    \\____\\__,_|_|  |___/\\___||___/");
	mvprintw(25,50,"      |_|");
}

