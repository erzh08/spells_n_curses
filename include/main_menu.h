#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <menu.h>

typedef enum {
	START_GAME,
	QUIT_GAME,
	CONTINUE_GAME
} Game_State;

void menu_loop(void);
int main_menu(int number_of_items, char *choices[]);
void close_menu(int number_of_items, MENU *menu, ITEM **items, WINDOW *menu_win);
void print_title(void);

#endif

