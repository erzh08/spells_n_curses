#ifndef CORE_H
#define CORE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/******** Constants ********/
#define INIT_HEIGHT 6
#define MAX_HEIGHT 31
#define MAX_WIDTH 100

typedef enum {
	NORMAL_STT = 0,
	POISON_STT = 10,
	SLEEP_STT = 11,
	SLOW_STT = 12
} Status;

#endif

