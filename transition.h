#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"

class State;
class Transition {
	private:
		char _symbol;
		State* _dest_state;
        public:
                Transition(char symbol, State* dest_state);
		void setState(State* dest_state);
		void setSymbol(char symbol);
		State* getState();
		char getSymbol();
};

#endif
