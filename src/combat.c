#include "core.h"
#include "utils.h"
#include "log.h"

void combat(Player *player, Monster *monster, int order){
	/* player attacks monster */
	if(order == 0){
		int final_damage = player->attack;
		char buffer[64];

		if(player->equipped_weapon != NULL){
			final_damage += player->equipped_weapon->item.weapon->attack;

			if(player->equipped_weapon->item.weapon->type == SWORD_TYPE){
				if(player->equipped_weapon->item.weapon->effect.affinity == monster->type)
					final_damage += player->equipped_weapon->item.weapon->attack / ((rand() % 2) + 1);

				if((monster->type == SPIRIT_TP) && (player->equipped_weapon->item.weapon->effect.affinity != SPIRIT_TP))
					final_damage -= player->equipped_weapon->item.weapon->attack;
			}
			else{
				if(monster->type == SPIRIT_TP)
					final_damage -= player->equipped_weapon->item.weapon->attack;

				switch(player->equipped_weapon->item.weapon->effect.effect){
					case SLOW_STT:
						if(rand() % 2){
							monster->stat = SLOW_STT;
							monster->stat_counter = 10;
						}
						break;

					case POISON_STT:
						if(monster->type != SPIRIT_TP){
							if(rand() % 2){
								monster->stat = POISON_STT;
								monster->stat_counter = 8;
							}
						}
						break;

					case SLEEP_STT:
						if(rand() % 2){
							monster->stat = SLEEP_STT;
							monster->stat_counter = 5;
						}
						break;

					default:
						break;
				}
			}
		}

		final_damage = (final_damage * final_damage) / (final_damage + (monster->defense / ((rand() % 2) + 1)));

		monster->health -= final_damage;

		sprintf(buffer, "%s took %d", monster->name, final_damage);

		event_log(DMG_EV, buffer);

		if(monster->health > 0){
			if(monster->path_finding == 1)
				if(monster->stat != SLEEP_STT)
					player->health -= (monster->attack * monster->attack) / (monster->attack + (player->defense / ((rand() % 2) + 1)));
		}
		else{
			kill_monster(monster);
			event_log(KILL_EV, monster->name);
			player->exp += monster->experience;
		}
	}
	/* monster attacks player */
	else{
		int final_defense = player->defense;

		if(player->equipped_shield != NULL)
			final_defense += player->equipped_shield->item.shield->defense;

		player->health -= (monster->attack * monster->attack) / (monster->attack + (final_defense / ((rand() % 2) + 1)));
	}
}

