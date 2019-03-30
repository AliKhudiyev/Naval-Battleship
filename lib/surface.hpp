
#include<SDL/SDL.h>

#pragma once

class Surface{
    public:
    Surface();

    static SDL_Surface* on_load(const char* file_name);
    static bool on_draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);
    static bool on_draw(SDL_Surface* dest, SDL_Surface* src, int x1, int y1, int x2, int y2, int width, int height);
};
