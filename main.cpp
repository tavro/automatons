#include <iostream>

#include "dfa.h"

int main()
{
	State start_state(Start, "q0");
	State state(None, "q1");
	State final_state(Final, "q2");

	start_state.createTransition('0', &state);
	state.createTransition('1', &final_state);

	vector<State> states;
	states.push_back(start_state);
	states.push_back(state);
	states.push_back(final_state);

	DFA dfa("01", &start_state);
	dfa.autofill(states);
	dfa.print(); //TODO: Implement
	dfa.traverse("01");

	return 0;
}
