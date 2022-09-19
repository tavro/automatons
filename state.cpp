#include "state.h"
#include <iostream>

State::State(state_type type, string name) {
	setType(type);
	setName(name);
}

void State::print() {
	string type;
	switch(getType()) {
		case 0:
			type = "START";
			break;
		case 1:
			type = "NONE";
			break;
		case 2:
			type = "FINAL";
			break;
	}
	cout << type << ':' << getName() << endl;
}

void State::setType(state_type type) {
	_type = type;
}

void State::setName(string name) {
	_name = name;
}

state_type State::getType() {
	return _type;
}

string State::getName() {
	return _name;
}

void State::addTransition(Transition* transition) {
	transitions.push_back(transition);
}

void State::createTransition(char symbol, State* dest_state) {
	Transition transition(symbol, dest_state);
	addTransition(&transition);
}