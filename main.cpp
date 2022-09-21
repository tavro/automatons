#include <iostream>
#include <SDL2/SDL.h>

#include "dfa.h"
#include "circle.h"

int main()
{
	SDL_Window *window; 		// declare a pointer
    	SDL_Init(SDL_INIT_VIDEO); 	// initialize SDL2

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
	SDL_DrawCircle(renderer, 320, 240, 32);
	SDL_RenderPresent(renderer);	// render circle
	SDL_Delay(5000);		// hold open for 5000 ms
    	SDL_DestroyWindow(window);	// destroy window
    	SDL_Quit();			// clean up

	State start_state(Start, "q0");
	State state(None, "q1");
	State final_state(Final, "q2");

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

	return 0;
}
