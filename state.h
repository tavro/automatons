#ifndef STATE_H
#define STATE_H

#include "transition.h"
#include <string>
#include <vector>

using namespace std;

enum state_type { Start, Final, None };

class Transition;
class State {
        private:
                state_type _type;
                string _name;
		vector<Transition> transitions;
        public:
                State(state_type type, string name);
                void print();
                void setType(state_type type);
                void setName(string name);
		void createTransition(char symbol, State* dest_state);
		void addTransition(Transition transition);
		int getTransitionIndex(char symbol);
		State* followTransition(char symbol);
                state_type getType();
                string getName();
};

#endif
