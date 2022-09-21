#include "circle.h"
#include "text.h"
#include "state.h"

void SDL_DrawTransition(SDL_Renderer* renderer, State* state, State* otherState) {
	SDL_RenderDrawLine(renderer, state->xPosition + state->radius, state->yPosition, otherState->xPosition - otherState->radius, otherState->yPosition);
	//TODO: int middle
	//TODO: SDL_DrawText(renderer, middle, state->yPosition, symbol, font, texture, rect);
}

void SDL_DrawArrow(SDL_Renderer* renderer, int startX, int startY, int endX, int endY) {
	SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
	SDL_RenderDrawLine(renderer, startX, startY+16, endX, endY);
	SDL_RenderDrawLine(renderer, startX, startY-16, endX, endY);
}

void SDL_DrawState(SDL_Renderer* renderer, State* state, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, char* text) {
        int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawCircle(renderer, x, y, r);
	SDL_DrawText(renderer, x, y, text, font, texture, rect);
}

void SDL_DrawStartState(SDL_Renderer* renderer, State* state, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, char* text) {
	int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawArrow(renderer, x-r*2, y, x-r, y);
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
