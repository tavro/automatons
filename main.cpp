#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "headers/dfa.h"
#include "headers/state-drawer.h"

int main()
{
	State start_state(Start, "q0", 320-64*2, 240, 32);
        State state(None, "q1", 320, 240, 32);
        State final_state(Final, "q2", 320+64*2, 240, 32);

        start_state.createTransition('0', &state);
        state.createTransition('1', &final_state);
        state.createTransition('1', &start_state);
        state.createTransition('0', &final_state);

        vector<State*> states;
        states.push_back(&start_state);
        states.push_back(&state);
        states.push_back(&final_state);

        DFA dfa("01", &start_state);
        dfa.autofill(states);
        dfa.printTable();
        dfa.traverse("01");

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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        TTF_Font *font = TTF_OpenFont("fonts/sans.ttf", 16);
	if (font == NULL) {
                printf("Could not find font \n");
                return 1;
        }

	SDL_DrawStartState(renderer, &start_state, font, "q0");
	SDL_DrawState(renderer, &state, font, "q1");
	SDL_DrawFinalState(renderer, &final_state, font, "q2");

	SDL_DrawTransition(renderer, &start_state, &state, "0", font);
	SDL_DrawTransition(renderer, &state, &final_state, "1", font);

	for(int i = 0; i < states.size(); i++) {
		SDL_RenderCopy(renderer, states[i]->texture, NULL, &states[i]->rect);
		if(states[i]->getTransition(0) != nullptr) {
			SDL_RenderCopy(renderer, states[i]->getTransition(0)->texture, NULL, &states[i]->getTransition(0)->rect);
		}
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(5000);		// hold open for 5000 ms

	for(int i = 0; i < states.size(); i++) {
		SDL_DestroyTexture(states[i]->texture);
		if(states[i]->getTransition(0) != nullptr) {
			SDL_DestroyTexture(states[i]->getTransition(0)->texture);
		}
	}
    	TTF_Quit();

    	SDL_DestroyWindow(window);	// destroy window
    	SDL_Quit();			// clean up

	return 0;
}
