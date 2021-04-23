#include "core.h"
#include "log.h"

WINDOW *start_log(void){
	WINDOW *log_win = newwin(5, 66, 0, 5);
	return log_win;
}

void event_log(Event_type ev, char* affected){
	mvprintw(2, 10, "                                                       ");

	switch(ev){
		case KILL_EV:
			mvprintw(2, 10, "Player has killed a %s", affected);
			break;
		case PICK_EV:
			mvprintw(2, 10, "Player has picked up a %s", affected);
			break;
		case DISCARD_EV:
			mvprintw(2, 10, "Player has discarded a %s", affected);
			break;
		case USE_EV:
			mvprintw(2, 10, "Player has used a %s", affected);
			break;
		case DIE_EV:
			mvprintw(2, 10, "Player has died :(");
			break;
		case DMG_EV:
			mvprintw(2, 10, "%s damage from player", affected);
			break;
	}
}

void update_log(WINDOW *log_win){
	box(log_win, 0, 0);
	wrefresh(log_win);
}

void close_log(WINDOW *log_win){
	wborder(log_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

	mvprintw(3, 10, "                                                       ");

	wrefresh(log_win);
	delwin(log_win);
}

