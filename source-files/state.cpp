#include "../headers/state.h"
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
	if(followTransition(symbol) == nullptr) {
		Transition transition(symbol, dest_state);
		addTransition(transition);
	}
	else {
		cout << "A DFA is not allowed to have multiple transitions on the same symbol" << endl;
	}
}

int State::getTransitionIndex(char symbol) {
	for(int i = 0; i < transitions.size(); i++) {
		char c = transitions[i].getSymbol();
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

int State::getTransitionSize() {
	return transitions.size();
}

Transition State::getTransition(int index) {
	return transitions[index];
}
