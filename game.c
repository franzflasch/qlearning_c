#include <stdio.h>
#include <game.h>

#define START_POSITION 3

static void game_draw(game_td *game)
{
	int i = 0;

	printf("#");
	for(i=0;i<game->map_size;i++)
	{
		if(game->player_pos == i)
			printf("P");
		else if(game->cheese_pos == i)
			printf("C");
		else if(game->pit_pos == i)
			printf("O");
		else
			printf("=");
	}
	printf("#");
	fflush(stdout);
	printf("\r");
}

static void game_loop(game_td *game, int move)
{
	/* get player input */
	if(move == MOVE_LEFT)
		game->player_pos = game->player_pos > 0 ? game->player_pos-1 : game->map_size-1;
	else if (move == MOVE_RIGHT)
		game->player_pos = game->player_pos < game->map_size-1 ? game->player_pos+1 : 0;

	if(game->player_pos == game->cheese_pos)
	{
		game->score += 1;
		game->player_pos = START_POSITION;
	}

	if(game->player_pos == game->pit_pos)
	{
		game->score -= 1;
		game->player_pos = START_POSITION;
	}
}

void game_init(game_td *game)
{
	game->player_pos = START_POSITION;
	game->pit_pos = 0;
	game->cheese_pos = 10;

	game->map_size = MAP_SIZE;
	game->score = 0;
	game->moves = 0;
}

void game_run(game_td *game, int (get_input(void)))
{
	int move = 0;

	while(game->score < 5 && game->score > -5)
	{
		game_draw(game);
		move = get_input();
		game_loop(game, move);
		game->moves +=1;
	}
	
	/* Draw one last time to update the */
	game_draw(game);
	
	if(game->score >= 5)
		printf("\n  You win in %d moves!\n", game->moves);
	else
	    printf("\n  Game over\n");
}
