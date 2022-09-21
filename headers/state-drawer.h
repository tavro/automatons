#include "circle.h"

void SDL_DrawState(SDL_Renderer* renderer, int x, int y, int r) {
        SDL_DrawCircle(renderer, x, y, r);
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
