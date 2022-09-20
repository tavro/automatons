#include "dfa.h"
#include <iostream>

DFA::DFA(string alphabet, State* start_state) {
	for(char& c : alphabet) {
		_alphabet.push_back(c);
	}
	_start_state = start_state;
}

void DFA::autofill(vector<State> states) {
	for(int i = 0; i < states.size(); i++) {
		switch(states[i].getType()) {
			case Start:
				break;
			case None:
				_states.push_back(&states[i]);
				break;
			case Final:
				_final_states.push_back(&states[i]);
				break;
		}
	}
}

void DFA::traverse(string x) {
	State* current_state = _start_state;
	cout << current_state->getName() << "->";
	for(char& c : x) {
		State* new_current_state = current_state->followTransition(c);
		if(new_current_state != nullptr) {
			current_state = new_current_state;
			if(current_state->getType() == Final) {
				cout << current_state->getName() << endl;
			}
			else {
				cout << current_state->getName() << "->";
			}
		}
	}
}

void DFA::print() {

}
