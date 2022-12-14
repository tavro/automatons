#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "headers/dfa.h"
#include "headers/state-drawer.h"

vector<State*> states;
State start_state(Start, "q0", 320-64*2, 240, 32);
State state(None, "q1", 320, 240, 32);
State final_state(Final, "q2", 320+64*2, 240, 32);

void rerender(SDL_Renderer* renderer, TTF_Font* font) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for(int i = 0; i < states.size(); i++) {
                switch(states[i]->getType()) {
			case Start:
				SDL_DrawStartState(renderer, states[i], font, states[i]->getName().c_str());
				break;
			case None:
				SDL_DrawState(renderer, states[i], font, states[i]->getName().c_str());
				break;
			case Final:
				SDL_DrawFinalState(renderer, states[i], font, states[i]->getName().c_str());
				break;
			default:
				break;
		}

		SDL_RenderCopy(renderer, states[i]->texture, NULL, &states[i]->rect);
		for(int j = 0; j < states[i]->getTransitionSize(); j++) {
			char symbol = states[i]->getTransition(j)->getSymbol();
			const char *sym = &symbol;
			SDL_DrawTransition(renderer, states[i], states[i]->getTransition(j)->getState(), sym, font);
			SDL_RenderCopy(renderer, states[i]->getTransition(0)->texture, NULL, &states[i]->getTransition(0)->rect);
		}
        }

        SDL_RenderPresent(renderer);
}

void mousePress(SDL_MouseButtonEvent& b, SDL_Renderer* renderer, TTF_Font* font) {
	int x, y;
	SDL_PumpEvents(); // make sure we have latest mouse state
	SDL_GetMouseState(&x, &y);

	if(b.button == SDL_BUTTON_LEFT){
		for(int i = 0; i < states.size(); i++) {
			if(!states[i]->isSelected) {
				int x_pos = states[i]->xPosition;
				int y_pos = states[i]->yPosition;
				int radius = states[i]->radius;
				if(x > x_pos-radius && x < x_pos+radius && y > y_pos-radius && y < y_pos + radius) {
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					SDL_DrawState(renderer, states[i], font, states[i]->getName().c_str());
					SDL_RenderCopy(renderer, states[i]->texture, NULL, &states[i]->rect);
					SDL_RenderPresent(renderer);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

					states[i]->isSelected = true;
				}
			}
			else {
				states[i]->xPosition = x;
				states[i]->yPosition = y;
				states[i]->isSelected = false;
				rerender(renderer, font);
			}
		}
	}
	if(b.button == SDL_BUTTON_RIGHT){
		string num = to_string(states.size());
		State* new_state = new State(None, "q" + num, x, y, 32);
		states.push_back(new_state);
		rerender(renderer, font);
	}
}

int main()
{
        start_state.createTransition('0', &state);
	state.createTransition('1', &final_state);
	state.createTransition('0', &start_state);

        states.push_back(&start_state);
        states.push_back(&state);
        states.push_back(&final_state);

	/*
        DFA dfa("01", &start_state);
        dfa.autofill(states);
        dfa.printTable();
        dfa.traverse("01");
	*/

	SDL_Window *window; 		// declare a pointer
    	SDL_Init(SDL_INIT_VIDEO); 	// initialize SDL2
	TTF_Init();

	window = SDL_CreateWindow(
        	"Automatons",          	// window title
        	SDL_WINDOWPOS_UNDEFINED,// initial x position
        	SDL_WINDOWPOS_UNDEFINED,// initial y position
        	640,                   	// width, in pixels
        	480,                   	// height, in pixels
        	SDL_WINDOW_SHOWN
    	);

    	if (window == NULL) {
        	printf("Could not create window: %s\n", SDL_GetError());
        	return 1;
    	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        TTF_Font *font = TTF_OpenFont("fonts/sans.ttf", 16);
	if (font == NULL) {
                printf("Could not find font \n");
                return 1;
        }

	rerender(renderer, font);

	bool running = true;
	while(running) {
		SDL_Event e;
        	while(SDL_PollEvent(&e)){
                	switch(e.type){
                        	case SDL_QUIT:
                                	running = false;
                                	break;
                        	case SDL_MOUSEBUTTONDOWN:
                                	mousePress(e.button, renderer, font);
                                	break;
                	}
        	}
	}

	for(int i = 0; i < states.size(); i++) {
		SDL_DestroyTexture(states[i]->texture);
		if(states[i]->getTransitionSize() > 0) {
			if(states[i]->getTransition(0) != nullptr) {
				SDL_DestroyTexture(states[i]->getTransition(0)->texture);
			}
		}
	}
    	TTF_Quit();

    	SDL_DestroyWindow(window);	// destroy window
    	SDL_Quit();			// clean up

	return 0;
}
