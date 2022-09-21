#include "circle.h"
#include "text.h"
#include "state.h"

void SDL_DrawState(SDL_Renderer* renderer, State* state, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, char* text) {
        int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawCircle(renderer, x, y, r);
	SDL_DrawText(renderer, x, y, text, font, texture, rect);
}

void SDL_DrawStartState(SDL_Renderer* renderer, State* state, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, char* text) {
        //TODO: Make function for drawing arrow
	int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
        SDL_RenderDrawLine(renderer, x-r*2, y, x-r, y);
        SDL_RenderDrawLine(renderer, x-r-16, y+r/2, x-r, y);
        SDL_RenderDrawLine(renderer, x-r-16, y-r/2, x-r, y);
        SDL_DrawCircle(renderer, x, y, r);
	SDL_DrawText(renderer, x, y, text, font, texture, rect);
}

void SDL_DrawFinalState(SDL_Renderer* renderer, State* state, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, char* text) {
        int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawCircle(renderer, x, y, r);
        SDL_DrawCircle(renderer, x, y, r-8);
	SDL_DrawText(renderer, x, y, text, font, texture, rect);
}
