#include "core.h"
#include "game.h"
#include "level.h"
#include "utils.h"
#include "inventory.h"
#include "log.h"

void render(Game *game, WINDOW *log_win){
	print_game_hub(game->levels[game->current_level - 1]);
	draw_level(game->levels[game->current_level - 1]);
	update_log(log_win);
}

int game_loop(Game *game){
	Level *level;
	WINDOW *log_win;
	Position *new_pos = NULL;
	Player *player = NULL;
	int ch = '\0';

	if(game->current_level == 0)
		game->levels[game->current_level++] = create_level(1);

	level = game->levels[game->current_level - 1];
	player = level->player;

	log_win = start_log();

	/* MAIN GAME LOOP */
	while(ch != 'q'){
		if(ch == 'e'){
			inventory(level);
			ch = '\0';
		}
		new_pos = handle_input(ch, player);
		check_pos(new_pos, level);

		move_monster(level);
		move(player->pos.y, player->pos.x);
		check_level(player);

		render(game, log_win);
		if(player->health <= 0){
			player_dies(player);
			game->current_level = 0;
			free_player(player);
			free_level(level);
			free(new_pos);
			event_log(DIE_EV, NULL);
			getch();
			close_log(log_win);
			clear();
			refresh();
			return 1;
		}

		if(new_pos->y == level->stairs->pos.y && new_pos->x == level->stairs->pos.x){
			if(level->level != 10){
				clear();
				game->levels[game->current_level] = create_level(game->current_level + 1);
				free_level(level);
				level = game->levels[game->current_level++];
				player->pos = level->player->pos;
				free_player(level->player);
				level->player = player;
				render(game, log_win);
			}
			else{
				free_player(player);
				free_level(level);
				free(new_pos);
				game->current_level = 0;
				close_log(log_win);
				clear();
				thanks_scr();
				getch();
				return 1;
			}
		}

		ch = getch();

		if(new_pos != NULL)
			free(new_pos);
	}

	close_log(log_win);
	clear();
	refresh();
	return 0;
}

