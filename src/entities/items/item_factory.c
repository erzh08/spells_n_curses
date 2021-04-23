#include "core.h"
#include "item.h"

Item *create_sword(int attack, Monster_type affinity){
	Item *item = (Item*) malloc(sizeof(Item));
	
	if(item == NULL){
		perror("Error on allocation of item");
		exit(EXIT_FAILURE);
	}

	item->type = WEAPON_TYPE;
	item->stored = 0;
	item->equipped = 0;
	item->item.weapon = (Weapon*) malloc(sizeof(Weapon));

	if(item->item.weapon == NULL){
		perror("Error on allocation of sword");
		exit(EXIT_FAILURE);
	}

	item->item.weapon->type = SWORD_TYPE;

	if(attack <= 25)
		attack = 5;
	else if(attack <= 30)
		attack = 10;
	else if(attack <= 40)
		attack = 15;
	else if(attack <= 48)
		attack = 20;
	else
		attack = 25;

	item->item.weapon->attack = attack;
	item->item.weapon->effect.affinity = affinity;
	item->symbol = '!';

	switch(affinity){
		case BEAST_TP:
			strcpy(item->name, "Beast Killer ");
			break;

		case REPTILE_TP:
			strcpy(item->name, "Reptile Slayer ");
			break;

		case SPIRIT_TP:
			strcpy(item->name, "Spirit Banisher ");
			break;

		default:
			strcpy(item->name, "");
			break;
	}

	switch(attack){
		case 5:
			strcat(item->name, "Dagger");
			break;

		case 10:
			if(affinity == SPIRIT_TP)
				strcat(item->name, "Kodachi");
			else
				strcat(item->name, "Shortsword");

			break;

		case 15:
			if(affinity == SPIRIT_TP)
				strcat(item->name, "Katana");
			else
				strcat(item->name, "Broadsword");

			break;

		case 20:
			if(affinity == SPIRIT_TP)
				strcat(item->name, "Odachi");
			else
				strcat(item->name, "Longsword");

			break;

		default:
			strcat(item->name, "Zweihander");
			break;
	}

	return item;
}

Item *create_spear(int attack, int effect){
	Item *item = (Item*) malloc(sizeof(Item));

	if(item == NULL){
		perror("Error on allocation of item");
		exit(EXIT_FAILURE);
	}

	item->type = WEAPON_TYPE;
	item->stored = 0;
	item->equipped = 0;
	item->item.weapon = (Weapon*) malloc(sizeof(Weapon));

	if(item->item.weapon == NULL){
		perror("Error on allocation of spear");
		exit(EXIT_FAILURE);
	}

	item->item.weapon->type = SPEAR_TYPE;

	if(attack <= 50)
		attack = 3;

	else if(attack <= 75)
		attack = 7;

	else if(attack <= 90)
		attack = 12;

	else if(attack <= 98)
		attack = 18;

	else{
		attack = 50;
		effect = 4;
	}

	item->item.weapon->attack = attack;
	item->symbol = '/';

	switch(effect){
		case 1:
			strcpy(item->name, "Decelerating ");
			item->item.weapon->effect.effect = SLOW_STT;
			break;

		case 2:
			strcpy(item->name, "Slothful ");
			item->item.weapon->effect.effect = SLEEP_STT;
			break;

		case 3:
			strcpy(item->name, "Venomous ");
			item->item.weapon->effect.effect = POISON_STT;
			break;

		default:
			strcpy(item->name, "");
			item->item.weapon->effect.effect = NORMAL_STT;
			break;
	}

	switch(attack){
		case 3:
			strcat(item->name, "Spear");
			break;

		case 7:
			strcat(item->name, "Lance");
			break;

		case 12:
			strcat(item->name, "Glaive");
			break;

		case 18:
			strcat(item->name, "Voulge");
			break;

		default:
			strcat(item->name, "Gae Bulg");
			break;
	}

	return item;
}

Item *create_health_potion(int effect){
	Item *item = (Item*) malloc(sizeof(Item));
	
	if(item == NULL){
		perror("Error on allocation of item");
		exit(EXIT_FAILURE);
	}

	item->type = POTION_TYPE;
	item->stored = 0;
	item->equipped = 0;
	item->item.potion = (Potion*) malloc(sizeof(Potion));
	
	if(item->item.potion == NULL){
		perror("Error on allocation of potion");
		exit(EXIT_FAILURE);
	}

	if(effect <= 8)
		effect = 5;

	else if(effect <= 11)
		effect = 15;

	else if(effect <= 13)
		effect = 25;

	else
		effect = 40;

	item->item.potion->effect = effect;
	item->symbol = '?';

	switch(effect){
		case 5:
			strcpy(item->name, "Small Health Potion");
			break;

		case 15:
			strcpy(item->name, "Medium Health Potion");
			break;

		case 25:
			strcpy(item->name, "Big Health Potion");
			break;

		case 40:
			strcpy(item->name, "High Health Potion");
			break;

		default:
			break;
	}

	return item;
}

Item *create_scroll(Status effect){
	Item *item = (Item*) malloc(sizeof(Item));
	
	if(item == NULL){
		perror("Error on allocation of item");
		exit(EXIT_FAILURE);
	}

	item->type = SCROLL_TYPE;
	item->stored = 0;
	item->equipped = 0;
	item->item.scroll = (Scroll*) malloc(sizeof(Scroll));
	
	if(item->item.scroll == NULL){
		perror("Error on allocation of scroll");
		exit(EXIT_FAILURE);
	}

	item->item.scroll->effect = effect;
	item->symbol = '=';

	switch(effect){
		case POISON_STT:
			strcpy(item->name, "Poisoning Scroll");
			break;

		case SLEEP_STT:
			strcpy(item->name, "Sleeping Scroll");
			break;

		case SLOW_STT:
			strcpy(item->name, "Slowing Scroll");
			break;

		default:
			break;
	}

	return item;
}

Item *create_shield(int defense){
	Item *item = (Item*) malloc(sizeof(Item));
	
	if(item == NULL){
		perror("Error on allocation of item");
		exit(EXIT_FAILURE);
	}

	item->type = SHIELD_TYPE;
	item->stored = 0;
	item->equipped = 0;
	item->item.shield = (Shield*) malloc(sizeof(Shield));
	
	if(item->item.shield == NULL){
		perror("Error on allocation of shield");
		exit(EXIT_FAILURE);
	}

	if(defense <= 35)
		defense = 10;

	else if(defense <= 48)
		defense = 30;

	else
		defense = 60;

	item->item.shield->defense = defense;
	item->symbol = ']';

	switch (defense){
		case 10:
			strcpy(item->name, "Wooden shield");
			break;

		case 30:
			strcpy(item->name, "Tantalum shield");
			break;

		default:
			strcpy(item->name, "Titanium shield");
			break;
	}

	return item;
}

