
#include<SDL/SDL.h>
#include<iostream>

#pragma once

#include"event.hpp"
// #include"cell.hpp"
#include"position.hpp"
#include"user.hpp"

class Window: public Event{
    private:
    unsigned running;
    SDL_Surface* surface[2];
    SDL_Surface* test, *block;
    Position position;

    public:
    Window(){
        running=1;
        surface[0]=NULL;
        surface[1]=NULL;
        test=NULL;
        block=NULL;

        on_init();
    }
    static Window* create(){
        if(!window) window=new Window();
        return window;
    }
    int on_execute(User& user1, User& user2);

    bool on_init();
    void on_event(SDL_Event* event);
    void on_exit();
    void on_loop(User& user1, User& user2);
    void on_render();
    void on_quit();

    void on_LButton_down(int x, int y);
    ~Window(){
        window->on_quit();
    }

    private:
    static Window* window;
};
