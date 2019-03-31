
#include<SDL/SDL.h>
#include<iostream>

#pragma once

#include"event.hpp"
// #include"cell.hpp"
#include"position.hpp"
#include"user.hpp"

class Window: public Event{
    // private:
    // static Window* window;

    private:
    unsigned running;
    SDL_Surface* surface[2];
    SDL_Surface* test, *block;
    Position position;
    unsigned cell_status[121], my_cell_status[121];

    public:
    Window(){
        running=1;
        surface[0]=NULL;
        surface[1]=NULL;
        test=NULL;
        block=NULL;
        position.init(-1, -1);
        for(unsigned i=0;i<121;++i){
            cell_status[i]=my_cell_status[i]=0;
        }

        on_init();
    }
    // static Window* create(){
        // window=new Window();
        // return window;
    // }
    int on_execute(User& user1, User& user2);

    bool on_init();
    void on_event(SDL_Event* event);
    void on_exit();
    void on_loop(User& user1, User& user2);
    void on_render();
    void on_quit();

    void on_LButton_down(int x, int y);
    ~Window(){
        // window->on_quit();
        on_quit();
    }
};
