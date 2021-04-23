#ifndef LOG_H
#define LOG_H

typedef enum {
	KILL_EV,
	PICK_EV,
	DISCARD_EV,
	USE_EV,
	DIE_EV,
	DMG_EV
} Event_type;

WINDOW *start_log(void);
void event_log(Event_type ev, char* affected);
void update_log(WINDOW *log_win);
void close_log(WINDOW *log_win);

#endif

