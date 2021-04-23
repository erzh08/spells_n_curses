#ifndef WEAPON_H
#define WEAPON_H

#include "monster.h"

typedef enum {
	SWORD_TYPE,
	SPEAR_TYPE
} Weapon_type;

typedef struct Weapon {
	Weapon_type type;
	int attack;

	union {
		Monster_type affinity;
		Status effect;
	} effect;
} Weapon;

#endif

