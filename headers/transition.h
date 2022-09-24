#ifndef TRANSITION_H
#define TRANSITION_H

#include <SDL2/SDL.h>
#include "state.h"

class State;
class Transition {
	private:
		char _symbol;
		State* _dest_state;
        public:
		SDL_Texture* texture;
		SDL_Rect rect;
                Transition(char symbol, State* dest_state);
		void setState(State* dest_state);
		void setSymbol(char symbol);
		State* getState();
		char getSymbol();
};

#endif
