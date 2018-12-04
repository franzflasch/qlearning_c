#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <qtable.h>

void qtable_init(qtable_td *qtable, int states, int actions)
{
	int i = 0;
	
	/* allocate qtable with random values */
	qtable->values = (float**) calloc(states, sizeof(float *));
	for(i=0;i<states;i++)
	    qtable->values[i]=(float *) calloc(actions, sizeof(float));

	qtable->states = states;
	qtable->actions = actions;
}

void qtable_random(qtable_td *qtable)
{
	int i,j = 0;

	srand(time(NULL));
	
	for(i=0;i<qtable->states;i++)
	{
		for(j=0;j<qtable->actions;j++)
		{
			qtable->values[i][j] = (float)rand()/(float)RAND_MAX;
		}
	}
}

void qtable_update(qtable_td *qtable, 
                   int old_state, 
                   int outcome_state, 
                   int action, 
                   float learning_rate, 
                   float discount,
                   float reward)
{
	int i = 0;
	float max_val = qtable->values[outcome_state][0];

	/* find max value of the new state */
	for(i=0;i<qtable->actions;i++)
	{
		if(qtable->values[outcome_state][i] > max_val)
			max_val = qtable->values[outcome_state][i];
	}
	//printf("MAXVAL: %f reward: %f old_state %d outcome_state %d\n", max_val, reward, old_state, outcome_state);
	
	qtable->values[old_state][action] = qtable->values[old_state][action] + learning_rate * (reward + (discount * max_val) - qtable->values[old_state][action]);
}

//@q_table[@old_state][@action_taken_index] = @q_table[@old_state][@action_taken_index] + @learning_rate * (r + @discount * @q_table[@outcome_state].max - @q_table[@old_state][@action_taken_index])


void qtable_print(qtable_td *qtable)
{
	int i,j = 0;

	for(i=0;i<qtable->states;i++)
	{
		printf("qtable[%d]:", i);
		for(j=0;j<qtable->actions;j++)
		{
			//printf("[%f]\n", qtable[(i*ACTIONS)+j]);
			printf("[%f] ", qtable->values[i][j]);
		}
		printf("\n");
	}
}
