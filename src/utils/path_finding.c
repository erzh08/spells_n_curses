#include "core.h"
#include "utils.h"

void path_find(Position *start, Position *end){
	int i, j, x, y, frontier_index = 0, frontier_count = 0;
	int **frontier = (int**) malloc(sizeof(int*) * MAX_HEIGHT * MAX_WIDTH);
	int ***came_from = (int***) malloc(sizeof(int**) * MAX_HEIGHT);

	if(frontier == NULL){
		perror("Error on allocation of frontier");
		exit(EXIT_FAILURE);
	}

	
	if(came_from == NULL){
		perror("Error on allocation of came_from");
		exit(EXIT_FAILURE);
	}
	

	for(i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++){
		frontier[i] = (int *) malloc(sizeof(int) * 2);

		if(frontier[i] == NULL){
			perror("Error on allocation of frontier[i]");
			exit(EXIT_FAILURE);
		}
	}

	for(i = 0; i < MAX_HEIGHT; i++){
		came_from[i] = (int**) malloc(sizeof(int*) * MAX_WIDTH);

		if(came_from[i] == NULL){
			perror("Error on allocation of came_from[i]");
			exit(EXIT_FAILURE);
		}

		for(j = 0; j < MAX_WIDTH; j++){
			came_from[i][j] = (int *) malloc(sizeof(int) * 2);

			if(came_from[i][j] == NULL){
				perror("Error on allocation of came_from[i][j]");
				exit(EXIT_FAILURE);
			}

			came_from[i][j][0] = -1;
			came_from[i][j][1] = -1;
		}
	}

	/* add start to came_from */
	came_from[start->y][start->x][0] = -9;
	came_from[start->y][start->x][1] = -9;

	/* add start position to frontier */
	add_position_yx(frontier, frontier_count, start->y, start->x);
	frontier_count++;

	while(frontier_index < frontier_count){
		y = frontier[frontier_index][0];
		x = frontier[frontier_index][1];
		frontier_index++;

		if(y == end->y && x == end->x)
			break;

		frontier_count = add_neighbors(frontier, came_from, frontier_count, y, x);
	}

	y = end->y;
	x = end->x;

	while(y != start->y || x != start->x){
		int temp_y = y;
		y = came_from[y][x][0];
		x = came_from[temp_y][x][1];
		if(mvinch(y, x) != '+')
			mvprintw(y, x, "#");
	}

	free_arrays(frontier, came_from);
}

void add_position_yx(int **frontier, int count, int y, int x){
	frontier[count][0] = y;
	frontier[count][1] = x;
}

int check_position(int y, int x){
	char ch_in_pos = mvinch(y, x);
	if(ch_in_pos == '.' || ch_in_pos == '|' || ch_in_pos == '-')
		return 0;

	return 1;
}


int add_neighbors(int **frontier, int ***came_from, int count, int y, int x){
	/* up */
	if(y > 0 && came_from[y-1][x][0] < 0 && check_position(y-1, x)){
		add_position_yx(frontier, count, y-1, x);
		count++;
		came_from[y-1][x][0] = y;
		came_from[y-1][x][1] = x;
	}
	/* down */
	if(y < (MAX_HEIGHT - 1) && came_from[y+1][x][0] < 0  && check_position(y+1, x)){
		add_position_yx(frontier, count, y+1, x);
		count++;
		came_from[y+1][x][0] = y;
		came_from[y+1][x][1] = x;
	}
	/* left */
	if(x > 0 && came_from[y][x-1][0] < 0 && check_position(y, x-1)){
		add_position_yx(frontier, count, y, x-1);
		count++;
		came_from[y][x-1][0] = y;
		came_from[y][x-1][1] = x;
	}
	/* right */
	if(x < (MAX_WIDTH - 1) && came_from[y][x+1][0] < 0 && check_position(y, x+1)){
		add_position_yx(frontier, count, y, x+1);
		count++;
		came_from[y][x+1][0] = y;
		came_from[y][x+1][1] = x;
	}

	return count;
}

void free_arrays(int **frontier, int ***came_from){
	int i, j;

	for(i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++){
		free(frontier[i]);
	}
	free(frontier);

	for(i = 0; i < MAX_HEIGHT; i++){
		for(j = 0; j < MAX_WIDTH; j++){
			free(came_from[i][j]);
		}
		free(came_from[i]);
	}
	free(came_from);
}

