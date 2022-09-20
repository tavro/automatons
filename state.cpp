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

void State::addTransition(Transition transition) {
	transitions.push_back(transition);
}

void State::createTransition(char symbol, State* dest_state) {
	Transition transition(symbol, dest_state);
	addTransition(transition);
}

int State::getTransitionIndex(char symbol) {
	for(int i = 0; i < transitions.size(); i++) {
		char c = transitions[i].getSymbol();
		//TODO: Figure out why c is nothing
		if(symbol == c) {
			return i;
		}
	}
	return -1;
}

State* State::followTransition(char symbol) {
	int index = getTransitionIndex(symbol);
	if(index != -1) {
		return transitions[index].getState();
	}
	return nullptr;
}
