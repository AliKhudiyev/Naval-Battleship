#include"surface.hpp"

Surface::Surface(){
    ;
}

SDL_Surface* Surface::on_load(const char* file_name){
    SDL_Surface* tmp=nullptr;
    SDL_Surface* surface=nullptr;

    if(!(tmp=SDL_LoadBMP(file_name))) return NULL;

    surface=SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);

    return surface;
}

bool Surface::on_draw(SDL_Surface* dest, SDL_Surface* src, int x, int y){
    if(!dest || !src) return false;

    SDL_Rect dest_r;
    dest_r.x=x;
    dest_r.y=y;
    
    SDL_BlitSurface(src, NULL, dest, &dest_r);

    return true;
}

bool Surface::on_draw(SDL_Surface* dest, SDL_Surface* src, int x1, int y1, int x2, int y2, int width, int height){
    if(!dest || !src) return false;

    SDL_Rect dest_r;
    dest_r.x=x1;
    dest_r.y=y1;

    SDL_Rect src_r;
    src_r.x=x2;
    src_r.y=y2;
    src_r.w=width;
    src_r.h=height;

    SDL_BlitSurface(src, &src_r, dest, &dest_r);
    return true;
}