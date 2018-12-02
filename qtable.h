#ifndef QTABLE_H
#define QTABLE_H

typedef struct qtable_struct
{
	int states;
	int actions;
	float **values;
	
} qtable_td;

void qtable_init(qtable_td *qtable, int states, int actions);
void qtable_random(qtable_td *qtable);
void qtable_update(qtable_td *qtable, 
                   int old_state, 
                   int outcome_state, 
                   int action, 
                   float learning_rate, 
                   float discount,
                   float reward);
void qtable_print(qtable_td *qtable);

#endif /* QTABLE_H */
