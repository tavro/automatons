#include "state.h"

class State;
class DFA {
	private:
		vector<char> _alphabet;
                vector<State*> _states;
                vector<State*> _final_states;
                State* _start_state;
        public:
		DFA(string alphabet, State* start_state);
		void autofill(vector<State*> states);
		void traverse(string x);
		void printTable();
		void printAlphabet();
		void printStartStateTransitions();
		void printStateTransitions(State* state);
		void printFinalStatesTransitions();
		void printStatesTransitions();
};
