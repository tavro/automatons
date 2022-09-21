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

	SDL_Rect rect1, rect2, rect3;
        SDL_Texture *texture1, *texture2, *texture3;
        TTF_Font *font = TTF_OpenFont("fonts/sans.ttf", 16);
	if (font == NULL) {
                printf("Could not find font \n");
                return 1;
        }

	SDL_DrawStartState(renderer, &start_state, font, &texture3, &rect3, "q0");
        SDL_DrawState(renderer, &state, font, &texture1, &rect1, "q1");
        SDL_DrawFinalState(renderer, &final_state, font, &texture2, &rect2, "q2");
	SDL_DrawTransition(renderer, &start_state, &state);
	SDL_DrawTransition(renderer, &state, &final_state);

	SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(renderer, texture2, NULL, &rect2);
	SDL_RenderCopy(renderer, texture3, NULL, &rect3);

	SDL_RenderPresent(renderer);
	SDL_Delay(5000);		// hold open for 5000 ms

	SDL_DestroyTexture(texture1);
    	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(texture3);
    	TTF_Quit();

    	SDL_DestroyWindow(window);	// destroy window
    	SDL_Quit();			// clean up

	return 0;
}
