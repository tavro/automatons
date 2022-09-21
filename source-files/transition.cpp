#include "../headers/transition.h"
#include <iostream>

Transition::Transition(char symbol, State* dest_state) {
	setSymbol(symbol);
	setState(dest_state);
}

void Transition::setState(State* dest_state) {
	_dest_state = dest_state;
}

void Transition::setSymbol(char symbol) {
	_symbol = symbol;
}

State* Transition::getState() {
	return _dest_state;
}

char Transition::getSymbol() {
	return _symbol;
}
