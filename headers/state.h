#ifndef STATE_H
#define STATE_H

#include "transition.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

enum state_type { Start, Final, None };

class Transition;
class State {
        private:
                state_type _type;
                string _name;
		vector<Transition> transitions;
        public:
		int xPosition;
		int yPosition;
		int radius;
		bool isSelected;
		SDL_Texture* texture;
		SDL_Rect rect;
                State(state_type type, string name, int x, int y, int r);
                void print();
                void setType(state_type type);
                void setName(string name);
		void createTransition(char symbol, State* dest_state);
		void addTransition(Transition transition);
		int getTransitionIndex(char symbol);
		int getTransitionSize();
		Transition* getTransition(int index);
		State* followTransition(char symbol);
                state_type getType();
                string getName();
};

#endif
