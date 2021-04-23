#ifndef INVENTORY_H
#define INVENTORY_H

#include "player.h"
#include "main_menu.h"
#include "level.h"

void inventory(Level *level);
void item_options(Level *level, Item *item);
void clear_inventory(WINDOW *invent_win);
void clear_options(WINDOW *win);

#endif

