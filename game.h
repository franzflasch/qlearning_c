#ifndef GAME_H
#define GAME_H

#define MAP_SIZE 12

#define MOVE_LEFT 0
#define MOVE_RIGHT 1

typedef struct game_struct
{
	int player_pos;
	int pit_pos;
	int cheese_pos;

	int map_size;	
	int score;
	int moves;
		
} game_td;

void game_init(game_td *game);
void game_run(game_td *game, int (get_input(void)));

#endif /* GAME_H */
