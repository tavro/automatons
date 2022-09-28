#include "circle.h"
#include "text.h"
#include "state.h"

void SDL_DrawArrow(SDL_Renderer* renderer, int startX, int startY, int endX, int endY);
void SDL_DrawTransition(SDL_Renderer* renderer, State* state, State* otherState, const char* symbol, TTF_Font *font) {
	int startX, endX, yOffset;
	if (state->xPosition < otherState->xPosition) {
		startX = state->xPosition + state->radius;
		endX = otherState->xPosition - otherState->radius;
		yOffset = 16;
	}
	else {
		startX = state->xPosition - state->radius;
		endX = otherState->xPosition + otherState->radius;
		yOffset = -16;
	}

	SDL_DrawArrow(renderer, startX, state->yPosition + yOffset, endX, otherState->yPosition + yOffset);
	int xMiddle = (startX + endX)/2;
	int yMiddle = (state->yPosition + otherState->yPosition + yOffset*2)/2;
	SDL_DrawText(renderer, xMiddle, yMiddle, symbol, font, &state->getTransition(0)->texture, &state->getTransition(0)->rect);
}

void SDL_DrawArrow(SDL_Renderer* renderer, int startX, int startY, int endX, int endY) {
	SDL_RenderDrawLine(renderer, startX, startY, endX, endY);

	int newEndX;
	if(startX < endX) {
		newEndX = endX-16;
	}
	else {
		newEndX = endX+16;
	}

	SDL_RenderDrawLine(renderer, newEndX, endY+16, endX, endY);
	SDL_RenderDrawLine(renderer, newEndX, endY-16, endX, endY);
}

void SDL_DrawState(SDL_Renderer* renderer, State* state, TTF_Font *font, const char* text) {
        int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawCircle(renderer, x, y, r);
	SDL_DrawText(renderer, x, y, text, font, &state->texture, &state->rect);
}

void SDL_DrawStartState(SDL_Renderer* renderer, State* state, TTF_Font *font, const char* text) {
	int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawArrow(renderer, x-r*2, y, x-r, y);
        SDL_DrawCircle(renderer, x, y, r);
	SDL_DrawText(renderer, x, y, text, font, &state->texture, &state->rect);
}

void SDL_DrawFinalState(SDL_Renderer* renderer, State* state, TTF_Font *font, const char* text) {
        int x = state->xPosition;
	int y = state->yPosition;
	int r = state->radius;
	SDL_DrawCircle(renderer, x, y, r);
        SDL_DrawCircle(renderer, x, y, r-8);
	SDL_DrawText(renderer, x, y, text, font, &state->texture, &state->rect);
}
