#include "circle.h"
#include "text.h"
#include "state.h"

void SDL_DrawArrow(SDL_Renderer* renderer, int startX, int startY, int endX, int endY);
void SDL_DrawTransition(SDL_Renderer* renderer, State* state, State* otherState, char* symbol, TTF_Font *font) {
	int startX = state->xPosition + state->radius;
	int endX = otherState->xPosition - otherState->radius;
	//SDL_RenderDrawLine(renderer, startX, state->yPosition, endX, otherState->yPosition);
	SDL_DrawArrow(renderer, startX, state->yPosition, endX, otherState->yPosition);
	int xMiddle = (startX + endX)/2;
	SDL_DrawText(renderer,xMiddle, state->yPosition, symbol, font, &state->getTransition(0)->texture, &state->getTransition(0)->rect);
}

void SDL_DrawArrow(SDL_Renderer* renderer, int startX, int startY, int endX, int endY) {
	SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
	SDL_RenderDrawLine(renderer, endX-16, startY+16, endX, endY);
	SDL_RenderDrawLine(renderer, endX-16, startY-16, endX, endY);
}

void SDL_DrawState(SDL_Renderer* renderer, State* state, TTF_Font *font, char* text) {
        int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawCircle(renderer, x, y, r);
	SDL_DrawText(renderer, x, y, text, font, &state->texture, &state->rect);
}

void SDL_DrawStartState(SDL_Renderer* renderer, State* state, TTF_Font *font, char* text) {
	int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawArrow(renderer, x-r*2, y, x-r, y);
        SDL_DrawCircle(renderer, x, y, r);
	SDL_DrawText(renderer, x, y, text, font, &state->texture, &state->rect);
}

void SDL_DrawFinalState(SDL_Renderer* renderer, State* state, TTF_Font *font, char* text) {
        int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawCircle(renderer, x, y, r);
        SDL_DrawCircle(renderer, x, y, r-8);
	SDL_DrawText(renderer, x, y, text, font, &state->texture, &state->rect);
}
