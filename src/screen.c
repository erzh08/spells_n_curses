#include "core.h"
#include "utils.h"

void start_ncurses(void){
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	refresh();

	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);		/* Items */
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);	/* Beasts */
	init_pair(3, COLOR_GREEN, COLOR_BLACK);		/* Reptiles */
	init_pair(4, COLOR_WHITE, COLOR_BLACK);		/* Spirits */
	init_pair(5, COLOR_RED, COLOR_BLACK);		/* Dead player*/
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);	/* Stairs */
	init_color(POISON_STT, 118, 361, 184);
	init_pair(10, POISON_STT, COLOR_BLACK);		/* Poison */
	init_color(SLEEP_STT, 400, 200, 600);
	init_pair(11, SLEEP_STT, COLOR_BLACK);		/* Sleep */
	init_color(SLOW_STT, 392, 584, 929);
	init_pair(12, SLOW_STT, COLOR_BLACK);		/* Slow */

	/* Generates the "seed" to the rooms */
	srand(time(NULL));
}

void print_game_hub(Level *level){
	mvprintw(36, 0, "    Floor: %d", level->level);
	printw("    Level: %d", level->player->level);
	printw("    HP: %d(%d)", level->player->health, level->player->max_health);
	printw("    Attack: %d", level->player->attack);
	printw("    Exp: %d", level->player->exp);
	printw("    ");
	printw("    ");
}

void info_screen(void){
	WINDOW* info_win;
	clear();
	info_win = newwin(30, 105, 5, 30);
	keypad(info_win, TRUE);

	mvwprintw(info_win, 1, 7, "Spirits are white creatures that are only damaged by \"Spirit Banisher\" swords and are not\n  affected by poison, so take care.");

	wattron(info_win, COLOR_PAIR(REPTILE_TP));
	mvwprintw(info_win, 4, 7, "Reptiles");
	wattroff(info_win, COLOR_PAIR(REPTILE_TP));
	wprintw(info_win, " are normal creatures, much like ");
	wattron(info_win, COLOR_PAIR(BEAST_TP));
	wprintw(info_win, "Beasts");
	wattroff(info_win, COLOR_PAIR(BEAST_TP));
	wprintw(info_win, ", affected by all effects and being damaged by\n  all ");
	wattron(info_win, COLOR_PAIR(1));
	wprintw(info_win, "Weapons");
	wattroff(info_win, COLOR_PAIR(1));
	waddch(info_win, '.');

	wattron(info_win, COLOR_PAIR(1));
	mvwprintw(info_win, 7, 7, "Scrolls(=)");
	wattroff(info_win, COLOR_PAIR(1));
	wprintw(info_win, " are items that can be used to affect all monsters on the floor depending on its\n  effects, that can be ");
	wattron(info_win, COLOR_PAIR(SLOW_STT));
	wprintw(info_win, "Slow");
	wattroff(info_win, COLOR_PAIR(SLOW_STT));
	waddch(info_win, ',');
	wattron(info_win, COLOR_PAIR(POISON_STT));
	wprintw(info_win, " Poison");
	wattroff(info_win, COLOR_PAIR(POISON_STT));
	wprintw(info_win, " or ");
	wattron(info_win, COLOR_PAIR(SLEEP_STT));
	wprintw(info_win, "Sleep");
	wattroff(info_win, COLOR_PAIR(SLEEP_STT));
	waddch(info_win, '.');

	wattron(info_win, COLOR_PAIR(1));
	mvwprintw(info_win, 10, 7, "Swords(!)");
	wattroff(info_win, COLOR_PAIR(1));
	wprintw(info_win, " have affinities for each monster type, and can be divided into name(dmg):");

	mvwprintw(info_win, 11, 3, "Dagger(5), Kodachi/Shortsword(10), Katana/Broadsword(15), Odachi/Longsword(20), Zweihander(25).");

	wattron(info_win, COLOR_PAIR(1));
	mvwprintw(info_win, 13, 7, "Spears(/)");
	wattroff(info_win, COLOR_PAIR(1));
	wprintw(info_win, " have a 50%% chance of affecting the attacked monster with its respective effect, being\n  divided into:");

	mvwprintw(info_win, 15, 3, "Spear(3), Lance(7), Glaive(12), Voulge(18), and another one.");

	mvwprintw(info_win, 17, 7, "(Health) ");
	wattron(info_win, COLOR_PAIR(1));
	wprintw(info_win, "Potions(?)");
	wattroff(info_win, COLOR_PAIR(1));
	wprintw(info_win, " are items that restore the player's health, and are divided into type(hp):");

	mvwprintw(info_win, 18, 3, "Small(5), Medium(15), Big(25) and High(40).");

	wattron(info_win, COLOR_PAIR(1));
	mvwprintw(info_win, 20, 7, "Shields(])");
	wattroff(info_win, COLOR_PAIR(1));
	wprintw(info_win, " are items which defense sums up with the player's, and are divided into type(def):");

	mvwprintw(info_win, 21, 3, "Wood(10), Tantalum(30) and Titanium(60).");

	wattron(info_win, COLOR_PAIR(6));
	mvwprintw(info_win, 23, 7, "Stairs(%%)");
	wattroff(info_win, COLOR_PAIR(6));
	wprintw(info_win, " take you to the next floor, but the ones on the 10th floor only appear after defeating\n  the ");
	wattron(info_win, COLOR_PAIR(REPTILE_TP));
	wprintw(info_win, "Wyvern(W)");
	wattroff(info_win, COLOR_PAIR(REPTILE_TP));
	wprintw(info_win, " that lies there, allowing you to leave the dungeon (you knew we would get there).");

	mvwprintw(info_win, 26, 7, "After killing each monster you get some EXP, that raises your HP, ATK and DMG, and knowing this,\n  good luck.");

	box(info_win, 0, 0);
	refresh();
	wrefresh(info_win);
	getch();
	wborder(info_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(info_win);
	delwin(info_win);
	clear();
}

void thanks_scr(void){
	mvprintw(18, 45, " ________             __          ___                __          _           __");
	mvprintw(19, 45, "/_  __/ /  ___ ____  / /__ ___   / _/__  ____  ___  / /__ ___ __(_)__  ___ _/ /");
	mvprintw(20, 45, " / / / _ \\/ _ `/ _ \\/  '_/(_-<  / _/ _ \\/ __/ / _ \\/ / _ `/ // / / _ \\/ _ `/_/");
	mvprintw(21, 45, "/_/ /_//_/\\_,_/_//_/_/\\_\\/___/ /_/ \\___/_/   / .__/_/\\_,_/\\_, /_/_//_/\\_, (_)");
	mvprintw(22, 45, "                                            /_/          /___/       /___/");
}

