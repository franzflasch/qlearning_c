#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

#include <qtable.h>
#include <game.h>

#define STATES MAP_SIZE
#define ACTIONS 2

qtable_td qtable = { 0 };
game_td game = { 0 };

static int get_input(void)
{
	int move = 0;
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

	while(1)
	{	
	    character = fgetc(stdin);
   		if(character == 'a') { move = MOVE_LEFT; break; }
   		if(character == 'd') { move = MOVE_RIGHT; break; }
	}
	
    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

	return move;
}

static float get_rand(void)
{
	 return (float)rand()/(float)RAND_MAX;
}

static int get_input_qlearning(void)
{
	static int first_run = 1;
	static int old_score = 0;
	static int old_state = 0;
	static int action_taken_index = 0;
	const float epsilon = 0.9;

	int outcome_state = 0;
	float reward = 0;

	usleep(10000);

	if(!first_run)
	{
		if(old_score < game.score)
			reward = 1;
		else if(old_score > game.score)
			reward = -1;

		outcome_state = game.player_pos;
		qtable_update(&qtable, old_state, outcome_state, action_taken_index, 0.2, 0.9, reward);
	}
	else
		first_run = 0;
	
	old_score = game.score;
	old_state = game.player_pos;

	/* Chose action based on Q value estimates for state */
	if(get_rand() > epsilon)
	{
		//printf("RANDOM\n");
		action_taken_index = (rand() % ACTIONS);
	}
	else
	{
		//printf("QTABLE\n");
		action_taken_index = qtable.values[game.player_pos][0] > qtable.values[game.player_pos][1] ? MOVE_LEFT : MOVE_RIGHT;
	}

	//printf("action taken %d\n", action_taken_index);

	return action_taken_index;
}

int main (int argc, char *argv[])
{
	/* avoid unused warning */
	(void) argc;
	(void) argv;

	int i = 0;

	srand(time(NULL));

	/* initialize the qtable */
	qtable_init(&qtable, STATES, ACTIONS);
	qtable_random(&qtable);

	for(i=0;i<10;i++)
	{
		qtable_print(&qtable);
		game_init(&game);
		game_run(&game, get_input_qlearning);
	}
}
