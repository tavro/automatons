#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void SDL_DrawText(SDL_Renderer *renderer, int x, int y, const char* text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x-text_width/2;
    rect->y = y-text_height/2;
    rect->w = text_width;
    rect->h = text_height;
}
