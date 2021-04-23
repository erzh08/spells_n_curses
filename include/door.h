#ifndef DOOR_H
#define DOOR_H

#include "position.h"

typedef struct Door {
	struct Position pos;
	int connected;
} Door;

#endif

