
#include<SDL/SDL.h>

#pragma once

#define BACKGROUND  "resource/background.bmp"
#define SHIP        "resource/ship.bmp"
#define SHOT_SHIP   "resource/shotShip.bmp"
#define SHOT_SEA    "resource/shotSea.bmp"
#define LOST_SHIP   "resource/lostShip.bmp"
#define LOST_SEA    "resource/lostSea.bmp"

class Surface{
    public:
    Surface();

    static SDL_Surface* on_load(const char* file_name);
    static bool on_draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);
    static bool on_draw(SDL_Surface* dest, SDL_Surface* src, int x1, int y1, int x2, int y2, int width, int height);
};
