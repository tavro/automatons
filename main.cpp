#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "headers/dfa.h"
#include "headers/circle.h"

void SDL_DrawText(SDL_Renderer *renderer, int x, int y, char* text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}

void SDL_DrawStartState(SDL_Renderer* renderer, int x, int y, int r) {
	//TODO: Make function for drawing arrow
	SDL_RenderDrawLine(renderer, x-r*2, y, x-r, y);
	SDL_RenderDrawLine(renderer, x-r-16, y+r/2, x-r, y);
	SDL_RenderDrawLine(renderer, x-r-16, y-r/2, x-r, y);
	SDL_DrawCircle(renderer, x, y, r);
}

void SDL_DrawFinalState(SDL_Renderer* renderer, int x, int y, int r) {
	SDL_DrawCircle(renderer, x, y, r);
	SDL_DrawCircle(renderer, x, y, r-8);
}

int main()
{
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
	SDL_DrawStartState(renderer, 320-64*2, 240, 32);
	SDL_DrawCircle(renderer, 320, 240, 32);
	SDL_DrawFinalState(renderer, 320+64*2, 240, 32);

	SDL_Rect rect1, rect2;
        SDL_Texture *texture1, *texture2;
        TTF_Font *font = TTF_OpenFont("fonts/sans.ttf", 16);
        if (font == NULL) {
                printf("Could not find font \n");
                return 1;
        }
	SDL_DrawText(renderer, 0, 0, "q0", font, &texture1, &rect1);
    	SDL_DrawText(renderer, 0, rect1.y + rect1.h, "q2", font, &texture2, &rect2);

	SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(renderer, texture2, NULL, &rect2);

	SDL_RenderPresent(renderer);
	SDL_Delay(5000);		// hold open for 5000 ms

	SDL_DestroyTexture(texture1);
    	SDL_DestroyTexture(texture2);
    	TTF_Quit();

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
