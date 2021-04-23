#include "core.h"
#include "main_menu.h"
#include "game.h"
#include "utils.h"

void menu_loop(void){
	int user_choice, game_state = -1, number_of_choices = 2;
	char *choices[3] = {"Start Game", "End Game", ""};

	Game game;
	game.current_level = 0;

	while(true){
		if(number_of_choices == 2){
			choices[0] = "Start Game";
			choices[1] = "End Game";
			choices[2] = "";
		}
		else if(number_of_choices == 3){
			choices[0] = "Continue Game";
			choices[1] = "Start Game";
			choices[2] = "End Game";
		}
		user_choice = main_menu(number_of_choices, choices);

		switch(user_choice){
			case START_GAME:
				if(game.current_level > 0) game.current_level--;
				if(game_state != -1 && game_state != 1){
					free_player(game.levels[game.current_level]->player);
					free_level(game.levels[game.current_level]);
				}
				game.current_level = 0;
				info_screen();
				game_state = game_loop(&game);
				clear();
				break;

			case QUIT_GAME:
				if(game.current_level > 0) game.current_level--;
				if(game_state != -1 && game_state != 1){
					free_player(game.levels[game.current_level]->player);
					free_level(game.levels[game.current_level]);
				}
				return;

			case CONTINUE_GAME:
				game_state = game_loop(&game);
				clear();
				break;
		}
		if(game_state == 1){
			game_state = -1;
			number_of_choices = 2;
		}
		else
			number_of_choices = 3;
	}
}

int main(void){
	start_ncurses();

	menu_loop();
	endwin();

	return 0;
}

